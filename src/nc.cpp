#include "nc.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

Nc::Nc(void)
{
  mIdPolarFile = 0;
  mDimCountX = 0;
  mDimCountY = 0;
}

Nc::Nc(const std::string aPolarFile, std::string aVarNameX, std::string aVarNameY)
{
  mIdPolarFile = 0;
  mDimCountX = 0;
  mDimCountY = 0;

  Open(aPolarFile, aVarNameX, aVarNameY);
}

Nc::~Nc()
{
  nc_close(mIdPolarFile);
}

int Nc::Open(const std::string aPolarFile, std::string aVarNameX, std::string aVarNameY)
{
  if(!aPolarFile.empty() && !aVarNameX.empty() && !aVarNameY.empty())
    {
      int errRet = nc_open(aPolarFile.c_str(), NC_NOWRITE, &mIdPolarFile);
      if(errRet == NC_NOERR)
        {
          errRet = nc_inq_varid(mIdPolarFile, aVarNameX.c_str(), &mSailVarX);
          if(errRet != NC_NOERR)
            {
              nc_close(mIdPolarFile);
            }
          else
            {
              errRet = nc_inq_varndims(mIdPolarFile, mSailVarX, &mDimCountX);
              if(errRet != NC_NOERR)
                {
                  nc_close(mIdPolarFile);
                }
            }

          errRet = nc_inq_varid(mIdPolarFile, aVarNameY.c_str(), &mSailVarY);
          if(errRet != NC_NOERR)
            {
              nc_close(mIdPolarFile);
            }
          else
            {
              errRet = nc_inq_varndims(mIdPolarFile, mSailVarY, &mDimCountY);
              if(errRet != NC_NOERR)
                {
                  nc_close(mIdPolarFile);
                }

              return 0;
            }
        }
    }

  return -1;
}

void Nc::Close(void)
{
  if(mIdPolarFile)
    nc_close(mIdPolarFile);
}

int Nc::Init(std::string aSpeedWaterVarName, std::string aWindSpeedVarName, std::string aWindAngleVarName)
{
  int err = -1;

  if(TOTAL_SAIL_DIM_COUNT == mDimCountX && TOTAL_SAIL_DIM_COUNT == mDimCountY)
    {
      int speedTroughWaterVar, trueWindSpeedVar, trueWindAngleVar;
      size_t stwSize, twsSize, twaSize; //2 last dims not used
      int dimIds[NC_MAX_VAR_DIMS];
      int nDims;

      nc_inq_varid(mIdPolarFile, aSpeedWaterVarName.c_str(), &speedTroughWaterVar);
      nc_inq_varid(mIdPolarFile, aWindSpeedVarName.c_str(), &trueWindSpeedVar);
      nc_inq_varid(mIdPolarFile, aWindAngleVarName.c_str(), &trueWindAngleVar);

      //speedThroughWaterVar
      nc_inq_varndims(mIdPolarFile, speedTroughWaterVar, &nDims);
      nc_inq_vardimid(mIdPolarFile, speedTroughWaterVar, dimIds);
      nc_inq_dimlen(mIdPolarFile, dimIds[0], &stwSize);

      //trueWindSpeedVar
      nc_inq_varndims(mIdPolarFile, trueWindSpeedVar, &nDims);
      nc_inq_vardimid(mIdPolarFile, trueWindSpeedVar, dimIds);
      nc_inq_dimlen(mIdPolarFile, dimIds[0], &twsSize);

      //trueWindAngleVar
      nc_inq_varndims(mIdPolarFile, trueWindAngleVar, &nDims);
      nc_inq_vardimid(mIdPolarFile, trueWindAngleVar, dimIds);
      nc_inq_dimlen(mIdPolarFile, dimIds[0], &twaSize);

      mStw.resize(stwSize);
      mTws.resize(twsSize);
      mTwa.resize(twaSize);

      /*Store data*/
      nc_get_var_float(mIdPolarFile, speedTroughWaterVar, mStw.data());
      nc_get_var_float(mIdPolarFile, trueWindSpeedVar, mTws.data());
      nc_get_var_float(mIdPolarFile, trueWindAngleVar, mTwa.data());

      err=0;
    }

  return err;
}

size_t FindClosestIndex(const std::vector<float>& aValue, float aTarget)
{
  size_t best = 0;
  float minDiff = std::abs(aValue[0] - aTarget);

  for(size_t i = 1; i < aValue.size(); ++i)
    {
      float diff = std::abs(aValue[i] - aTarget);
      if(diff < minDiff)
        {
          minDiff = diff;
          best = i;
        }
    }

  return best;
}

float Nc::GetForce(char aAxe, float aStwValue, float aTwsValue, float aTwaValue)
{
  float force = 0;

  size_t iStw = FindClosestIndex(mStw, aStwValue);
  size_t iTws = FindClosestIndex(mTws, aTwsValue);
  size_t iTwa = FindClosestIndex(mTwa, aTwaValue);

  std::vector<size_t> start = {iStw, iTws, iTwa, 0, 0};
  std::vector<size_t> count = {1, 1, 1, 1, 1};

  if('X' == aAxe)
    {
      nc_get_vara_float(mIdPolarFile, mSailVarX, start.data(), count.data(), &force);
    }
  else if('Y' == aAxe)
    {
      nc_get_vara_float(mIdPolarFile, mSailVarY, start.data(), count.data(), &force);
    }

  return force;
}

std::string Nc::GetGlobalAttrString(const std::string aName)
{
  nc_type xtype;
  size_t len = 0;

  if(NC_NOERR != nc_inq_att(mIdPolarFile, NC_GLOBAL, aName.c_str(), &xtype, &len) || NC_CHAR != xtype)
    return "";

  std::vector<char> buffer(len+1, 0);
  nc_get_att_text(mIdPolarFile, NC_GLOBAL, aName.c_str(), buffer.data());

  return std::string(buffer.data(), len);
}

int Nc::GetSailCount(void)
{
  int count = 0;
  int nVars = 0;

  nc_inq_nvars(mIdPolarFile, &nVars);

  for(int i = 0; i < nVars; i++)
    {
      char name[NC_MAX_NAME+1] = {0};
      nc_inq_varname(mIdPolarFile, i, name);
      std::string varName(name);

      //Per-sail force variables are named "Sail_<sail name>_X" (the aggregate is "TotalSails_X")
      if(0 == varName.rfind("Sail_", 0) && varName.size() > 2 &&
         0 == varName.compare(varName.size()-2, 2, "_X"))
        {
          count++;
        }
    }

  return count;
}

float Nc::GetMaxForce(void)
{
  float maxForce = 0;
  int dimIds[NC_MAX_VAR_DIMS];
  int nDims = 0;
  size_t totalCount = 1, dimLen = 0;

  nc_inq_varndims(mIdPolarFile, mSailVarX, &nDims);
  nc_inq_vardimid(mIdPolarFile, mSailVarX, dimIds);
  for(int i = 0; i < nDims; i++)
    {
      nc_inq_dimlen(mIdPolarFile, dimIds[i], &dimLen);
      totalCount *= dimLen;
    }

  std::vector<float> dataX(totalCount, 0), dataY(totalCount, 0);

  nc_get_var_float(mIdPolarFile, mSailVarX, dataX.data());
  nc_get_var_float(mIdPolarFile, mSailVarY, dataY.data());

  for(size_t i = 0; i < totalCount; i++)
    {
      maxForce = std::max({maxForce, std::abs(dataX[i]), std::abs(dataY[i])});
    }

  return maxForce;
}

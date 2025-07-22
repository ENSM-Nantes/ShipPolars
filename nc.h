#ifndef NC_HPP
#define NC_HPP

#include <string>
#include <vector>
#include <netcdf.h>

#define TOTAL_SAIL_DIM_COUNT (5)

class Nc
{
 public:

  Nc();
  Nc(const std::string aPolarFile, std::string aVarNameX, std::string aVarNameY);
  ~Nc();
  int Open(const std::string aPolarFile, std::string aVarNameX, std::string aVarNameY);
  int Init(std::string aSpeedWaterVarName, std::string aWindSpeedVarName, std::string aWindAngleVarName);
  float GetForce(char aAxe, float aStwValue, float aTwsValue, float aTwaValue);

 private:

  int mIdPolarFile;

  int mSailVarX;
  int mDimCountX;
  int mSailVarY;
  int mDimCountY;

  std::vector<float> mStw;
  std::vector<float> mTws;
  std::vector<float> mTwa;

};




#endif

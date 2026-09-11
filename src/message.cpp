#include "message.h"
#include "tools.h"
#include <iostream>
#include <math.h>

Message::Message()
{
  mSpeedThroughWater=0;
  mTrueWindSpeed=0;
  mTrueWindDir=0;
  mAppWindSpeed=0;
  mAppWindDir=0;
  mRotOnOff=0;
  mRotDir=-1;
  mRotSpeed=0;
  mWindSide = "";
  mShutDown = false;
}

Message::~Message()
{


}

int Message::Parse(const char *aData, size_t aDataSize)
{
  std::string inRawData(aData, aDataSize);
  //std::cout << "Message : " << inRawData << std::endl;

  if(0 == inRawData.substr(0,2).compare("SD"))
    {
      mShutDown = true;
      return 0;
    }

  if(0 == inRawData.substr(0,2).compare("OS"))
    {
      std::vector<std::string> inData = split(&inRawData[2],',');
      unsigned int nbrData = inData.size();

      mSpeedThroughWater = std::stof(inData.at(4));
      mTrueWindSpeed = std::stof(inData.at(6));
      mTrueWindDir = std::stof(inData.at(5));
      mAppWindSpeed = std::stof(inData.at(8));
      mAppWindDir = std::stof(inData.at(7));
      mRotOnOff = std::stoi(inData.at(9));
      mRotDir = std::stoi(inData.at(10));
      mRotSpeed = std::stof(inData.at(11));

      if(GetAWA() < 0)
	mWindSide = "port";
      else
	mWindSide = "starboard";

      mAppWindDir = fabs(mAppWindDir);
    }

  return 0;
}

bool Message::GetShutDown(void)
{
  return mShutDown;
}

const float Message::GetTWS(void)
{
  return mTrueWindSpeed;
}

const float Message::GetAWS(void)
{
  return mAppWindSpeed;
}

const float Message::GetSTW(void)
{
  return mSpeedThroughWater;
}

const float Message::GetAWA(void)
{
  return mAppWindDir;
}

bool Message::GetRotOnOff(void)
{
  return mRotOnOff == 1 ? true : false;
}

int Message::GetRotDir(void)
{
  return mRotDir;
}

float Message::GetRotSpeed(void)
{
  return mRotSpeed;
}


std::string Message::GetWindSide(void)
{
  return mWindSide;
}

#include "message.h"
#include "tools.h"
#include <iostream>

Message::Message()
{
  mSpeedThroughWater="0";
  mTrueWindSpeed="0";
  mTrueWindDir="0";
  mAppWindSpeed="0";
  mAppWindDir="0";
  mRotOnOff="0";
  mRotDir="-1";
  mRotSpeed="0";
}

Message::~Message()
{


}

int Message::Parse(const char *aData, size_t aDataSize)
{
  std::string inRawData(aData, aDataSize);
  //std::cout << "Message : " << inRawData << std::endl;
  
  if(0 == inRawData.substr(0,2).compare("OS"))
    {
      std::vector<std::string> inData = split(&inRawData[2],',');
      unsigned int nbrData = inData.size();

      mSpeedThroughWater = inData.at(4);
      mTrueWindSpeed = inData.at(6);
      mTrueWindDir = inData.at(5);
      mAppWindSpeed = inData.at(8);
      mAppWindDir = inData.at(7);
      mRotOnOff = inData.at(9);
      mRotDir = inData.at(10);
      mRotSpeed = inData.at(11);
    }

  return 0;
}

const float Message::GetTWS(void)
{
  return std::stof(mTrueWindSpeed);
}

const float Message::GetAWS(void)
{
  return std::stof(mAppWindSpeed);
}

const float Message::GetSTW(void)
{
  return std::stof(mSpeedThroughWater);
}

const float Message::GetAWA(void)
{
  return std::stof(mAppWindDir);
}

bool Message::GetRotOnOff(void)
{
  return std::stoi(mRotOnOff) == 1 ? true : false;
}

int Message::GetRotDir(void)
{
  return std::stoi(mRotDir);
}

float Message::GetRotSpeed(void)
{
  return std::stof(mRotSpeed);
}

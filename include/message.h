#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

class Message
{
 public:

  Message();
  ~Message();
  int Parse(const char *aData, size_t aDataSize);
  const float GetTWS(void);
  const float GetSTW(void);
  const float GetAWS(void);
  const float GetAWA(void);
  bool GetRotOnOff(void);
  int GetRotDir(void);
  float GetRotSpeed(void);
  std::string GetWindSide(void);
  
 private:
  float mSpeedThroughWater;
  float mTrueWindSpeed;
  float mTrueWindDir;
  float mAppWindSpeed;
  float mAppWindDir;
  bool mRotOnOff;
  int mRotDir;
  float mRotSpeed;
  std::string mWindSide;
};



#endif

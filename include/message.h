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
  
 private:
  std::string mSpeedThroughWater;
  std::string mTrueWindSpeed;
  std::string mTrueWindDir;
  std::string mAppWindSpeed;
  std::string mAppWindDir;
  std::string mRotOnOff;
  std::string mRotDir;
  std::string mRotSpeed;
};



#endif

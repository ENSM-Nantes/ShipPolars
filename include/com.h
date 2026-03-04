#ifndef COM_HPP
#define COM_HPP

#include <string>
#include <enet/enet.h>
#include "message.h"

#define ENET_SERVER_HOST ("localhost")

class Com
{

public:
  Com();
  ~Com();
  int Connect(std::string aServerName, unsigned int aPort);
  void WaitMessage(unsigned int aTimeout, Message& aMsg);
  int SendMessage(const std::string& aMsg, bool aIsReliable=false);
  bool IsConnected(void){return mIsConnect;}
 private:
  ENetAddress mWiAddress;
  ENetPeer *mWiPeer;
  ENetHost *mWiHandler;
  bool mIsConnect;

};

#endif

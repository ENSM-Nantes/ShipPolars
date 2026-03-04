#include "com.h"
#include "message.h"
#include <iostream>

Com::Com()
{
  mWiHandler = NULL;
  mWiAddress = {0};
  mWiPeer = NULL;
  mIsConnect = false;
}

Com::~Com()
{

}


int Com::Connect(std::string aServerName, unsigned int aPort)
{
  ENetEvent event;

  if(enet_initialize() != 0)
    {
      std::cout << "Enet initialization failed !" << std::endl;
      return -1;
    }

  mWiHandler = enet_host_create(NULL, 1, 2, 0, 0);

  if(NULL == mWiHandler)
    {
      std::cout << "Client creation failed !" << std::endl;
      enet_deinitialize();
      return -1;
    }

  enet_address_set_host(&mWiAddress, aServerName.c_str());
  mWiAddress.port = aPort;

  mWiPeer = enet_host_connect(mWiHandler, &mWiAddress, 2, 15);//0x0F for WI

  if(NULL == mWiPeer)
    {
      std::cout << "Connection failed !" << std::endl;
      enet_deinitialize();
      return -1;
    }

  if(enet_host_service(mWiHandler, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    std::cout << "Connect to the server" << std::endl;
    enet_host_flush(mWiHandler);
    mIsConnect = true;
  }
  else {
    std::cout << "Not connected --> Reset !" << std::endl;
    enet_peer_reset (mWiPeer);
    return -1;
  }

  return 0;

}


void Com::WaitMessage(unsigned int aTimeout, Message& aMsg)
{
  ENetEvent event;
  
  if(enet_host_service(mWiHandler, &event, aTimeout) > 0)
    {
      if(ENET_EVENT_TYPE_RECEIVE == event.type)
        {
	  aMsg.Parse((char*)event.packet->data, event.packet->dataLength);
          enet_packet_destroy(event.packet);
        }
    }
}


int Com::SendMessage(const std::string& aMsg, bool aIsReliable)
{
  int ret = -1;

  if(aMsg.length() > 0)
    {
      std::cout << "Msg length : " << aMsg << std::endl;
      enet_uint32 packetFlag = 0;
      if (aIsReliable)
        packetFlag = ENET_PACKET_FLAG_RELIABLE;

      ENetPacket* packet = enet_packet_create(aMsg.c_str(), aMsg.length(), packetFlag);
      std::cout << "Msg sent ! " << std::endl;
      enet_peer_send(mWiPeer, 0, packet);
      enet_host_flush(mWiHandler);
      ret = 0;

    }
  
  return ret;
}

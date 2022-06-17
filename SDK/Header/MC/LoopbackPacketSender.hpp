// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LoopbackPacketSender {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LOOPBACKPACKETSENDER
public:
    class LoopbackPacketSender& operator=(class LoopbackPacketSender const &) = delete;
    LoopbackPacketSender(class LoopbackPacketSender const &) = delete;
    LoopbackPacketSender() = delete;
#endif


public:
    /*0*/ virtual ~LoopbackPacketSender();
    /*1*/ virtual void send(class Packet &);
    /*2*/ virtual void sendToServer(class Packet &);
    /*3*/ virtual void sendToClient(class UserEntityIdentifierComponent const *, class Packet const &);
    /*4*/ virtual void sendToClient(class NetworkIdentifier const &, class Packet const &, unsigned char);
    /*5*/ virtual void sendToClients(std::vector<struct NetworkIdentifierWithSubId> const &, class Packet const &);
    /*6*/ virtual void sendBroadcast(class Packet const &);
    /*7*/ virtual void sendBroadcast(class NetworkIdentifier const &, unsigned char, class Packet const &);
    /*8*/ virtual void flush(class NetworkIdentifier const &, class std::function<void (void)> &&);
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_LOOPBACKPACKETSENDER
#endif
    MCAPI LoopbackPacketSender(unsigned char, class NetworkHandler &);
    MCAPI void addLoopbackCallback(class NetEventCallback &);
    MCAPI void removeLoopbackCallback(class NetEventCallback &);
    MCAPI void setUserList(std::vector<class OwnerPtrT<struct EntityRefTraits>> const *);



};
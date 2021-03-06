// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

struct RakWebSocketDataFrameHeader {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_RAKWEBSOCKETDATAFRAMEHEADER
public:
    struct RakWebSocketDataFrameHeader& operator=(struct RakWebSocketDataFrameHeader const &) = delete;
    RakWebSocketDataFrameHeader(struct RakWebSocketDataFrameHeader const &) = delete;
#endif

public:
    MCAPI RakWebSocketDataFrameHeader();
    MCAPI RakWebSocketDataFrameHeader(bool, bool, bool, bool, bool, enum OpCode, unsigned char);
    MCAPI int getFinBit() const;
    MCAPI int getMaskBit() const;
    MCAPI enum OpCode getOpCode() const;
    MCAPI unsigned char getPayloadLength() const;
    MCAPI int getRSV1Bit() const;
    MCAPI int getRSV2Bit() const;
    MCAPI int getRSV3Bit() const;
    MCAPI ~RakWebSocketDataFrameHeader();

protected:

private:

};
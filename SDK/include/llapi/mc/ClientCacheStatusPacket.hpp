/**
 * @file  ClientCacheStatusPacket.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class ClientCacheStatusPacket.
 *
 */
class ClientCacheStatusPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CLIENTCACHESTATUSPACKET
public:
    class ClientCacheStatusPacket& operator=(class ClientCacheStatusPacket const &) = delete;
    ClientCacheStatusPacket(class ClientCacheStatusPacket const &) = delete;
#endif

public:
    /**
     * @vftbl  0
     * @symbol  __unk_destructor_0
     */
    virtual ~ClientCacheStatusPacket();
    /**
     * @hash   1991549149
     * @vftbl  1
     * @symbol  ?getId\@ClientCacheStatusPacket\@\@UEBA?AW4MinecraftPacketIds\@\@XZ
     */
    virtual enum class MinecraftPacketIds getId() const;
    /**
     * @hash   1640790922
     * @vftbl  2
     * @symbol  ?getName\@ClientCacheStatusPacket\@\@UEBA?AV?$basic_string\@DU?$char_traits\@D\@std\@\@V?$allocator\@D\@2\@\@std\@\@XZ
     */
    virtual std::string getName() const;
    /**
     * @hash   138737677
     * @vftbl  3
     * @symbol  ?write\@ClientCacheStatusPacket\@\@UEBAXAEAVBinaryStream\@\@\@Z
     */
    virtual void write(class BinaryStream &) const;
    /**
     * @hash   1735867597
     * @vftbl  6
     * @symbol  ?_read\@ClientCacheStatusPacket\@\@EEAA?AW4StreamReadResult\@\@AEAVReadOnlyBinaryStream\@\@\@Z
     */
    virtual enum class StreamReadResult _read(class ReadOnlyBinaryStream &);
    /**
     * @hash   -1032473747
     * @symbol  ??0ClientCacheStatusPacket\@\@QEAA\@XZ
     */
    MCAPI ClientCacheStatusPacket();

};
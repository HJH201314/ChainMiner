/**
 * @file  AnimatePacket.hpp
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
 * @brief MC class AnimatePacket.
 *
 */
class AnimatePacket : public Packet {

#define AFTER_EXTRA
// Add Member There
public:
    enum class Action
    {
        NoAction = 0,
        Swing = 1,
        WakeUp = 3,
        CriticalHit = 4,
        // MagicCriticalHit=5,
        RowRight = 128,
        RowLeft = 129,
    };
    ActorRuntimeID mRuntimeId;
    Action mAction;
    float mData;

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ANIMATEPACKET
public:
    class AnimatePacket& operator=(class AnimatePacket const &) = delete;
    AnimatePacket(class AnimatePacket const &) = delete;
#endif

public:
    /**
     * @vftbl  0
     * @symbol  __unk_destructor_0
     */
    virtual ~AnimatePacket();
    /**
     * @hash   206346581
     * @vftbl  1
     * @symbol  ?getId\@AnimatePacket\@\@UEBA?AW4MinecraftPacketIds\@\@XZ
     */
    virtual enum class MinecraftPacketIds getId() const;
    /**
     * @hash   -1272908798
     * @vftbl  2
     * @symbol  ?getName\@AnimatePacket\@\@UEBA?AV?$basic_string\@DU?$char_traits\@D\@std\@\@V?$allocator\@D\@2\@\@std\@\@XZ
     */
    virtual std::string getName() const;
    /**
     * @hash   -531016539
     * @vftbl  3
     * @symbol  ?write\@AnimatePacket\@\@UEBAXAEAVBinaryStream\@\@\@Z
     */
    virtual void write(class BinaryStream &) const;
    /**
     * @hash   417733429
     * @vftbl  6
     * @symbol  ?_read\@AnimatePacket\@\@EEAA?AW4StreamReadResult\@\@AEAVReadOnlyBinaryStream\@\@\@Z
     */
    virtual enum class StreamReadResult _read(class ReadOnlyBinaryStream &);
    /**
     * @hash   -1725207099
     * @symbol  ??0AnimatePacket\@\@QEAA\@XZ
     */
    MCAPI AnimatePacket();
    /**
     * @hash   1421276561
     * @symbol  ??0AnimatePacket\@\@QEAA\@W4Action\@0\@VActorRuntimeID\@\@M\@Z
     */
    MCAPI AnimatePacket(enum class AnimatePacket::Action, class ActorRuntimeID, float);
    /**
     * @hash   1198458128
     * @symbol  ??0AnimatePacket\@\@QEAA\@W4Action\@0\@VActorRuntimeID\@\@\@Z
     */
    MCAPI AnimatePacket(enum class AnimatePacket::Action, class ActorRuntimeID);
    /**
     * @hash   1711801450
     * @symbol  ??0AnimatePacket\@\@QEAA\@W4Action\@0\@AEAVActor\@\@\@Z
     */
    MCAPI AnimatePacket(enum class AnimatePacket::Action, class Actor &);

};
/**
 * @file  SetSpawnPositionPacket.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class SetSpawnPositionPacket.
 *
 */
class SetSpawnPositionPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SETSPAWNPOSITIONPACKET
public:
    class SetSpawnPositionPacket& operator=(class SetSpawnPositionPacket const &) = delete;
    SetSpawnPositionPacket(class SetSpawnPositionPacket const &) = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   246096756
     */
    virtual ~SetSpawnPositionPacket();
    /**
     * @vftbl  1
     * @symbol ?getId@SetSpawnPositionPacket@@UEBA?AW4MinecraftPacketIds@@XZ
     * @hash   -718072028
     */
    virtual enum class MinecraftPacketIds getId() const;
    /**
     * @vftbl  2
     * @symbol ?getName@SetSpawnPositionPacket@@UEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
     * @hash   875832785
     */
    virtual std::string getName() const;
    /**
     * @vftbl  3
     * @symbol ?write@SetSpawnPositionPacket@@UEBAXAEAVBinaryStream@@@Z
     * @hash   1577712534
     */
    virtual void write(class BinaryStream &) const;
    /**
     * @vftbl  6
     * @symbol ?_read@SetSpawnPositionPacket@@EEAA?AW4StreamReadResult@@AEAVReadOnlyBinaryStream@@@Z
     * @hash   -1600354170
     */
    virtual enum class StreamReadResult _read(class ReadOnlyBinaryStream &);
    /**
     * @symbol ??0SetSpawnPositionPacket@@QEAA@XZ
     * @hash   1200343638
     */
    MCAPI SetSpawnPositionPacket();
    /**
     * @symbol ??0SetSpawnPositionPacket@@QEAA@W4SpawnPositionType@@V?$AutomaticID@VDimension@@H@@AEBVBlockPos@@@Z
     * @hash   -1416464127
     */
    MCAPI SetSpawnPositionPacket(enum class SpawnPositionType, class AutomaticID<class Dimension, int>, class BlockPos const &);
    /**
     * @symbol ??0SetSpawnPositionPacket@@QEAA@V?$AutomaticID@VDimension@@H@@AEBVBlockPos@@1@Z
     * @hash   -1921192297
     */
    MCAPI SetSpawnPositionPacket(class AutomaticID<class Dimension, int>, class BlockPos const &, class BlockPos const &);

};
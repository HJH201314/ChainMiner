/**
 * @file  ResourcePacksInfoPacket.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "llapi/Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here
#include "PackInfoData.hpp"
#include "PackIdVersion.hpp"

#undef BEFORE_EXTRA

/**
 * @brief MC class ResourcePacksInfoPacket.
 *
 */
class ResourcePacksInfoPacket : public Packet {

#define AFTER_EXTRA
// Add Member There
public:
    bool mTexturePackRequired;
    bool mHasScripts;
    bool mForceServerPacks;
    std::vector<struct PackInfoData> mAddOnPacks;
    std::vector<struct PackInfoData> mTexturePacks;
#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_RESOURCEPACKSINFOPACKET
public:
    class ResourcePacksInfoPacket& operator=(class ResourcePacksInfoPacket const &) = delete;
    ResourcePacksInfoPacket(class ResourcePacksInfoPacket const &) = delete;
#endif

public:
    /**
     * @vftbl  0
     * @symbol  __unk_destructor_0
     */
    virtual ~ResourcePacksInfoPacket();
    /**
     * @hash   -1038576404
     * @vftbl  1
     * @symbol  ?getId\@ResourcePacksInfoPacket\@\@UEBA?AW4MinecraftPacketIds\@\@XZ
     */
    virtual enum class MinecraftPacketIds getId() const;
    /**
     * @hash   -1152135271
     * @vftbl  2
     * @symbol  ?getName\@ResourcePacksInfoPacket\@\@UEBA?AV?$basic_string\@DU?$char_traits\@D\@std\@\@V?$allocator\@D\@2\@\@std\@\@XZ
     */
    virtual std::string getName() const;
    /**
     * @hash   -1644181698
     * @vftbl  3
     * @symbol  ?write\@ResourcePacksInfoPacket\@\@UEBAXAEAVBinaryStream\@\@\@Z
     */
    virtual void write(class BinaryStream &) const;
    /**
     * @hash   944142078
     * @vftbl  6
     * @symbol  ?_read\@ResourcePacksInfoPacket\@\@EEAA?AW4StreamReadResult\@\@AEAVReadOnlyBinaryStream\@\@\@Z
     */
    virtual enum class StreamReadResult _read(class ReadOnlyBinaryStream &);
    /**
     * @hash   220564325
     * @symbol  ??0ResourcePacksInfoPacket\@\@QEAA\@_NAEAV?$vector\@UPackInfoData\@\@V?$allocator\@UPackInfoData\@\@\@std\@\@\@std\@\@10\@Z
     */
    MCAPI ResourcePacksInfoPacket(bool, std::vector<struct PackInfoData> &, std::vector<struct PackInfoData> &, bool);
    /**
     * @hash   -1977854018
     * @symbol  ??0ResourcePacksInfoPacket\@\@QEAA\@XZ
     */
    MCAPI ResourcePacksInfoPacket();

};
/**
 * @file  NBCastleEntrance.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "NetherFortressPiece.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class NBCastleEntrance.
 *
 */
class NBCastleEntrance : public NetherFortressPiece {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NBCASTLEENTRANCE
public:
    class NBCastleEntrance& operator=(class NBCastleEntrance const &) = delete;
    NBCastleEntrance(class NBCastleEntrance const &) = delete;
    NBCastleEntrance() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @hash   1665343692
     */
    virtual ~NBCastleEntrance();
    /**
     * @vftbl  2
     * @symbol ?getType@NBCastleEntrance@@UEBA?AW4StructurePieceType@@XZ
     * @hash   -711081079
     */
    virtual enum class StructurePieceType getType() const;
    /**
     * @vftbl  3
     * @symbol ?addChildren@NBCastleEntrance@@UEAAXAEAVStructurePiece@@AEAV?$vector@V?$unique_ptr@VStructurePiece@@U?$default_delete@VStructurePiece@@@std@@@std@@V?$allocator@V?$unique_ptr@VStructurePiece@@U?$default_delete@VStructurePiece@@@std@@@std@@@2@@std@@AEAVRandom@@@Z
     * @hash   305675287
     */
    virtual void addChildren(class StructurePiece &, std::vector<std::unique_ptr<class StructurePiece>> &, class Random &);
    /**
     * @vftbl  4
     * @symbol ?postProcess@NBCastleEntrance@@UEAA_NAEAVBlockSource@@AEAVRandom@@AEBVBoundingBox@@@Z
     * @hash   597355551
     */
    virtual bool postProcess(class BlockSource &, class Random &, class BoundingBox const &);

};
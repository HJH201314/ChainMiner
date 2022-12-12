/**
 * @file  MineshaftCrossing.hpp
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "MineshaftPiece.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class MineshaftCrossing.
 *
 */
class MineshaftCrossing : public MineshaftPiece {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MINESHAFTCROSSING
public:
    class MineshaftCrossing& operator=(class MineshaftCrossing const &) = delete;
    MineshaftCrossing(class MineshaftCrossing const &) = delete;
    MineshaftCrossing() = delete;
#endif

public:
    /**
     * @vftbl  0
     * @symbol __unk_destructor_0
     */
    virtual ~MineshaftCrossing();
    /**
     * @hash   1144836946
     * @vftbl  2
     * @symbol ?getType@MineshaftCrossing@@UEBA?AW4StructurePieceType@@XZ
     */
    virtual enum StructurePieceType getType() const;
    /**
     * @hash   -1152052546
     * @vftbl  3
     * @symbol ?addChildren@MineshaftCrossing@@UEAAXAEAVStructurePiece@@AEAV?$vector@V?$unique_ptr@VStructurePiece@@U?$default_delete@VStructurePiece@@@std@@@std@@V?$allocator@V?$unique_ptr@VStructurePiece@@U?$default_delete@VStructurePiece@@@std@@@std@@@2@@std@@AEAVRandom@@@Z
     */
    virtual void addChildren(class StructurePiece &, std::vector<std::unique_ptr<class StructurePiece>> &, class Random &);
    /**
     * @hash   -1926352026
     * @vftbl  4
     * @symbol ?postProcess@MineshaftCrossing@@UEAA_NAEAVBlockSource@@AEAVRandom@@AEBVBoundingBox@@@Z
     */
    virtual bool postProcess(class BlockSource &, class Random &, class BoundingBox const &);
    /**
     * @hash   1277716317
     * @symbol ?_placeSupportPillar@MineshaftCrossing@@QEAAXAEAVBlockSource@@AEBVBoundingBox@@HHHH@Z
     */
    MCAPI void _placeSupportPillar(class BlockSource &, class BoundingBox const &, int, int, int, int);

};
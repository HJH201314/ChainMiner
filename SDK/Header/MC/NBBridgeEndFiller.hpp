// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "NetherFortressPiece.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class NBBridgeEndFiller : public NetherFortressPiece {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NBBRIDGEENDFILLER
public:
    class NBBridgeEndFiller& operator=(class NBBridgeEndFiller const &) = delete;
    NBBridgeEndFiller(class NBBridgeEndFiller const &) = delete;
    NBBridgeEndFiller() = delete;
#endif


public:
    /*0*/ virtual ~NBBridgeEndFiller();
    /*2*/ virtual enum StructurePieceType getType() const;
    /*4*/ virtual bool postProcess(class BlockSource &, class Random &, class BoundingBox const &);
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_NBBRIDGEENDFILLER
#endif
    MCAPI static std::unique_ptr<class NetherFortressPiece> createPiece(std::vector<std::unique_ptr<class StructurePiece>> &, class Random &, int, int, int, int, int);



};
#include <Engine/Block.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

Block::Block(const GeometryDefines::Box& rect):
    rect_(rect),
    isNeedCount_(true)
{}



Block::~Block() {}



void Block::setNeedCount(bool isNeedCount) {

    isNeedCount_ = isNeedCount;

}



bool Block::isNeedCount() const {

    return isNeedCount_;

}



GeometryDefines::Box Block::getRect() const {

    return rect_;

}

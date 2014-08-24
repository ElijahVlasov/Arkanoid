#include <Engine/Block.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

Block::Block(const GeometryDefines::Box& rect):
    rect_(rect)
{}



Block::~Block() {}



GeometryDefines::Box Block::getRect() const {

    return rect_;

}

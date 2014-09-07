#include <Engine/Block.hpp>

#include <LuaAPI/Block_wrapper.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

using namespace LuaAPI;

Block_wrapper::Block_wrapper(const GeometryDefines::Box& box):
    Block(box)
{}



bool Block_wrapper::crash() {

    return call<bool>("crash");

}

#include <stdexcept>

#include <Engine/EasyBlock.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/SpriteBuilder.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Graphics;

EasyBlock::EasyBlock(const GeometryDefines::Box& rect) throw(runtime_error):
    Block(rect)
{

    setSprite(SpriteBuilder::createSprite("textures/game/easyblock.png", SpriteBuilder::SpriteType::STATIC));

}



bool EasyBlock::crash() {

    return true;

}

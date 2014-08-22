#include <stdexcept>

#include <Engine/EasyBlock.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Graphics;

EasyBlock::EasyBlock(const GeometryDefines::Box& rect) throw(runtime_error):
    Block(rect)
{

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    texture_ = resourceManager->getResource<Texture>("textures/game/easyblock.png");

}



void EasyBlock::draw() {

    GraphicsManager::DrawTexture(getRect(), *texture_);

}



bool EasyBlock::crash() {

    return true;

}

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/DirectionToCoordsArray.h>
#include <Engine/StaticSprite.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

using namespace Utils;



StaticSprite::StaticSprite(){}



StaticSprite::StaticSprite(const boost::shared_ptr<Texture>& texture):
    texture_(texture)
{}



StaticSprite::~StaticSprite() {}



boost::shared_ptr<Texture> StaticSprite::getTexture() const {

    return texture_;

}



void StaticSprite::setTexture(const boost::shared_ptr<Texture>& texture) {

    texture_ = texture;

}



void StaticSprite::onRender(const GeometryDefines::Point& drawPoint, Direction dir) {

    Graphics::DrawTexture(
        drawPoint,
        *texture_,
        DirectionToCoordsArray(dir)
    );

}



void StaticSprite::onRender(const GeometryDefines::Box& drawBox, Direction dir) {

    Graphics::DrawTexture(
        drawBox,
        *texture_,
        DirectionToCoordsArray(dir)
    );

}

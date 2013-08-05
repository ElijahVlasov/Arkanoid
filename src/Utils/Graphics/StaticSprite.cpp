#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/StaticSprite.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

using namespace Utils;
using namespace Utils::Graphics;



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



void StaticSprite::onRender(const GeometryDefines::Point& point) {

    GraphicsManager::DrawTexture(
        point,
        *texture_
    );

}



void StaticSprite::onRender(const GeometryDefines::Box& box) {

    GraphicsManager::DrawTexture(
        box,
        *texture_
    );

}



void StaticSprite::onRender(const GeometryDefines::Polygon& polygon) {

	GraphicsManager::DrawTexture(
		polygon,
		*texture_
	);

}

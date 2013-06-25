#include <Engine/AnimationSprite.hpp>
#include <Engine/Direction.hpp>

#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

using namespace Utils;



AnimationSprite::AnimationSprite()
{}



AnimationSprite::~AnimationSprite() {}



void AnimationSprite::addFrame(int msDuration, const boost::shared_ptr<Texture>& frame) {

    Frame newFrame = {msDuration, frame};

    frames_.push_back(newFrame);

}



void AnimationSprite::onRender(const GeometryDefines::Box& drawBox, Direction dir) {



}



void AnimationSprite::onRender(const GeometryDefines::Point& drawPoint, Direction dir) {
}

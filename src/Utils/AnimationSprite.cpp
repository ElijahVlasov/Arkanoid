#include <Utils/AnimationSprite.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"


using namespace Utils;



AnimationSprite::AnimationSprite()
{}



AnimationSprite::~AnimationSprite() {}



void AnimationSprite::addFrame(std::chrono::milliseconds msDuration, const boost::shared_ptr<Texture>& frame) {

    Frame newFrame = {msDuration, frame};

    frames_.push_back(newFrame);

}



void AnimationSprite::onRender(const GeometryDefines::Box& box) {



}



void AnimationSprite::onRender(const GeometryDefines::Point& point) {
}



void AnimationSprite::onRender(const GeometryDefines::Polygon& polygon) {

}

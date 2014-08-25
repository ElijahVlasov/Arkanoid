#include <chrono>

#include <Engine/Ball.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/SpriteBuilder.hpp>

#include "geometry_defines.hpp"
#include "salt_defines.h"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Graphics;

const chrono::milliseconds Ball::STEP_TIME = chrono::milliseconds(50);


Ball::Ball(const GeometryDefines::Point& center, float radius, bool isSleep, float speed, const GeometryDefines::Vector2D& direction) throw(runtime_error):
    center_(center),
    radius_(radius),
    isSleep_(isSleep),
    speed_(speed),
    direction_(direction)
{

    setSprite(SpriteBuilder::createSprite(BALL_TEXTURE, SpriteBuilder::SpriteType::STATIC));

}



Ball::~Ball() {}



void Ball::move(float x, float y) {

    center_.x(center_.x() + x);
    center_.y(center_.y() + y);

}



void Ball::update() {

    if(isSleep_) {
        return;
    }

    auto now = chrono::system_clock::now();

    if(now - lastUpdate_ < STEP_TIME) {
        return;
    }

    lastUpdate_ = now;

    center_ = getNextPoint();

}



void Ball::sleep() {

    isSleep_ = true;

}



void Ball::awake() {

    isSleep_ = false;

    lastUpdate_ = chrono::system_clock::now();

}



bool Ball::isSleep() const {

    return isSleep_;

}



void Ball::setRadius(float radius) {

    radius_ = radius;

}



float Ball::getRadius() const {

    return radius_;

}



void Ball::setCenter(const GeometryDefines::Point& center) {

    center_ = center;

}



void Ball::setCenter(float x, float y) {

    center_.x(x);
    center_.y(y);

}



const GeometryDefines::Point & Ball::getCenter() const {

    return center_;

}



GeometryDefines::Box Ball::getRect() const {

    return GeometryDefines::Box(
               GeometryDefines::Point(center_.x() - radius_, center_.y() - radius_),
               GeometryDefines::Point(center_.x() + radius_, center_.y() + radius_)
           );
}



void Ball::setSpeed(float speed) {

    speed_ = speed;

}



float Ball::getSpeed() const {

    return speed_;

}



void Ball::setDirection(const GeometryDefines::Vector2D& direction) {

    direction_ = direction;

}



const GeometryDefines::Vector2D & Ball::getDirection() const {

    return direction_;

}



GeometryDefines::Point Ball::getNextPoint() const {

    GeometryDefines::Point nextCenter;

    float xStep = direction_.x() * speed_;
    float yStep = direction_.y() * speed_;

    nextCenter.x(center_.x() + xStep);
    nextCenter.y(center_.y() + yStep);

    return nextCenter;

}

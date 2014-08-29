#include <cmath>

#include <chrono>

#include <Engine/Ball.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/SpriteFactory.hpp>

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

    setSprite(SpriteFactory::createSprite(BALL_TEXTURE, SpriteFactory::SpriteType::STATIC));

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

    center_ = getNextPoint();

    lastUpdate_ = chrono::system_clock::now();

}



void Ball::sleep() {

    isSleep_ = true;

}



void Ball::awake() {

    isSleep_ = false;

    lastUpdate_ = chrono::system_clock::now();

}



void Ball::rotate(float angle) {

    float currentAngle = getAngle();

    setAngle(currentAngle + angle);

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



void Ball::setAngle(float angle) {

    float radian = (angle / 180) * 3.1415;

    direction_.x(cos(radian));
    direction_.y(sin(radian));

}



float Ball::getAngle() const {

    return (acos(direction_.x()) * 180) / 3.1415;

}



void Ball::setDirection(const GeometryDefines::Vector2D& direction) {

    direction_ = direction;

    float length = direction_.x() * direction_.x() + direction_.y() * direction_.y();

    direction_.x(direction_.x() / length);
    direction_.y(direction_.y() / length);

}



const GeometryDefines::Vector2D & Ball::getDirection() const {

    return direction_;

}



GeometryDefines::Point Ball::getNextPoint() const {

    GeometryDefines::Point nextCenter;

    auto timeDelta = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - lastUpdate_).count();

    float xStep = direction_.x() * speed_ *  (timeDelta / 1000.0f);
    float yStep = direction_.y() * speed_ *  (timeDelta / 1000.0f);

    nextCenter.x(center_.x() + xStep);
    nextCenter.y(center_.y() + yStep);

    return nextCenter;

}

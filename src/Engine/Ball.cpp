#include <cmath>
#include <ctime>

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

const float Ball::STEP = 10.0f;
const chrono::milliseconds Ball::STEP_TIME = chrono::milliseconds(50);


Ball::Ball(const GeometryDefines::Point& center, float radius, bool isSleep, float xSpeed, float ySpeed) throw(runtime_error):
    center_(center),
    radius_(radius),
    isSleep_(isSleep),
    xSpeed_(xSpeed),
    ySpeed_(ySpeed)
{

    setSprite(SpriteBuilder::createSprite(BALL_TEXTURE, SpriteBuilder::SpriteType::STATIC));

    if(xSpeed_ == 0.0f) {

        srand(time(0));
        srand(rand());

        int a = rand() % 80 - 40;

        xSpeed_ = static_cast<float>(a) / 100.0f;

    }

    if(ySpeed_ == 0.0f) {

        ySpeed_ = 1.0f;

    }

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

    float xStep = xSpeed_ * STEP;
    float yStep = ySpeed_ * STEP;

    center_.x(center_.x() + xStep);
    center_.y(center_.y() + yStep);

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



void Ball::setYSpeed(float ySpeed) {

    ySpeed_ = ySpeed;

}



float Ball::getYSpeed() const {

    return ySpeed_;

}



void Ball::setXSpeed(float xSpeed) {

    xSpeed_ = xSpeed;

}



float Ball::getXSpeed() const {

    return xSpeed_;

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

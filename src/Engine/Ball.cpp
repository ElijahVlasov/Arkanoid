#include <Engine/Ball.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"
#include "salt_defines.h"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Graphics;

const float Ball::STEP = 5.0f;


Ball::Ball(const GeometryDefines::Point& center, float radius, bool isSleep, float xSpeed, float ySpeed) throw(runtime_error):
    center_(center),
    radius_(radius),
    isSleep_(isSleep),
    xSpeed_(xSpeed),
    ySpeed_(ySpeed)
{

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    texture_ = resourceManager->getResource<Texture>(BALL_TEXTURE);

    if(xSpeed_ == 0.0f) {

        int a = rand() % 80 - 40;

        xSpeed_ = static_cast<float>(a) / 100.0f;

    }

    if(ySpeed_ == 0.0f) {

        ySpeed_ = 1.0f;

    }

}



void Ball::move(float x, float y) {

    center_.x(center_.x() + x);
    center_.y(center_.y() + y);

}



void Ball::update() {

    if(isSleep_) {
        return;
    }

    float xStep = xSpeed_ * STEP;
    float yStep = ySpeed_ * STEP;

    center_.x(center_.x() + xStep);
    center_.y(center_.y() + yStep);

}



void Ball::draw() {

    GraphicsManager::DrawTexture(
        GeometryDefines::Box(
            GeometryDefines::Point(center_.x() - radius_, center_.y() - radius_),
            GeometryDefines::Point(center_.x() + radius_, center_.y() + radius_)
        ),
        *texture_
    );

}



void Ball::sleep() {

    isSleep_ = true;

}



void Ball::awake() {

    isSleep_ = false;

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

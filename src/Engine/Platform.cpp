#include <mutex>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>
#include <Engine/Platform.hpp>

#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/SpriteBuilder.hpp>

#include "salt_defines.h"

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::Graphics;

Platform::Platform(const GeometryDefines::Box& rect) throw(runtime_error):
    rect_(rect),
    singleGame_(SingleGameState::getInstance())
{

    setSprite(SpriteBuilder::createSprite(PLATFORM_SPRITE, SpriteBuilder::ANIMATION));

}



Platform::~Platform() {}



void Platform::move(Platform::MovingDirection dir, float step) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    float minCornerX, maxCornerX;

    minCornerX = rect_.min_corner().x();
    maxCornerX = rect_.max_corner().x();

    switch(dir) {

        case RIGHT: {

            float worldWidth = singleGame_->getWorldWidth();

            if(maxCornerX > worldWidth - step) {

                step = worldWidth - maxCornerX;

            }

            rect_.min_corner().x(minCornerX + step);
            rect_.max_corner().x(maxCornerX + step);

        }
        break;

        case LEFT: {

            if(minCornerX < step) {

                step = minCornerX;

            }

            rect_.min_corner().x(minCornerX - step);
            rect_.max_corner().x(maxCornerX - step);

        }
        break;

    }

    if(ball_ != 0) {
        ball_->setCenter((rect_.min_corner().x() + rect_.max_corner().x()) / 2.0f,
                          ball_->getCenter().y());
    }


}



void Platform::bindBall(const boost::shared_ptr<Ball>& ball) {

    if(ball == 0) {
        return;
    }

    ball_ = ball;

    ball_->sleep();

    ball_->setCenter((rect_.min_corner().x() + rect_.max_corner().x()) / 2.0f,
                          rect_.max_corner().y() + ball_->getRadius());

}



void Platform::pushBall() {

    if(ball_ == 0) {
        return;
    }

    ball_->awake();

    ball_ = 0;

}



GeometryDefines::Box Platform::getRect() const {

    return rect_;

}

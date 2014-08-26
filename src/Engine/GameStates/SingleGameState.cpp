#include <cmath>

#include <chrono>
#include <stdexcept>

#include <boost/geometry/geometry.hpp>

#include <SDL/SDL_keycode.h>

#include <Engine/Ball.hpp>
#include <Engine/Block.hpp>
#include <Engine/EasyBlock.hpp>
#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>

#include "geometry_defines.hpp"
#include "salt_defines.h"

using namespace std;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;

const std::chrono::milliseconds SingleGameState::LOADING_DURATION = std::chrono::milliseconds(3000);



SingleGameState::SingleGameState() throw(runtime_error):
    game_(Game::getInstance()),
    lua_(Lua::getInstance()),
    menuState_(MenuState::getInstance()),
    audioManager_(AudioManager::getInstance()),
    isPlatformClicked_(false),
    isPaused_(false),
    ballsCount_(3)
{}



void SingleGameState::quit() {

    background_  = 0;
    ball_        = 0;
    musicPlayer_ = 0;
    music_       = 0;

    blocks_.clear();

}



void SingleGameState::onActive() {

    musicPlayer_->play();

    if(ball_ == 0) {
        return;
    }

    if(isPaused_) {

        ball_->awake();

        isPaused_ = false;

    }

}



void SingleGameState::onRemove() {

    musicPlayer_->pause();

    if(ball_ == 0) {
        return;
    }

    ball_->sleep();

    isPaused_ = true;

}



void SingleGameState::showDebugInfo() {}



void SingleGameState::makeScreenshot() {}



void SingleGameState::onRender() {

    GraphicsManager::ClearScreen();

    GraphicsManager::DrawTexture(
        GeometryDefines::BoxI(
            GeometryDefines::PointI(0, 0),
            GeometryDefines::PointI(game_->getScreenWidth(), game_->getScreenHeight())
        ),
        *background_
    );

    platform_->draw();

    for(size_t i = 0; i < blocks_.size(); i++) {

        for(size_t j = 0; j < blocks_[i].size(); j++) {

            if(blocks_[i][j] != 0) {
                blocks_[i][j]->draw();
            }

        }

    }

    if(ball_ != 0) {
        ball_->draw();
    }

    GraphicsManager::DrawTexture(
        GeometryDefines::BoxI(
            GeometryDefines::PointI(0.0f, 450),
            GeometryDefines::PointI(getWorldWidth(), getWorldHeight())
        ),
        *bar_
    );

    for(unsigned int i = 0; i < ballsCount_; i++) {

        GraphicsManager::DrawTexture(
            GeometryDefines::BoxI(
                GeometryDefines::PointI(5 + i * 18, 457),
                GeometryDefines::PointI(5 + i * 18 + 16, 473)
            ),
            *ballIcon_
        );

    }

}



void SingleGameState::onResize(unsigned int width, unsigned int height) {



}



void SingleGameState::onKeyDown(int key) {

	switch(key) {

		case SDLK_ESCAPE: {

            menuState_->setMenu(game_->getPauseMenu());

			game_->setState(menuState_.get());

		}
		break;

		case SDLK_RIGHT: {

		    platform_->move(Platform::MovingDirection::RIGHT);

		}
		break;

		case SDLK_LEFT: {

		    platform_->move(Platform::MovingDirection::LEFT);

		}
		break;

		default: {

		}

	}

}



void SingleGameState::onKeyUp(int key) {

	switch(key) {

		case SDLK_ESCAPE: {
			//game_->setState(menuState_.get());
		}
		break;

		case SDLK_F1: {
			showDebugInfo();
		}
		break;

		case SDLK_F2: {
			makeScreenshot();
		}
		break;

		case SDLK_SPACE: {

            platform_->pushBall();

		}
		break;

		default: {

		}

	}

}



void SingleGameState::onMouseMotion(int x, int y) {

    if(!isPlatformClicked_) {
        return;
    }

    // Расстояние от предыдущего расположения курсора до текущего
    int distance = x - lastMouseX_;

    if(distance < 0) { // Курсор ушел левее

        platform_->move(Platform::MovingDirection::LEFT, -distance);

    } else { // Правее

        platform_->move(Platform::MovingDirection::RIGHT, distance);

    }

    lastMouseX_ = x;

}



void SingleGameState::onMouseDown(int x, int y, MouseButton btn) {

    if(btn != MouseButton::BUTTON_LEFT) {
        return;
    }

    float platformX         = platform_->getRect().min_corner().x();
    float platformY         = platform_->getRect().min_corner().y();
    float platformMaxX      = platform_->getRect().max_corner().x();
    float platformMaxY      = platform_->getRect().max_corner().y();


    if( (static_cast<float>(x) >= platformX) && (static_cast<float>(x) <= platformMaxX) ) {

        if( (static_cast<float>(y) >= platformY) && (static_cast<float>(y) <= platformMaxY) ) { // Если кликнута платформа

            isPlatformClicked_ = true;

            lastMouseX_       = x;

        }

    }

}



void SingleGameState::onMouseUp(int x, int y, MouseButton btn) {

    isPlatformClicked_ = false;

}



void SingleGameState::onLoop() {

    if(ball_ == 0) {
        return;
    }

    if(ball_->isSleep()) {
       return;
    }


    checkBallAndWalls();
    checkBallAndObjects();

    if(ball_ == 0) {
        return;
    }

    ball_->update();

}



void SingleGameState::init() throw(runtime_error) {

    auto startLoading = chrono::system_clock::now();

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    background_  = resourceManager->getResource<Texture>(GAME_BACKGROUND);
    bar_         = resourceManager->getResource<Texture>(GAME_BAR);
    ballIcon_    = resourceManager->getResource<Texture>(BALL_ICON);

    music_       = resourceManager->getResource<Sound>(GAME_MUSIC);
    bounceSound_ = resourceManager->getResource<Sound>(BOUNCE_SOUND);

    musicPlayer_ = audioManager_->createSoundPlayer(music_);

    musicPlayer_->setLooping(true);

    platform_    = boost::shared_ptr<Platform>(
                       new Platform(
                           GeometryDefines::Box(GeometryDefines::Point(220, 10), GeometryDefines::Point(420, 35))
                       )
                   );

    blocks_.resize(10);

    for(size_t i = 0; i < 10; i++) { // Создаем блоки

        for(size_t j = 0; j < 16; j++) {

            blocks_[i].push_back(boost::shared_ptr<Block>(
                                    new EasyBlock(
                                        GeometryDefines::Box(
                                            GeometryDefines::Point(j * 40,      300 + i * 15),
                                            GeometryDefines::Point(j * 40 + 38, 300 + i * 15 + 13)
                                        )
                                    )
                                 ));

        }

    }

    ball_ = boost::shared_ptr<Ball>(new Ball(
                                     GeometryDefines::Point(0.0f, 0.0f),
                                     10.0f, true
                                    )
                                   );

    platform_->bindBall(ball_);

    auto n = chrono::system_clock::now() - startLoading;

    while(n <= LOADING_DURATION) {
        n = chrono::system_clock::now() - startLoading;
    }

}



float SingleGameState::getWorldHeight() const {

    return game_->getScreenHeight();

}



float SingleGameState::getWorldWidth() const {

    return game_->getScreenWidth();

}



void SingleGameState::checkBallAndWalls() {

    if(ball_ == 0) {
        return;
    }

    GeometryDefines::Point    nextPoint = ball_->getNextPoint();
    GeometryDefines::Vector2D direction = ball_->getDirection();

    if(nextPoint.y() + ball_->getRadius() < platform_->getRect().max_corner().y()) { // Мяч достиг нижней границы

        die();

        return;

    } else if(nextPoint.y() + ball_->getRadius() > getWorldHeight() - 30) {

        bounceSound();

        direction.y(-direction.y());

    }

    if( (nextPoint.x() - ball_->getRadius() < 0.0f) ||  (nextPoint.x() + ball_->getRadius() > getWorldWidth())) { // Шар столкнулся с боковыми стенками

        bounceSound();

        direction.x(-direction.x());

    }

    ball_->setDirection(direction);

}



#define IS_IN(N, R1, R2) ( ( (N) >= (R1) ) && ( (N) <= (R2) ) )
void SingleGameState::checkBallAndObjects() {

    if(ball_ == 0) {
        return;
    }

    GeometryDefines::Box   platformRect = platform_->getRect();
    GeometryDefines::Point ballCenter   = ball_->getCenter();
    float diameter = ball_->getRadius();

    //Проверяем положение шарика:

    float platformAreaMinX = platformRect.min_corner().x() - diameter;
    float platformAreaMaxX = platformRect.max_corner().x() + diameter;
    float platformAreaMaxY = platformRect.max_corner().y() + diameter;

    if(IS_IN(ballCenter.x(), platformAreaMinX, platformAreaMaxX)) {

        if( ballCenter.y() <= platformAreaMaxY) { // Если шарик рядом с платформой

            checkBallAndPlatform();

            return;

        }

    }

    if(ballCenter.y() >= 300 - diameter) {

        checkBallAndBlocks();

    }


}



void SingleGameState::checkBallAndPlatform() {

    GeometryDefines::Point      ballNextCenter = ball_->getNextPoint();
    GeometryDefines::Box        platformRect   = platform_->getRect();
    GeometryDefines::Vector2D   direction      = ball_->getDirection();
    GeometryDefines::Point      contact;

    if( !GeometryDefines::boxAndCircleContact(ball_->getRadius(), ballNextCenter, platformRect, contact) ) {
        return;
    }

    bounceSound();

    if(contact.y() == platformRect.max_corner().y()) {

        if(contact.x() == platformRect.min_corner().x()) {

            ball_->setAngle(135.0f);

            direction = ball_->getDirection();

        } else if(contact.x() == platformRect.max_corner().x()) {

            ball_->setAngle(45.0f);

            direction = ball_->getDirection();

        } else {

            direction.y(-direction.y());

        }

    } else if(contact.y() > platformRect.min_corner().y()) {

        direction.x(-direction.x());
        direction.y(-direction.y());

    }

    ball_->setDirection(direction);

}



void SingleGameState::checkBallAndBlocks() {

    GeometryDefines::Point      ballNextCenter = ball_->getNextPoint();
    float                       diameter       = ball_->getRadius() * 2;

    for(size_t i = 0; i < blocks_.size(); i++) {

        for(size_t j = 0; j < blocks_[i].size(); j++) {

            if(blocks_[i][j] == 0) {
                continue;
            }

            GeometryDefines::Box blockRect = blocks_[i][j]->getRect();

            float blockAreaMinX = blockRect.min_corner().x() - diameter;
            float blockAreaMaxX = blockRect.max_corner().x() + diameter;
            float blockAreaMinY = blockRect.min_corner().y() - diameter;
            float blockAreaMaxY = blockRect.max_corner().y() + diameter;

            if( IS_IN(ballNextCenter.x(), blockAreaMinX, blockAreaMaxX) ) {

                if( IS_IN(ballNextCenter.y(), blockAreaMinY, blockAreaMaxY) ) {

                    checkBallAndBlock(blocks_[i][j], ballNextCenter);

                }

            }

        }

    }

}



void SingleGameState::checkBallAndBlock(boost::shared_ptr<Block>& block, const GeometryDefines::Point& ballNextCenter) {

    GeometryDefines::Vector2D direction         = ball_->getDirection();
    GeometryDefines::Box      blockRect         = block->getRect();
    GeometryDefines::Point    contact;

    if( !GeometryDefines::boxAndCircleContact(ball_->getRadius(), ballNextCenter, blockRect, contact) ) {
        return;
    }

    if(contact.x() == blockRect.min_corner().x()) {

        if(contact.y() == blockRect.min_corner().y()) {

            ball_->setAngle(225.0f);

        } else if(contact.y() == blockRect.max_corner().y()) {

            ball_->setAngle(135.0f);

        } else {

            direction.x(-direction.x());

        }

    } else if(contact.x() == blockRect.max_corner().x()) {

        if(contact.y() == blockRect.min_corner().y()) {

            ball_->setAngle(315.0f);

        } else if(contact.y() == blockRect.max_corner().y()) {

            ball_->setAngle(45.0f);

        } else {

            direction.x(-direction.x());

        }

    } else {

        direction.y(-direction.y());

    }

    ball_->setDirection(direction);

    if(block->crash()) {
        block = 0;
    }

}



void SingleGameState::die() {

    if(ballsCount_ == 0) {

        ball_ = 0;

        return;

    }

    ballsCount_--;
    platform_->bindBall(ball_);

}



void SingleGameState::bounceSound() {

    boost::shared_ptr<SoundPlayer> bouncePlayer = audioManager_->createSoundPlayer(bounceSound_);

    bouncePlayer->play();

}

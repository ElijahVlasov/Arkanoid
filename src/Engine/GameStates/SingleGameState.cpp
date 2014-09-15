#include <cmath>

#include <chrono>
#include <list>
#include <stdexcept>

#include <boost/format.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <SDL/SDL_keycode.h>

#include <Engine/Ball.hpp>
#include <Engine/Block.hpp>
#include <Engine/DebugOutput.hpp>
#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils/Color.hpp>
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



SingleGameState::SingleGameState() throw(runtime_error):
    game_(Game::getInstance()),
    lua_(Lua::getInstance()),
    menuState_(MenuState::getInstance()),
    audioManager_(AudioManager::getInstance()),
    isPlatformClicked_(false),
    isWin_(false),
    isPaused_(false)
{}



void SingleGameState::quit() {

    ball_           = 0;
    musicPlayer_    = 0;
    isPaused_       = false;
    loseFont_       = 0;
    winFont_        = 0;
    level_          = 0;
    levelManager_   = 0;

}



void SingleGameState::onActive() {

    musicPlayer_->play();

    if(ball_ == 0) {
        return;
    }

    if(isPaused_) {

        if(platform_->getBall() == 0) {
            ball_->awake();
        }

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



void SingleGameState::printDebugInfo() {

    if(debugOutput_ == 0) {
        return;
    }

    debugOutput_->clear();

    debugOutput_->printf("blocks.count=%u\n", level_->getBlocksCount());

    if(ball_ != 0) {

        debugOutput_->printf("ball.center=(%f;%f)\n",    ball_->getCenter().x(),    ball_->getCenter().y());
        debugOutput_->printf("ball.direction=(%f;%f)\n", ball_->getDirection().x(), ball_->getDirection().y());
        debugOutput_->printf("ball.radius=%f\nball.angle=%f\nball.speed=%f\n", ball_->getRadius(), ball_->getAngle(), ball_->getSpeed());

    }

    debugOutput_->printf("platform.min_corner=(%f;%f)\n", platform_->getRect().min_corner().x(), platform_->getRect().min_corner().y());
    debugOutput_->printf("platform.max_corner=(%f;%f)\n", platform_->getRect().max_corner().x(), platform_->getRect().max_corner().y());

}



void SingleGameState::makeScreenshot() {}



void SingleGameState::onRender() {

    GraphicsManager::ClearScreen();

    level_->draw();

    platform_->draw();

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

    for(unsigned int i = 0; i < ballsCount_; i++) { // Нарисовать оставшиеся шарики

        GraphicsManager::DrawTexture(
            GeometryDefines::BoxI(
                GeometryDefines::PointI(5 + i * 18, 457),
                GeometryDefines::PointI(5 + i * 18 + 16, 473)
            ),
            *ballIcon_
        );

    }

    if(ballsCount_ == 0) {

        loseFont_->renderText("You lost!!!", 100, 100);

    } else if(isWin_) {

        winFont_->renderText("You win!!!", 50, 100);

    }

    if(debugOutput_ != 0) {
        debugOutput_->onRender();
    }

}



void SingleGameState::onResize(unsigned int width, unsigned int height) {



}



void SingleGameState::onKeyDown(int key) {

    if(ballsCount_ == 0) {
        game_->quitGame();
        return;
    }

    if(isWin_) {
        game_->quitGame();
        return;
    }

	switch(key) {

		case SDLK_ESCAPE: {

            menuState_->setMenu(game_->getPauseMenu());

			game_->setState(menuState_.get());

		}
		break;

		case SDLK_F1: {

			if(debugOutput_ == 0) {
                debugOutput_ = boost::shared_ptr<DebugOutput>(new DebugOutput());
			} else {
                debugOutput_ = 0;
			}

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

		case SDLK_c: {

            level_->clear();

		}
		break;

		default: {

		}

	}

}



void SingleGameState::onKeyUp(int key) {}



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

    printDebugInfo();

    if(isWin_) {
        return;
    }

    if(level_->getBlocksCount() == 0) {

        if(!levelManager_->hasNextLevel()) {

            isWin_ = true;

        } else {

            loadingState_ = boost::shared_ptr<LoadingState>(new LoadingState([this](){

                                                                                     this->level_ = this->levelManager_->loadNextLevel();

                                                                                     this->musicPlayer_ = this->audioManager_->createSoundPlayer(this->level_->getSound());
                                                                                     this->musicPlayer_->setLooping(true);

                                                                                     this->platform_->bindBall(ball_);

                                                                                 }, this));

            game_->setState(loadingState_.get());

        }

    }

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

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    bar_            = resourceManager->getResource<Texture>(GAME_BAR);
    ballIcon_       = resourceManager->getResource<Texture>(BALL_ICON);

    bounceSound_    = resourceManager->getResource<Sound>(BOUNCE_SOUND);

    loseFont_       = resourceManager->getResource<Font>(YOU_LOST_FONT);
    winFont_        = resourceManager->getResource<Font>(YOU_WIN_FONT);

    Color loseColor = {1.0f, 0.0f, 0.0f};
    loseFont_->setColor(loseColor);
    loseFont_->setSize(144);

    Color winColor = {0.97f, 0.07f, 0.94f};
    winFont_->setColor(winColor);
    winFont_->setSize(120);

    levelManager_ = boost::shared_ptr<LevelManager>(new LevelManager(LEVELS_FILE));

    level_ = levelManager_->loadNextLevel();

    musicPlayer_ = audioManager_->createSoundPlayer(level_->getSound());

    musicPlayer_->setLooping(true);

    platform_    = boost::shared_ptr<Platform>(
                       new Platform(
                           GeometryDefines::Box(GeometryDefines::Point(270, 10), GeometryDefines::Point(370, 35))
                       )
                   );

    ball_ = boost::shared_ptr<Ball>(new Ball(
                                     GeometryDefines::Point(0.0f, 0.0f),
                                     10.0f, true
                                    )
                                   );

    platform_->bindBall(ball_);

    ballsCount_ = 3;

}



float SingleGameState::getWorldHeight() const {

    return game_->getScreenHeight();

}



float SingleGameState::getWorldWidth() const {

    return game_->getScreenWidth();

}



float SingleGameState::genAngleDelta() {

    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(-5, 5);

    float deltaAngle = dist(gen) / 1.0f;

    return deltaAngle;

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

    if(ballCenter.y() >= level_->getRect().min_corner().y() - diameter) {

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

    float angle = ball_->getAngle();

    angle += genAngleDelta();

    ball_->setAngle(angle);

}



void SingleGameState::checkBallAndBlocks() {

    GeometryDefines::Point      ballNextCenter = ball_->getNextPoint();
    float                       radius         = ball_->getRadius();
    GeometryDefines::Box        ballArea       = ball_->getRect();
    GeometryDefines::Vector2D   direction         = ball_->getDirection();

    ballArea.min_corner().x(ballArea.min_corner().x() - radius);
    ballArea.min_corner().y(ballArea.min_corner().y() - radius);
    ballArea.max_corner().x(ballArea.max_corner().x() + radius);
    ballArea.max_corner().y(ballArea.max_corner().y() + radius);

    list< boost::shared_ptr< Block > > blocks = level_->getBlocksInBox(ballArea);

    if(blocks.empty()) {
        return;
    }

    list< GeometryDefines::Point > contacts;
    list< boost::shared_ptr<Block> > blocksForCrash;

    BOOST_FOREACH(boost::shared_ptr<Block>& block, blocks) {

        GeometryDefines::Box      blockRect         = block->getRect();

        GeometryDefines::Point contact;

        if( !GeometryDefines::boxAndCircleContact(ball_->getRadius(), ballNextCenter, blockRect, contact) ) {
            continue;
        }

        contacts.push_back(contact);
        blocksForCrash.push_back(block);

    }

    if(contacts.empty()) {
        return;
    }

    GeometryDefines::Point contact = contacts.front();
    GeometryDefines::Box blockRect = blocksForCrash.front()->getRect();

    if(contacts.size() > 1) {

        if(contact.x() == blockRect.min_corner().x()) {

            direction.x(-abs(direction.x()));

        } else if(contact.x() == blockRect.max_corner().x()) {

            direction.x(abs(direction.x()));

        } else {

            if(contact.y() == blockRect.min_corner().y()) {

                direction.y(-abs(direction.y()));

            } else {

                direction.y(abs(direction.y()));

            }

        }

    }

    if(contact.x() == blockRect.min_corner().x()) {

        if(contact.y() == blockRect.min_corner().y()) {

            ball_->setAngle(225.0f);
            direction = ball_->getDirection();

        } else if(contact.y() == blockRect.max_corner().y()) {

            ball_->setAngle(135.0f);
            direction = ball_->getDirection();

        } else {

            direction.x(-abs(direction.x()));

        }

    } else if(contact.x() == blockRect.max_corner().x()) {

        if(contact.y() == blockRect.min_corner().y()) {

            ball_->setAngle(315.0f);
            direction = ball_->getDirection();

        } else if(contact.y() == blockRect.max_corner().y()) {

            ball_->setAngle(45.0f);
            direction = ball_->getDirection();

        } else {

            direction.x(abs(direction.x()));

        }

    } else {

        if(contact.y() == blockRect.min_corner().y()) {

            direction.y(-abs(direction.y()));

        } else {

            direction.y(abs(direction.y()));

        }

    }

    ball_->setDirection(direction);

    BOOST_FOREACH(boost::shared_ptr<Block>& block, blocksForCrash) {

        level_->crashBlock(block);

    }

}



void SingleGameState::die() {

    if(--ballsCount_ == 0) {

        ball_ = 0;

        return;

    }

    platform_->bindBall(ball_);

}



void SingleGameState::bounceSound() {

    boost::shared_ptr<SoundPlayer> bouncePlayer = audioManager_->createSoundPlayer(bounceSound_);

    bouncePlayer->play();

}

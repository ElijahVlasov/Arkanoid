#include <chrono>
#include <stdexcept>

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
    isPlatformClicked_(false)
{}



void SingleGameState::quit() {}



void SingleGameState::onActive() {

    musicPlayer_->play();

}



void SingleGameState::onRemove() {

    musicPlayer_->pause();

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

    for(int i = 0; i < 6; i++) {

        for(int j = 0; j < 8; j++) {

            if(blocks_[i][j] != 0) {
                blocks_[i][j]->draw();
            }

        }

    }

    if(ball_ != 0) {
        ball_->draw();
    }

}



void SingleGameState::onResize(unsigned int width, unsigned int height) {



}



void SingleGameState::onKeyDown(int key) {

	switch(key) {

		case SDLK_ESCAPE: {

            /*menuState_->setMenu(game_->getPauseMenu());

			game_->setState(menuState_.get());*/

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

    if(ball_ != 0) {

        ball_->update();

    }

}



void SingleGameState::init() throw(runtime_error) {

    auto startLoading = chrono::system_clock::now();

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();
    SingletonPointer<AudioManager>    audioManager    = AudioManager::getInstance();

    background_  = resourceManager->getResource<Texture>(GAME_BACKGROUND);

    music_       = resourceManager->getResource<Sound>(GAME_MUSIC);

    musicPlayer_ = audioManager->createSoundPlayer(music_);

    musicPlayer_->setLooping(true);

    platform_    = boost::shared_ptr<Platform>(
                       new Platform(
                           GeometryDefines::Box(GeometryDefines::Point(220, 10), GeometryDefines::Point(420, 35))
                       )
                   );

    for(int i = 0; i < 6; i++) { // Создаем блоки

        for(int j = 0; j < 8; j++) {

            blocks_[i][j] = boost::shared_ptr<Block>(
                                new EasyBlock(
                                    GeometryDefines::Box(
                                        GeometryDefines::Point(j * 80,      300 + i * 30),
                                        GeometryDefines::Point(j * 80 + 78, 300 + i * 30 + 28)
                                    )
                                )
                            );

        }

    }

    ball_ = boost::shared_ptr<Ball>(new Ball(
                                     GeometryDefines::Point(0.0f, 0.0f),
                                     20.0f, true
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

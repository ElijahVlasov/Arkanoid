#include <stdexcept>

#include <SDL/SDL_keysym.h>

#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Lua.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/SingletonPointer.hpp>

#include "geometry_defines.hpp"
#include "salt_defines.h"

using namespace std;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::Graphics;


SingleGameState::SingleGameState() throw(runtime_error):
    game_(Game::getInstance()),
    lua_(Lua::getInstance())
{}



void SingleGameState::quit() {}



void SingleGameState::onActive() {}



void SingleGameState::onRemove() {}



void SingleGameState::showDebugInfo() {}



void SingleGameState::makeScreenshot() {}



void SingleGameState::onRender() {

    GraphicsManager::DrawTexture(
        GeometryDefines::BoxI(
            GeometryDefines::PointI(0, 0),
            GeometryDefines::PointI(game_->getScreenWidth(), game_->getScreenHeight())
        ),
        *background_
    );

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

		default: {

		}

	}

}



void SingleGameState::onKeyUp(int key) {

	switch(key) {

		/*case SDLK_ESCAPE: {
			game_->setState(menuState_);
		}
		break;*/

		case SDLK_F1: {
			showDebugInfo();
		}
		break;

		case SDLK_F2: {
			makeScreenshot();
		}
		break;

		default: {

		}

	}

}



void SingleGameState::onMouseMotion(int x, int y) {



}



void SingleGameState::onMouseDown(int x, int y, MouseButton btn) {



}



void SingleGameState::onMouseUp(int x, int y, MouseButton btn) {



}



void SingleGameState::init() throw(runtime_error) {

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    background_ = resourceManager->getResource<Texture>(GAME_BACKGROUND);



}

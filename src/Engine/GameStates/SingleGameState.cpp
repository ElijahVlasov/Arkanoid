#include <stdexcept>

#include <SDL/SDL_keysym.h>

#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils/Lua.hpp>

using namespace std;

using namespace Engine;

using namespace Engine::GameStates;

using namespace Utils;



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

//	renderer_->onRender();

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

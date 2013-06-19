#include <stdexcept>

//#include <SDL/SDL_keysym.h>

#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>

#include <Utils.hpp>

using namespace std;

using namespace Engine;

using namespace Engine::GameStates;

using namespace Utils;



SingleGameState::SingleGameState() throw(runtime_error):
	game_(Game::getInstance()),
	lua_(Lua::getInstance()),
	menuState_(MenuState::getInstance())
{}



SingleGameState::~SingleGameState() {

	if(game_ != 0) {
		game_->Free();
	}

	if(lua_ != 0) {
		lua_->Free();
	}

	if(menuState_ != 0) {
		menuState_->Free();
	}

}



void SingleGameState::showDebugInfo() {}



void SingleGameState::makeScreenshot() {}



void SingleGameState::onRender() {

//	renderer_->onRender();

}



void SingleGameState::onResize(unsigned int width, unsigned int height) {



}



void SingleGameState::onKeyDown(int key) {

	/*switch(static_cast<SDLKey>(key)) {

		case SDLK_ESCAPE: {
			game_->setState(menuState_);
		}
		break;

		default: {
			
		}

	}*/

}



void SingleGameState::onKeyUp(int key) {

	/*switch(static_cast<SDLKey>(key)) {

		case SDLK_ESCAPE: {
			game_->setState(menuState_);
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

		default: {
			
		}

	}*/

}



void SingleGameState::onMouseMotion(int x, int y) {



}



void SingleGameState::onMouseDown(int x, int y, MouseButton btn) {



}



void SingleGameState::onMouseUp(int x, int y, MouseButton btn) {



}

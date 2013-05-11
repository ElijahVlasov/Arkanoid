#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <boost/interprocess/shared_memory_object.hpp>

#include <stdexcept>

#include <Engine/Game.hpp>
#include <Engine/GameStates/IGameState.hpp>

#include <Utils/MouseButton.hpp>

using namespace boost::interprocess;
using namespace std;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;



Game::Game():
	state_(0)
{}



Game::~Game() {}



void Game::onRender() {

	if(state_ != 0) {
		state_->onRender();
	}

}



void Game::onKeyDown(int key) {

	if(state_ != 0) {
		state_->onKeyDown(key);
	}

}



void Game::onKeyUp(int key) {

	if(state_ != 0) {
		state_->onKeyUp(key);
	}

}



void Game::onMouseMotion(int x, int y) {

	if(state_ != 0) {
		state_->onMouseMotion(x, y);
	}

}



void Game::onMouseDown(int x, int y, MouseButton btn) {

	if(state_ != 0) {
		state_->onMouseDown(x, y, btn);
	}

}



void Game::onMouseUp(int x, int y, MouseButton btn) {

	if(state_ != 0) {
		state_->onMouseUp(x, y, btn);
	}

}



void Game::setScreenRect(unsigned int width, unsigned int height) {
	
	scrHeight_	=	height;
	scrWidth_	=	width;

}



int Game::getScreenHeight() const {
	
	return scrHeight_;

}



int Game::getScreenWidth() const {
	
	return scrWidth_;

}



const IGameState* Game::getState() const {

	return state_;

}



void Game::setState(IGameState* state) {

	state_ = state;

}



void Game::setRunning(bool isRunning) {

	isRunning_ = isRunning;

}



bool Game::isRunning() const {

	return isRunning_;

}

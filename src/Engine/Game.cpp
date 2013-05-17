#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexcept>
#include <thread>

#include <Engine/Game.hpp>
#include <Engine/GameStates.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/MouseButton.hpp>

using namespace std;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;



Game::Game() throw(runtime_error):
    graphics_(Graphics::getInstance()),
    scrWidth_(640),
    scrHeight_(480)
{

    graphics_->setViewportSize(scrWidth_, scrHeight_);

}



Game::~Game() {

    if(graphics_ != 0) {
        graphics_->Free();
    }

}



Game* Game::Create() throw(runtime_error) {

    Game* game = getInstance();

    game->startLogoState_  =  StartLogoState::getInstance();
    game->menuGameState_   =  MenuState::getInstance();
    game->singleGameState_ =  SingleGameState::getInstance();

    game->setState(game->startLogoState_);

    return game;   

}



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
	
    scrHeight_ =  height;
    scrWidth_  =  width;

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



void Game::run() {

  //  thread initThread();

    isRunning_ = true;

    

}



void Game::quit() {

    isRunning_ = false;

}



bool Game::isRunning() const {

    return isRunning_;

}



void Game::loadingThread() {

    menuGameState_ = MenuState::getInstance();

}

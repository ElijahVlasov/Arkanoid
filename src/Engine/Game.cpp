#include <stdexcept>
#include <thread>

#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>
#include <Engine/GameStates.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/MouseButton.hpp>

#include <Utils/UI/Menu.hpp>
#include <Utils/UI/MenuFactory.hpp>


using namespace std;

using namespace boost;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::UI;


Game::Game() throw(runtime_error):
    menuFactory_(MenuFactory::getInstance()),
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

    if(menuFactory_ != 0) {
        menuFactory_->Free();
    }

}



Game* Game::Create() throw(runtime_error) {

    Game* game = getInstance();

    // Создаем состояние, которое будет показывать лого
    game->startLogoState_  =  StartLogoState::getInstance();

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



void Game::run() throw(runtime_error) {

    // Запускаем загрузку ресурсов
    initThread_ =  new std::thread(mem_fn(&Game::loadResources), this);

    isRunning_ = true;

    

}



void Game::quit() {

    isRunning_ = false;

}



bool Game::isRunning() const {

    return isRunning_;

}



// Загрузка ресурсов
void Game::loadResources() throw(runtime_error) {

    // Загружаем главное меню
    mainMenu_ = boost::shared_ptr<Menu>(menuFactory_->createFromXML("main_menu.xml"));

    menuGameState_    =  MenuState::getInstance();
    singleGameState_  =  SingleGameState::getInstance();

    menuGameState_->setMenu(mainMenu_);

    

}

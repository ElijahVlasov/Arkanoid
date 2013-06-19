#include <exception>
#include <mutex>
#include <stdexcept>
#include <thread>

#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Game.hpp>
#include <Engine/GameStates.hpp>

#include <LuaAPI.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>

#include <Utils/UI/Menu.hpp>
#include <Utils/UI/MenuFactory.hpp>


using namespace std;

using namespace boost;

using namespace Engine;
using namespace Engine::GameStates;

using namespace LuaAPI;

using namespace Utils;
using namespace Utils::UI;


Game::Game() throw(runtime_error):
    lua_(Lua::getInstance()),
    resourceManager_(ResourceManager::getInstance()),
    menuFactory_(MenuFactory::getInstance()),
    graphics_(Graphics::getInstance()),
    scrWidth_(640),
    scrHeight_(480)
{

    graphics_->setViewportSize(scrWidth_, scrHeight_);

}



Game::~Game() {

    if(lua_ != 0) {
        lua_->Free();
    }

    if(luaAPI_ != 0) {
        luaAPI_->Free();
    }

    if(graphics_ != 0) {
        graphics_->Free();
    }

    if(menuFactory_ != 0) {
        menuFactory_->Free();
    }

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

}



Game* Game::Create(Utils::ResourceLoader* resourceLoader) throw(runtime_error) {

    Game* game = getInstance();

    game->luaAPI_ = LuaAPI_::getInstance();

    game->resourceManager_->setResourceLoader(resourceLoader);

    // Создаем состояние, которое будет показывать лого
    game->startLogoState_  =  StartLogoState::getInstance();

    game->setState(game->startLogoState_);

    return game;

}



void Game::onLoop() throw(std::exception) {

    exception_ptr e = getException();

    if(e != 0) {
        rethrow_exception(e);
    }

}



void Game::onRender() {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onRender();
    }

}



void Game::onKeyDown(int key) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onKeyDown(key);
    }

}



void Game::onKeyUp(int key) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onKeyUp(key);
    }

}



void Game::onMouseMotion(int x, int y) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onMouseMotion(x, y);
    }

}



void Game::onMouseDown(int x, int y, MouseButton btn) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onMouseDown(x, y, btn);
    }

}



void Game::onMouseUp(int x, int y, MouseButton btn) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onMouseUp(x, y, btn);
    }

}



void Game::setScreenRect(unsigned int width, unsigned int height) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    scrHeight_ =  height;
    scrWidth_  =  width;

}



int Game::getScreenHeight() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return scrHeight_;

}



int Game::getScreenWidth() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return scrWidth_;

}



const IGameState* Game::getState() const {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    return state_;

}



void Game::setState(IGameState* state) {

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    state_ = state;

}



void Game::run() throw(runtime_error) {

    isRunning_ = true;

    // Запускаем загрузку ресурсов
    initThread_ =  new std::thread(boost::mem_fn(&Game::loadResources), this);

    initThread_->detach();

}



void Game::quit() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    isRunning_ = false;

}



bool Game::isRunning() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return isRunning_;

}



void Game::setException(const std::exception_ptr& e) {

    std::lock_guard<std::mutex> guard(exceptionCheckMutex_);

    e_ = e;

}



const std::exception_ptr& Game::getException() {

    std::lock_guard<std::mutex> guard(exceptionCheckMutex_);

    return e_;

}



// Загрузка ресурсов
void Game::loadResources() {

    // Загружаем главное меню

    try {

        std::lock_guard<std::mutex> guard(initMutex_);

        loadMainMenu();

        //mainMenu_ = boost::shared_ptr<Menu>();

        menuGameState_    =  MenuState::getInstance();
        singleGameState_  =  SingleGameState::getInstance();

        menuGameState_->setMenu(mainMenu_);

        lua_->loadScript("init.lua");

        luabind::call_function<void>(lua_->getFunctionObject("init.load_resources"));

        setState(menuGameState_);

    } catch(...) {

        setException(current_exception());

    }

}



void Game::loadMainMenu() throw(runtime_error) {

    boost::shared_ptr<Resource> menuResource = resourceManager_->getResource(ResourceLoader::ResourceType::PLAIN_TEXT, "ui/main_menu.xml");

    string menuXML = menuResource->getData();

    Menu* mainMenu = menuFactory_->createFromXML(menuXML);

    mainMenu_ = boost::shared_ptr<Menu>(mainMenu);

    Color menuColor = {0.5f, 0.5f, 0.5f, 0.0f};

    mainMenu_->setBackgroundColor(menuColor);

}

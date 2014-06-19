#include <chrono>
#include <exception>
#include <mutex>
#include <stdexcept>
#include <thread>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Game.hpp>
#include <Engine/GameStates.hpp>

#include <LuaAPI.hpp>

#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/TextureManager.hpp>

#include <Utils/UI/Menu.hpp>
#include <Utils/UI/MenuBuilder.hpp>

#include "salt_defines.h"

using namespace std;

using namespace boost;

using namespace Engine;
using namespace Engine::GameStates;

using namespace LuaAPI;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;
using namespace Utils::UI;


const std::chrono::milliseconds Game::START_LOGO_DURATION = std::chrono::milliseconds(2300);


Game::Game() throw(runtime_error):
    audioManager_(AudioManager::getInstance()),
    lua_(Lua::getInstance()),
    resourceManager_(ResourceManager::getInstance()),
    menuBuilder_(MenuBuilder::getInstance()),
    graphicsManager_(GraphicsManager::getInstance()),
    textureManager_(TextureManager::getInstance()),
    scrWidth_(640),
    scrHeight_(480),
    state_(0)
{

    graphicsManager_->setViewportSize(scrWidth_, scrHeight_);

    //luabind::set_pcall_callback(luaErrorHandler);

}



Game::~Game() {}



Game* Game::Create() throw(runtime_error) {

    Game* game = getInstance();

    // Создаем состояние, которое будет показывать лого
    game->startLogoState_  =  StartLogoState::getInstance();

    game->setState(game->startLogoState_.get());

    return game;

}



void Game::onLoop() throw(std::exception) {

    textureManager_->update();

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

    std::lock_guard<std::mutex> stateGuard(stateAccessMutex_);

    if(state_ != 0) {
        state_->onResize(width, height);
    }

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

    if(state == state_) {
        return;
    }

    std::lock_guard<std::mutex> guard(stateAccessMutex_);

    if(state_ != 0) {
       state_->onRemove();
    }

    state_ = state;

    if(state_ != 0) {
        state_->onActive();
    }

}



void Game::run() throw(runtime_error) {

    isRunning_          = true;
    isAudioThreadNeed_  = true;

    // Запускаем загрузку ресурсов
    initThread_ =  boost::shared_ptr<std::thread>(new std::thread([this] () {
        this->loadResources();
    }));

    initThread_->detach();

    audioThread_ =  boost::shared_ptr<std::thread>(new std::thread([this] () {
        this->audioThread();
    }));

    audioThread_->detach();

}



void Game::quit() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    isRunning_ = false;

    setAudioThreadNeed(false);

}



bool Game::isRunning() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return isRunning_;

}



void Game::startGame(const char* worldName) {

    singleGameState_ = SingleGameState::getInstance();

    setState(singleGameState_.get());

}



void Game::startGame(const string& worldName) {

    startGame(worldName.c_str());

}



void Game::quitGame() {

    if(singleGameState_ != 0) {

        singleGameState_->quit();

        singleGameState_ = 0;

    }

}



boost::shared_ptr<Menu> Game::getPauseMenu() const {

    return mainMenu_;

}



boost::shared_ptr<Menu> Game::getMainMenu() const {

    return pauseMenu_;

}



void Game::setAudioThreadNeed(bool isNeed) {

    std::lock_guard<std::mutex> guard(audioMutex_);

    isAudioThreadNeed_ = isNeed;

}



bool Game::isAudioThreadNeed() const {

    std::lock_guard<std::mutex> guard(audioMutex_);

    return isAudioThreadNeed_;

}



void Game::setException(const std::exception_ptr& e) {

    std::lock_guard<std::mutex> guard(exceptionCheckMutex_);

    e_ = e;

}



const std::exception_ptr& Game::getException() {

    std::lock_guard<std::mutex> guard(exceptionCheckMutex_);

    return e_;

}



void Game::audioThread() {

    SingletonPointer<AudioManager> audioManager = AudioManager::getInstance();

    while(isAudioThreadNeed()) {

        audioManager->update();

    }

}



// Загрузка ресурсов
void Game::loadResources() {

    // Загружаем главное меню

    try {

        std::lock_guard<std::mutex> guard(initMutex_);

        auto startLoading = chrono::system_clock::now();

        luaAPI_ = LuaAPI_::getInstance();

        menuGameState_    =  MenuState::getInstance();
        //singleGameState_  =  SingleGameState::getInstance();

        lua_->loadScript("init.lua");

        luabind::call_function<void>(lua_->getFunctionObject("init.load_resources"));

        loadMainMenu();
        loadPauseMenu();

        menuGameState_->setMenu(mainMenu_);

        auto n = chrono::system_clock::now() - startLoading;

        while(n <= START_LOGO_DURATION) {
            n = chrono::system_clock::now() - startLoading;
        }

        setState(menuGameState_.get());

        startLogoState_ = 0;

    } catch(...) {

        setException(current_exception());

    }

}



void Game::loadMainMenu() throw(runtime_error) {

    string menuXML = resourceManager_->getFileData(MAIN_MENU);

    Menu* mainMenu = menuBuilder_->createMenu(menuXML);

    mainMenu_ = boost::shared_ptr<Menu>(mainMenu);

    Color menuColor = {0.5f, 0.5f, 0.5f, 0.0f};

    mainMenu_->setBackgroundColor(menuColor);

}



void Game::loadPauseMenu() throw(runtime_error) {

    string menuXML = resourceManager_->getFileData(PAUSE_MENU);

    Menu* pauseMenu = menuBuilder_->createMenu(menuXML);

    pauseMenu_ = boost::shared_ptr<Menu>(pauseMenu);

    Color menuColor = {0.5f, 0.5f, 0.5f, 0.0f};

    pauseMenu_->setBackgroundColor(menuColor);

}



int Game::luaErrorHandler(lua_State* L) {

    lua_Debug debug;

    lua_getstack(L, 1, &debug);
    lua_getinfo(L, "ln", &debug);

    string err = lua_tostring(L, -1);

    lua_pop(L, 1);

    string errMsg = (boost::format("Error in Lua function: %1%:%2%:\n\"%3%\"")
                        % debug.name
                        % debug.currentline
                        % err
                     ).str();

    lua_pushstring(L, errMsg.c_str());

    return 1;

}

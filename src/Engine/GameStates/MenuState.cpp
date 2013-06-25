#include <cstddef>

#include <mutex>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>

#include <Utils/assert.hpp>

#include <Utils/UI.hpp>

using namespace std;

using namespace Engine;

using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::UI;



MenuState::MenuState() throw(runtime_error):
    game_(),
    menu_()
{}



void MenuState::setMenu(const boost::shared_ptr<Menu>& menu) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    menu_ = menu;

    menu_->setRect(0, 0, game_->getScreenWidth(), game_->getScreenHeight());

}



const boost::shared_ptr<Menu>&
    MenuState::getMenu() const {

    return menu_;

}



void MenuState::onRender() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->draw();
    }

}



void MenuState::onResize(unsigned int width, unsigned int height) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->setRect(0, 0, width, height);
    }

}



void MenuState::onKeyDown(int key) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->keyDown(key);
    }

}



void MenuState::onKeyUp(int key) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->keyUp(key);
    }

}



void MenuState::onMouseMotion(int x, int y) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->hoverMouse(x, y);
    }

}



void MenuState::onMouseDown(int x, int y, Utils::MouseButton btn) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->mouseDown(x, y, btn);
    }

}



void MenuState::onMouseUp(int x, int y, Utils::MouseButton btn) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(menu_ != 0) {
        menu_->mouseUp(x, y, btn);
    }

}

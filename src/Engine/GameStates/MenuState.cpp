#include <cstddef>

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/MenuState.hpp>

#include <Utils/assert.hpp>

#include <Utils/UI.hpp>

using namespace std;

using namespace Engine;

using namespace Engine::GameStates;

using namespace Utils::UI;



MenuState::MenuState() throw(runtime_error):
	game_(Game::getInstance()),
	menu_()
{}



MenuState::~MenuState() {

	if(game_ != 0) {
		game_->Free();
	}

}



void MenuState::setMenu(const boost::shared_ptr<Menu>& menu) throw(invalid_argument) {

	menu_ = menu;

}



const boost::shared_ptr<Menu>& 
	MenuState::getMenu() const {

	return menu_;

}



void MenuState::onRender() {

	if(menu_ != 0) {
		menu_->draw();
	}

}



void MenuState::onResize(unsigned int width, unsigned int height) {

	if(menu_ != 0) {
		menu_->setRect(0, 0, width, height);
	}

}



void MenuState::onKeyDown(int key) {

	if(menu_ != 0) {
		menu_->keyDown(key);
	}

}



void MenuState::onKeyUp(int key) {

	if(menu_ != 0) {
		menu_->keyUp(key);
	}

}



void MenuState::onMouseMotion(int x, int y) {

	if(menu_ != 0) {
		menu_->hoverMouse(x, y);
	}

}



void MenuState::onMouseDown(int x, int y, Utils::MouseButton btn) {

	if(menu_ != 0) {
		menu_->mouseDown(x, y, btn);
	}

}



void MenuState::onMouseUp(int x, int y, Utils::MouseButton btn) {

	if(menu_ != 0) {
		menu_->mouseUp(x, y, btn);
	}

}

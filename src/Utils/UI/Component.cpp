#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/function.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/FreeType.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>
#include <Utils/UI/KeyEvent.hpp>
#include <Utils/UI/MouseEvent.hpp>

#include "salt_defines.h"
#include "geometry_defines.hpp"

using namespace GeometryDefines;

using namespace Utils::FreeType;

using namespace Utils::UI;

using namespace std;



Component::Component() throw(runtime_error):
    box_(PointI(0, 0), PointI(0, 0)),
    mouseDownX_(-100),
    mouseDownY_(-100),
    isHovered_(false)
{

    try {

    	SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

        boost::shared_ptr<Resource> fontResource = resourceManager->getResource(ResourceManager::ResourceType::FONT, DEFAULT_FONT);

        font_ = *(boost::dynamic_pointer_cast<Font>(fontResource));

    } catch(const bad_cast&) {}

}



Component::~Component() {}



void Component::setRect(int x, int y, unsigned int width, unsigned int height) {

    box_.min_corner().x(x);
    box_.min_corner().y(y);

    box_.max_corner().x(x + width);
    box_.max_corner().y(y + height);

}



int Component::getX() const {

    return box_.min_corner().x();

}



int Component::getY() const {

    return box_.min_corner().y();

}



unsigned int Component::getWidth() const {

    return box_.max_corner().x() - box_.min_corner().x();

}



unsigned int Component::getHeight() const {

    return box_.max_corner().y() - box_.min_corner().y();

}



const BoxI& Component::getBoxI() const {

    return box_;

}



void Component::setText(const char* text) {

    if(text == 0) {

        text_ = "";

    } else {

        text_ = text;

    }

}



void Component::setText(const string& text) {

    text_ = text;

}



const string& Component::getText() const {

    return text_;

}



void Component::setName(const char* name) {

    if(name == 0) {

        name_ = "";

    } else {

        name_ = name;

    }

}



void Component::setName(const string& name) {

    setName(name.c_str());

}



const string& Component::getName() const {

    return name_;

}



void Component::setFont(const Font& font) {

    font_ = font;

}



Font& Component::getFont() {

    return font_;

}



const Font& Component::getFont() const {

    return font_;

}



bool Component::isContains(int x, int y) {

	// TODO: Найти стандартные бустовские функции вместо этого.

	if( ( x >= box_.min_corner().x() )
			&& ( x <= box_.max_corner().x() ) ) {

		if( ( y >= box_.min_corner().y() )
				&& ( y <= box_.max_corner().y() ) ) {

			return true;

		}

	}

    return false;

}




// Все событийные методы преобразовывают аргументы в
// Event структуры и вызывают обработчики.

void Component::mouseDown(int x, int y, Utils::MouseButton btn) {

    if(!isContains(x, y)) {
        return;
    }


    if(btn == Utils::BUTTON_LEFT) { // сохраним координаты, на случай, если это был клик.

        mouseDownX_ = x;
        mouseDownY_ = y;

    }

    try {

        MouseEvent event;

        event.x            =  x - box_.min_corner().x();
        event.y            =  y - box_.min_corner().y();
        event.mouseButton  =  btn;

        mouseDownEvent_(this, event);

    } catch(const boost::bad_function_call&) {}


}



void Component::mouseUp(int x, int y, Utils::MouseButton btn) {

    if(!isContains(x, y)) {
        return;
    }

    try {

        MouseEvent event;

        event.x            =  x - box_.min_corner().x();
        event.y            =  y - box_.min_corner().y();
        event.mouseButton  =  btn;

        mouseUpEvent_(this, event);

    } catch(const boost::bad_function_call&) {}

    if(btn != Utils::BUTTON_LEFT) {
        return;
    }


    if((mouseDownX_ == x)
        || (mouseDownY_ == y)) { // если был клик.

            click(x - box_.min_corner().x(), y - box_.min_corner().y());

    }

}



void Component::click(int x, int y) {

    if(!isContains(x, y)) {
        return;
    }

    try {

        MouseEvent event;

        event.x            =  x - box_.min_corner().x();
        event.y            =  y - box_.min_corner().y();
        event.mouseButton  =  MouseButton::BUTTON_LEFT;

        clickEvent_(this, event);

    } catch(const boost::bad_function_call&) {}


}



void Component::mouseMotion(int x, int y) {

    if(!isContains(x, y)) {

        if(isHovered_) {

            isHovered_ = false;

            mouseLeave(x, y);

        }

        return;

    }

    isHovered_ = true;

    mouseHover(x, y);


}



void Component::mouseHover(int x, int y) {

    try {

        MouseEvent event;

        event.x            =  x - box_.min_corner().x();
        event.y            =  y - box_.min_corner().y();
        event.mouseButton  =  MouseButton::BUTTON_NONE;

        hoverEvent_(this, event);

    } catch(const boost::bad_function_call&) {}

}



void Component::mouseLeave(int x, int y) {

    try {

        MouseEvent event;

        event.x             =   x;
        event.y             =   y;
        event.mouseButton   =   MouseButton::BUTTON_NONE;

        isHovered_ = false;

        leaveEvent_(event);

    } catch (const boost::bad_function_call&){}

}



void Component::draw() {

    try {

        Event event;

        drawEvent_(this, event);

    } catch(const boost::bad_function_call&) {}

}



void Component::keyDown(int key) {

    try {

        KeyEvent event;

        event.key = key;

        keyDownEvent_(this, event);

    } catch(const boost::bad_function_call&) {}

}



void Component::keyUp(int key) {

    try {

        KeyEvent event;

        event.key = key;

        keyUpEvent_(this, event);

    } catch(const boost::bad_function_call&) {}

}



void Component::setHoveredEvent(const Component::MouseHoverEvent& eventHandler) {

    hoverEvent_ = eventHandler;

}



void Component::setMouseLeavedEvent(const Component::MouseLeaveEvent& eventHandler) {

    leaveEvent_ = eventHandler;

}



void Component::setClickedEvent(const Component::MouseClickEvent& eventHandler) {

    clickEvent_ = eventHandler;

}



void Component::setMouseDownEvent(const Component::MouseDownEvent& eventHandler) {

    mouseDownEvent_ = eventHandler;

}



void Component::setMouseUpEvent(const Component::MouseUpEvent& eventHandler) {

    mouseUpEvent_ = eventHandler;

}



void Component::setDrawEvent(const Component::DrawEvent& eventHandler) {

    drawEvent_ = eventHandler;

}



void Component::setKeyDownEvent(const Component::KeyDownEvent& eventHandler) {

    keyDownEvent_ = eventHandler;

}



void Component::setKeyUpEvent(const Component::KeyUpEvent& eventHandler) {

    keyUpEvent_ = eventHandler;

}

#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils.hpp>

#include <Utils/UI/Component.hpp>

#include "config.h"

using namespace Utils::FreeType;

using namespace Utils::UI;

using namespace std;



Component::Component() throw(runtime_error):
    resourceManager_(ResourceManager::getInstance()),
    x_(0),
    y_(0),
    width_(0),
    height_(0)
{

    try {

        boost::shared_ptr<Resource> fontResource = resourceManager_->getResource(ResourceLoader::ResourceType::FONT, DEFAULT_FONT);

        font_ = *(boost::dynamic_pointer_cast<Font>(fontResource).get());

    } catch(const bad_cast&) {}

}



Component::~Component() {

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

}



void Component::setRect(int x, int y, unsigned int width, unsigned int height) {
	
    x_       =  x;
    y_       =  y;
    width_   =  width;
    height_  =  height;

}



int Component::getX() const {

    return x_;

}



int Component::getY() const {

    return y_;

}



unsigned int Component::getWidth() const {
	
    return width_;

}



unsigned int Component::getHeight() const {

    return height_;

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



Font Component::getFont() const {

    return font_;

}



bool Component::isContains(int x, int y) {

    if((x >= x_)
        || (x <= x_ + static_cast<int>(width_))) {

            if((y >= y_)
                || (y <= y_ + static_cast<int>(height_))) {
                    return true;
            }

    }

    return false;

}




// Обработка событий происходит так:
// пытаемся вызвать нужный event.
// если не удается, то не делаем 
// ни чего.

void Component::mouseDown(int x, int y, Utils::MouseButton btn) {

    if(btn == Utils::BUTTON_LEFT) { // если, потенциально, происходит клик
            // сохраняем координаты
            mouseDownX_ = x;
            mouseDownY_ = y;
	
    }

    try {

        MouseEvent event;
		
        event.x            =  x;
        event.y            =  y;
        event.mouseButton  =  btn;

        mouseDownEvent_(event);

    } catch(const boost::bad_function_call&) {}


}



void Component::mouseUp(int x, int y, Utils::MouseButton btn) {

    try {

        MouseEvent event;
		
        event.x            =  x;
        event.y            =  y;
        event.mouseButton  =  btn;

        mouseUpEvent_(event);

    } catch(const boost::bad_function_call&) {}


    // если, потенциально, не произошел клик,
    if(btn != Utils::BUTTON_LEFT) { // то выходим из метода
        return;
    }

		
    if((mouseDownX_ == x)
        || (mouseDownY_ == y)) { // иначе вызываем метод клика
	
            click(x, y);

    }

}



void Component::click(int x, int y) {

    try {

        MouseEvent event;
		
        event.x            =  x;
        event.y            =  y;
        event.mouseButton  =  MouseButton::BUTTON_LEFT;

        clickEvent_(event);

    } catch(const boost::bad_function_call&) {}


}



void Component::hoverMouse(int x, int y) {

    try {

        MouseEvent event;
		
        event.x            =  x;
        event.y            =  y;
        event.mouseButton  =  MouseButton::BUTTON_NONE;

        hoverEvent_(event);

    } catch(const boost::bad_function_call&) {}


}



void Component::draw() {

    try {

        Event event;

        drawEvent_(event);

    } catch(const boost::bad_function_call&) {}

}



void Component::keyDown(int key) {

    try {

        KeyEvent event;

        event.key = key;

        keyDownEvent_(event);

    } catch(const boost::bad_function_call&) {}

}



void Component::keyUp(int key) {

    try {

        KeyEvent event;

        event.key = key;

        keyUpEvent_(event);

    } catch(const boost::bad_function_call&) {}

}



void Component::setHoveredEvent(const Component::MouseHoverEvent& eventHandler) {

    hoverEvent_ = eventHandler;

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

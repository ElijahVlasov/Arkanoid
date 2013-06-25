#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/function.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/FreeType.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/ResourceManager.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>
#include <Utils/UI/KeyEvent.hpp>
#include <Utils/UI/MouseEvent.hpp>

#include "config.h"
#include "geometry_defines.hpp"

using namespace GeometryDefines;

using namespace Utils::FreeType;

using namespace Utils::UI;

using namespace std;



Component::Component() throw(runtime_error):
    resourceManager_(ResourceManager::getInstance()),
    box_(PointI(0, 0), PointI(0, 0))
{

    try {

        boost::shared_ptr<Resource> fontResource = resourceManager_->getResource(ResourceManager::ResourceType::FONT, DEFAULT_FONT);

        font_ = *(boost::dynamic_pointer_cast<Font>(fontResource));

    } catch(const bad_cast&) {}

}



Component::~Component() {

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

}



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

    return false;/*boost::geometry::overlaps(PointI(x, y), box_)*/;

}




// Îáðàáîòêà ñîáûòèé ïðîèñõîäèò òàê:
// ïûòàåìñÿ âûçâàòü íóæíûé event.
// åñëè íå óäàåòñÿ, òî íå äåëàåì
// íè ÷åãî.

void Component::mouseDown(int x, int y, Utils::MouseButton btn) {

    if(btn == Utils::BUTTON_LEFT) { // åñëè, ïîòåíöèàëüíî, ïðîèñõîäèò êëèê
            // ñîõðàíÿåì êîîðäèíàòû
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


    // åñëè, ïîòåíöèàëüíî, íå ïðîèçîøåë êëèê,
    if(btn != Utils::BUTTON_LEFT) { // òî âûõîäèì èç ìåòîäà
        return;
    }


    if((mouseDownX_ == x)
        || (mouseDownY_ == y)) { // èíà÷å âûçûâàåì ìåòîä êëèêà

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

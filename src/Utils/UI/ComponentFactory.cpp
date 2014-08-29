#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <tinyxml.h>

#include <Utils/FreeType.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/UI.hpp>

#include <Utils/UI/ComponentFactory.hpp>

#include "salt_defines.h"

using namespace std;

using namespace Utils::FreeType;
using namespace Utils::UI;



const std::string ComponentFactory::BUTTON_TYPE     =   "button";
const std::string ComponentFactory::LABEL_TYPE      =   "label";
const std::string ComponentFactory::PICTURE_TYPE    =   "picture";



ComponentFactory::ComponentFactory():
	localizationManager_(LocalizationManager::getInstance()),
    resourceManager_(ResourceManager::getInstance())
{}



Component* ComponentFactory::createComponent(const TiXmlElement* element) throw(invalid_argument, runtime_error) {

    ASSERT(
        (element != 0),
        invalid_argument("element")
    );

    Component* component;

    string elementType = element->ValueStr();

    const char*     textKey    	=   element->GetText();
    string 			text		=	localizationManager_->getString(textKey);

    // Создаем нужный объект
    if(elementType == BUTTON_TYPE) {

        component = new Button();
        component->setText(text);

    } else if(elementType == LABEL_TYPE) {

        component = new Label();
        component->setText(text);

    } else if(elementType == PICTURE_TYPE) {

        component = new Picture(text);

    } else {

        string errMsg = (boost::format("Failed to create UI-element \"%1%\".")
            % elementType).str();

        throw(runtime_error(errMsg));

    }

    // задаем свойства объекта
    setXMLAttributes(element, component);

    return component;

}



void ComponentFactory::setXMLAttributes(const TiXmlElement* element, Component* component) throw(runtime_error) {

    if(component == 0) {
        return;
    }

    if(element == 0) {
        return;
    }

    int             x,          y;
    unsigned int    width,      height;
    string          fontName,   componentName;
    unsigned int    fontSize;

    // загружаем свойства объекта
    x               =   getXMLAttribute<int>(element, "x", 0);
    y               =   getXMLAttribute<int>(element, "y", 0);
    width           =   static_cast<unsigned int>(getXMLAttribute<int>(element, "width", 100));
    height          =   static_cast<unsigned int>(getXMLAttribute<int>(element, "height", 100));

    fontName        =   getXMLAttribute<string>(element, "font", DEFAULT_FONT);
    fontSize        =   static_cast<unsigned int>(getXMLAttribute<int>(element, "font_size", 12));
    componentName   =   getXMLAttribute<string>(element, "name");

    component->setRect(x, y, width, height);

    try {

        boost::shared_ptr<Font> font = resourceManager_->getResource<Font>(fontName);

        font->setSize(fontSize);

        component->setFont(*font);

    } catch(const invalid_argument&) {}
      catch(const bad_cast&) {}

    component->setName(componentName);

    // задаем луашные обработчики
    setLuaHandlers(element, component);

}



void ComponentFactory::setLuaHandlers(const TiXmlElement* element, Component* component) throw(runtime_error) {

    string          clickEvent, hoverEvent, leavedEvent, mouseMotionEvent, mouseDownEvent, mouseUpEvent, drawEvent, keyDownEvent, keyUpEvent;

    clickEvent      =   getXMLAttribute<string>(element, "on_click");
    mouseMotionEvent=   getXMLAttribute<string>(element, "on_mouse_motion");
    hoverEvent      =   getXMLAttribute<string>(element, "on_hover");
    leavedEvent     =   getXMLAttribute<string>(element, "on_leave");

    mouseDownEvent  =   getXMLAttribute<string>(element, "on_mouse_down");
    mouseUpEvent    =   getXMLAttribute<string>(element, "on_mouse_up");

    drawEvent       =   getXMLAttribute<string>(element, "on_draw");

    keyDownEvent    =   getXMLAttribute<string>(element, "on_key_down");
    keyUpEvent      =   getXMLAttribute<string>(element, "on_key_up");

    // Устанавливаем обработчики. Имя функции-обработчика может быть
    // неправильным, тогда генерируется invalid_argument, просто
    // игнорируем это событие.
    try {

        component->setClickedEvent      (ComponentEvent_wrapper<MouseEvent>(clickEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setMouseMotionEvent  (ComponentEvent_wrapper<MouseEvent>(mouseMotionEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setHoveredEvent      (ComponentEvent_wrapper<Event>(hoverEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setLeavedEvent      (ComponentEvent_wrapper<Event>(leavedEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setMouseDownEvent    (ComponentEvent_wrapper<MouseEvent>(mouseDownEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setMouseUpEvent      (ComponentEvent_wrapper<MouseEvent>(mouseUpEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setDrawEvent         (ComponentEvent_wrapper<Event>(drawEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setKeyDownEvent      (ComponentEvent_wrapper<KeyEvent>(keyDownEvent));

    } catch (const invalid_argument&) {}

    try {

        component->setKeyUpEvent        (ComponentEvent_wrapper<KeyEvent>(keyUpEvent));

    } catch (const invalid_argument&) {}

}



template<typename T> T ComponentFactory::getXMLAttribute(const TiXmlElement* element, const char* attrName) throw(runtime_error) {

    return getXMLAttribute<T>(element, string(attrName));

}



template<typename T> T ComponentFactory::getXMLAttribute(const TiXmlElement* element, const char* attrName, const T& defValue) throw(runtime_error) {

    return getXMLAttribute<T>(element, string(attrName), defValue);

}



template<typename T> T ComponentFactory::getXMLAttribute(const TiXmlElement* element, const string& attrName) throw(runtime_error) {

    return getXMLAttribute<T>(element, attrName, T());

}



template<typename T> T ComponentFactory::getXMLAttribute(const TiXmlElement* element, const string& attrName, const T& defValue) throw(runtime_error) {

    T attr;

    int err = element->QueryValueAttribute<T>(attrName, &attr);

    ASSERT(
        (err != TIXML_WRONG_TYPE),
        runtime_error(
            (boost::format("UI element attribute \"%1%\" has wrong type")
                % attrName
            ).str()
        )
    );

    if(err == TIXML_NO_ATTRIBUTE) {
        attr = defValue;
    }

    return attr;

}

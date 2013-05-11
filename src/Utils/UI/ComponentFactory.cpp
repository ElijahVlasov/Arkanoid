#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>

#include <lua/lua.hpp>
#include <luabind/luabind.hpp>

#include <TinyXML/tinyxml.h>

#include <Utils.hpp>

#include <Utils/UI/ComponentFactory.hpp>

using namespace std;

using namespace Utils::FreeType;
using namespace Utils::UI;



const std::string ComponentFactory::BUTTON_TYPE		=	"button";
const std::string ComponentFactory::LABEL_TYPE		=	"label";



Component* ComponentFactory::createFromXMLElement(const TiXmlElement* element) throw(invalid_argument, runtime_error) {

	ASSERT(
		(element != 0),
		invalid_argument("element")
	);

	Component* component;

	string elementType = element->ValueStr();

	// Создаем нужный объект
	if(elementType == BUTTON_TYPE) {

		component = new Button();

	} else if(elementType == LABEL_TYPE) {
	
		component = new Label();

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

	int				x,			y;
	unsigned int	width,		height;
	const char*		text	=	element->GetText();
	string			fontName,	componentName;

	// загружаем свойства объекта
	x				=	getXMLAttribute<int>(element, "x", 0);
	y				=	getXMLAttribute<int>(element, "y", 0);
	width			=	static_cast<unsigned int>(getXMLAttribute<int>(element, "width", 100));
	height			=	static_cast<unsigned int>(getXMLAttribute<int>(element, "height", 100));

	fontName		=	getXMLAttribute<string>(element, "font", "arial.ttf");
	componentName	=	getXMLAttribute<string>(element, "name");

	component->setRect(x, y, width, height);

	try {

		component->setFont(Font(fontName));

	} catch(const invalid_argument&) {}

	component->setName(componentName);
	component->setText(text);

	// задаем луашные обработчики
	setLuaHandlers(element, component);

}



void ComponentFactory::setLuaHandlers(const TiXmlElement* element, Component* component) throw(runtime_error) {

	string			clickEvent, hoverEvent, mouseDownEvent, mouseUpEvent, drawEvent, keyDownEvent, keyUpEvent;

	clickEvent		=	getXMLAttribute<string>(element, "onClick");
	hoverEvent		=	getXMLAttribute<string>(element, "onHover");
	mouseDownEvent	=	getXMLAttribute<string>(element, "onMouseDown");
	mouseUpEvent	=	getXMLAttribute<string>(element, "onMouseUp");

	drawEvent		=	getXMLAttribute<string>(element, "onDraw");
	
	keyDownEvent	=	getXMLAttribute<string>(element, "onKeyDown");
	keyUpEvent		=	getXMLAttribute<string>(element, "onKeyUp");

	// Устанавливаем обработчики. Имя функции-обработчика может быть
	// неправильным, тогда генерируется invalid_argument, просто
	// игнорируем это событие.
	try {

		component->setClickedEvent		(ComponentEvent_wrapper<MouseEvent>(clickEvent));

	} catch (const invalid_argument&) {} 

	try {

		component->setHoveredEvent		(ComponentEvent_wrapper<MouseEvent>(hoverEvent));

	} catch (const invalid_argument&) {} 

	try {

		component->setMouseDownEvent	(ComponentEvent_wrapper<MouseEvent>(mouseDownEvent));

	} catch (const invalid_argument&) {} 

	try {

		component->setMouseUpEvent		(ComponentEvent_wrapper<MouseEvent>(mouseUpEvent));

	} catch (const invalid_argument&) {} 

	try {

		component->setDrawEvent			(ComponentEvent_wrapper<Event>(drawEvent));

	} catch (const invalid_argument&) {} 

	try {
		
		component->setKeyDownEvent		(ComponentEvent_wrapper<KeyEvent>(keyDownEvent));

	} catch (const invalid_argument&) {} 

	try {

		component->setKeyUpEvent		(ComponentEvent_wrapper<KeyEvent>(keyUpEvent));

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

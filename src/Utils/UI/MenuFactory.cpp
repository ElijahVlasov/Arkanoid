#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <TinyXML/tinyxml.h>

#include <Utils.hpp>

#include <Utils/UI/MenuFactory.hpp>

using namespace std;
using namespace boost;
using namespace Utils::UI;



const std::string MenuFactory::MENU_ROOT_NODE_VALUE = "menu";



MenuFactory::MenuFactory() throw(runtime_error):
	componentFactory_(ComponentFactory::getInstance())
{}



MenuFactory::~MenuFactory() {

	if(componentFactory_ != 0) {
		componentFactory_->Free();
	}

}



Menu* MenuFactory::createFromXML(const char* fileName) throw(invalid_argument, runtime_error) {

	ASSERT(
		(fileName != 0),
		invalid_argument("fileName")
	);

	ASSERT(
		(strlen(fileName) != 0),
		invalid_argument("fileName")
	);

	curXMLFileName_ = fileName;

	Menu* menu = new Menu();

	TiXmlDocument doc(fileName);

	ASSERT(
		doc.LoadFile(),
		runtime_error((boost::format("Failed to load file \"%1%\".") % fileName).str())
	);

	loadComponents(doc, menu);

	return menu;

}



Menu* MenuFactory::createFromXML(const string& fileName) throw(invalid_argument, runtime_error) {

	return createFromXML(fileName.c_str());

}



void MenuFactory::loadComponents(TiXmlDocument& document, Menu* menu) throw(runtime_error) {

	TiXmlElement* rootElement = document.RootElement();

	ASSERT(
		(rootElement != 0),
		runtime_error(
			(boost::format("%1%: document hasn't root element") 
				% curXMLFileName_ 
			).str()
		)
	);

	ASSERT(
		(rootElement->ValueStr() == MENU_ROOT_NODE_VALUE),
		runtime_error(
			(boost::format("%1%: Root node of menu document must have \"%2%\" value")
				% curXMLFileName_
				% MENU_ROOT_NODE_VALUE
			).str()
		)
	);

	// проходим по всем node'ам, если это элементы,
	// то создаем компонент
	for(TiXmlNode* node = rootElement->FirstChild(); node != 0; node = node->NextSibling()) {
	
		TiXmlElement* uiElement = node->ToElement();

		if(uiElement == 0) {
			continue;
		}

		Component* component = 0;

		try {

			component = componentFactory_->createFromXMLElement(uiElement);

		} catch(const runtime_error& err) {

			throw(runtime_error(
				(boost::format("%1%: %2%") 
					% curXMLFileName_
					% err.what()
				).str()
			));

		} catch(const invalid_argument&) {}

		if(component == 0) {
			continue;
		}

		menu->addComponent(boost::shared_ptr<Component>(component));

	}

}

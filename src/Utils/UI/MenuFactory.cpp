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



Menu* MenuFactory::createFromXML(const char* xmlMenu) throw(invalid_argument, runtime_error) {

    ASSERT(
        (xmlMenu != 0),
        invalid_argument("xmlMenu")
    );

    ASSERT(
        (strlen(xmlMenu) != 0),
        invalid_argument("xmlMenu")
    );

    Menu* menu = new Menu();

    TiXmlDocument doc;

    doc.Parse(xmlMenu);

    ASSERT(
        !doc.Error(),
        runtime_error(doc.ErrorDesc())
    );

    loadComponents(doc, menu);

    return menu;

}



Menu* MenuFactory::createFromXML(const string& xmlMenu) throw(invalid_argument, runtime_error) {

    return createFromXML(xmlMenu.c_str());

}



void MenuFactory::loadComponents(TiXmlDocument& document, Menu* menu) throw(runtime_error) {

    TiXmlElement* rootElement = document.RootElement();

    ASSERT(
        (rootElement != 0),
        runtime_error("Document hasn't root element")
    );

    ASSERT(
        (rootElement->ValueStr() == MENU_ROOT_NODE_VALUE),
        runtime_error(
            (boost::format("Root node of menu document must have \"%1%\" value")
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

        } catch(const invalid_argument&) {}

        if(component == 0) {
            continue;
        }

        menu->addComponent(boost::shared_ptr<Component>(component));

    }

}

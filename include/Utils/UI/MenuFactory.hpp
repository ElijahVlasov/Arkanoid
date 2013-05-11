/******************************************

	

*******************************************/

#ifndef _SALT2D_UTILS_UI_MENUBUILDER_HPP
#define _SALT2D_UTILS_UI_MENUBUILDER_HPP

#include <fstream>
#include <stdexcept>
#include <string>

#include <TinyXML/tinyxml.h>

#include <Utils.hpp>

#include <Utils/UI/Menu.hpp>

namespace Utils {

	namespace UI {
	
		class MenuFactory: public Utils::Singleton<MenuFactory> {

			SINGLETON(MenuFactory)

			public:

				// Создать Menu из XML документа,
				// если fileName == 0 или fileName - пустая 
				// строка, то генерируется invalid_argument
				Utils::UI::Menu* createFromXML(const char* fileName)			
									throw(std::invalid_argument, std::runtime_error);
				Utils::UI::Menu* createFromXML(const std::string& fileName)	
									throw(std::invalid_argument, std::runtime_error);
				

			protected:

				MenuFactory() throw(std::runtime_error);
				~MenuFactory();

			private:

				ComponentFactory* componentFactory_;

				static const std::string MENU_ROOT_NODE_VALUE;

				std::string curXMLFileName_;

				// загружаем компоненты из XML-документа, если
				void loadComponents(TiXmlDocument& document, Utils::UI::Menu* menu) throw(std::runtime_error);				

		};

	}

}

#endif
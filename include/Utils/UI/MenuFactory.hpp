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
    
        /** Фабрика, создающая меню.
          * @author Elijah Vlasov
        */
	
		class MenuFactory: public Utils::Singleton<MenuFactory> {

			SINGLETON(MenuFactory)

			public:

                /** Создать меню из XML-документа.
                  * @param fileName XML-документ
                  * @throw Генерирует std::invalid_argument, если
                  *        fileName == NULL или fileName - пустая строка.
                  *        Генерирует std::runtime_error, если невозможно
                  *        открыть файл или произошла ошибка парсинга.
                */
            
				Utils::UI::Menu* createFromXML(const char* fileName)			
									throw(std::invalid_argument, std::runtime_error);
                                    
                /** Создать меню из XML-документа.
                  * @param fileName XML-документ
                  * @throw Генерирует std::invalid_argument, если fileName - пустая
                  *        строка. Генерирует std::runtime_error, если невозможно
                  *        открыть файл или произошла ошибка парсинга.
                */
                                    
				Utils::UI::Menu* createFromXML(const std::string& fileName)	
									throw(std::invalid_argument, std::runtime_error);
				

			protected:

				MenuFactory() throw(std::runtime_error);
				~MenuFactory();

			private:

				ComponentFactory* componentFactory_;

				static const std::string MENU_ROOT_NODE_VALUE;

				std::string curXMLFileName_;

				// Загрузить menu из TiXml document
				void loadComponents(TiXmlDocument& document, Utils::UI::Menu* menu) throw(std::runtime_error);				

		};

	}

}

#endif
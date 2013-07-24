#ifndef _SALT2D_UTILS_UI_MENUBUILDER_HPP
#define _SALT2D_UTILS_UI_MENUBUILDER_HPP

#include <fstream>
#include <stdexcept>
#include <string>

#include <tinyxml.h>

#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/UI/ComponentBuilder.hpp>
#include <Utils/UI/Menu.hpp>

namespace Utils {

    namespace UI {

        /** Класс для создания меню.
          * @author Elijah Vlasov
        */

        class MenuBuilder: public Utils::Singleton<MenuBuilder> {

            SINGLETON(MenuBuilder)

            public:

                /** Создать меню из XML.
                  * @param xmlMenu XML-меню
                  * @throw Генерирует std::invalid_argument, если
                  *        xmlMenu == NULL или xmlMenu - пустая строка.
                  *        Генерирует std::runtime_error, если произошла ошибка парсинга.
                */

                Menu* createMenu(const char* xmlMenu)
                                    throw(std::invalid_argument, std::runtime_error);

                /** Создать меню из XML.
                  * @param xmlMenu XML-меню
                  * @throw Генерирует std::invalid_argument, если xmlMenu - пустая
                  *        строка. Генерирует std::runtime_error, если произошла ошибка парсинга.
                */

                Menu* createMenu(const std::string& xmlMenu)
                                    throw(std::invalid_argument, std::runtime_error);


            protected:

                MenuBuilder() throw(std::runtime_error);

            private:

                Utils::SingletonPointer<ResourceManager>    resourceManager_;

                Utils::SingletonPointer<ComponentBuilder>   componentBuilder_;

                static const std::string MENU_ROOT_NODE_VALUE;

                // Загрузить menu из TiXml document
                void loadComponents(TiXmlDocument& document, Utils::UI::Menu* menu) throw(std::runtime_error);

        };

    }

}

#endif

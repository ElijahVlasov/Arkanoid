#ifndef _SALT2D_UTILS_UI_COMPONENTFACTORY_HPP
#define _SALT2D_UTILS_UI_COMPONENTFACTORY_HPP

#include <stdexcept>
#include <string>

#include <boost/intrusive_ptr.hpp>

#include <tinyxml.h>

#include <Utils/LocalizationManager.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {

        /** Класс для создания компонентов.
          * @author Elijah Vlasov
        */

        class ComponentFactory: public Utils::Singleton<ComponentFactory> {

            SINGLETON(ComponentFactory)

            public:

                /** Создать компонент из XML-элемента.
                  * @param element XML-элемент
                  * @throw Генерирует std::invalid_argument, если
                  *        element == NULL. Генерирует std::runtime_error,
                  *        если произошли ошибки парсинга или другие.
                */

                Component* createComponent(const TiXmlElement* element)
                                                    throw(std::invalid_argument, std::runtime_error);

            protected:

                ComponentFactory();

            private:

                static const std::string BUTTON_TYPE;
                static const std::string LABEL_TYPE;
                static const std::string PICTURE_TYPE;

                Utils::SingletonPointer<ResourceManager> 		resourceManager_;

                void setXMLAttributes(const TiXmlElement* element, Component* component)
                                                    throw(std::runtime_error);

                void setLuaHandlers(const TiXmlElement* element, Component* component)
                                                    throw(std::runtime_error);

                template<typename T> T getXMLAttribute(const TiXmlElement* element, const char* attrName)
                                                    throw(std::runtime_error);

                template<typename T> T getXMLAttribute(const TiXmlElement* element, const std::string& attrName)
                                                    throw(std::runtime_error);

                template<typename T> T getXMLAttribute(const TiXmlElement* element, const char* attrName, const T& defValue)
                                                    throw(std::runtime_error);

                template<typename T> T getXMLAttribute(const TiXmlElement* element, const std::string& attrName, const T& defValue)
                                                    throw(std::runtime_error);

        };

    }

}

#endif

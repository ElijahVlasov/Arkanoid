#ifndef _SALT2D_UTILS_RESOURCELOADER_HPP
#define _SALT2D_UTILS_RESOURCELOADER_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Resource.hpp>

namespace Utils {

    /** Загрузчик ресурсов.
      * Унифицирует доступ к ресурсам на разных ОС.
      * Потомки должны определять load* методы, для загрузки
      * каждого из типов ресурсов.
      * @author Elijah Vlasov
    */

    class ResourceLoader {

        public:

            /** Тип ресурса.
            */

            enum ResourceType {

                TEXTURE     = 0,        /**< Текстура(только PNG)     */
                SOUND       = 1,        /**< Файл звуков(только OGG)  */
                FONT        = 2,        /**< Шрифт                    */
                PLAIN_TEXT  = 3,        /**< Текстовый файл           */
                BINARY_FILE = 4         /**< Двоичный файл            */

            };

            /** Загрузить ресурс.
              * @param resourceType Тип ресурса
              * @param resourceName Имя ресурса
              * @throws Генерирует std::invalid_argument, если resourceName == NULL или
              *         resourceName - пустая строка. Генерирует std::runtime_error при
              *         ошибках загрузки ресурса.
            */

            boost::shared_ptr<Resource> loadResource(ResourceType resourceType, const char* resourceName)
                                                        throw(std::invalid_argument, std::runtime_error);

            /** Загрузить ресурс.
              * @param resourceType Тип ресурса
              * @param resourceName Имя ресурса
              * @throws Генерирует std::invalid_argument, если resourceName - пустая строка.
              *         Генерирует std::runtime_error при ошибках загрузки ресурса.
            */

            virtual boost::shared_ptr<Resource> loadResource(ResourceType resourceType, const std::string& resourceName)
                                                        throw(std::invalid_argument, std::runtime_error);

        protected:

            virtual boost::shared_ptr<Resource> loadSound(const char* fileName)      throw(std::runtime_error) = 0;
            virtual boost::shared_ptr<Resource> loadTexture(const char* fileName)    throw(std::runtime_error) = 0;
            virtual boost::shared_ptr<Resource> loadFont(const char* fileName)       throw(std::runtime_error) = 0;
            virtual boost::shared_ptr<Resource> loadPlainText(const char* fileName)  throw(std::runtime_error) = 0;
            virtual boost::shared_ptr<Resource> loadBinaryFile(const char* fileName) throw(std::runtime_error) = 0;

    };

}

#endif

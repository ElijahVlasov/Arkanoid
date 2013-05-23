#ifndef _SALT2D_UTILS_RESOURCE_HPP
#define _SALT2D_UTILS_RESOURCE_HPP

#include <string>

namespace Utils {

    /** Интерфейс для всех ресурсов.
      * @author Elijah Vlasov
    */

    class Resource {

        public:

            /** Получить данные ресурса.
            */

            virtual const std::string& getData() const    = 0;

            /** Установить данные ресурса.
            */

            virtual void setData(const std::string& data) = 0;

    };

}

#endif

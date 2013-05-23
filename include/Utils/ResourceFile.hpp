#ifndef _SALT2D_UTILS_PALINTEXT_HPP
#define _SALT2D_UTILS_PALINTEXT_HPP

#include <string>

#include <Utils/Resource.hpp>

namespace Utils {

    /** Ресурс файла.
      * @author Elijah Vlasov
    */

    class ResourceFile: public Resource {

        public:

            ~ResourceFile();

            std::string getData() const;
            void setData(const std::string& data);

        private:

            std::string text_;

    };

}

#endif

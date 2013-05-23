#ifndef _SALT2D_UTILS_PALINTEXT_HPP
#define _SALT2D_UTILS_PALINTEXT_HPP

#include <string>

#include <Utils/Resource.hpp>

namespace Utils {

    /** Ресурс текстового файла.
      * @author Elijah Vlasov
    */

    class PlainText: public Resource {

        public:

            const std::string& getData() const;
            void setData(const std::string& data);

        private:

            std::string text_;

    };

}

#endif

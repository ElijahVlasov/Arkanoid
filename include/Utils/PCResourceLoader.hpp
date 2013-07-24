#ifndef _SALT2D_UTILS_PCRESOURCELOADER_HPP
#define _SALT2D_UTILS_PCRESOURCELOADER_HPP

#include <istream>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>

namespace Utils {

    /** Загрузчик ресурсов для ПК.
      * @author Elijah Vlasov
    */

    class PCResourceLoader: public Singleton<PCResourceLoader>,
                                public ResourceLoader {

        SINGLETON(PCResourceLoader)

        public:

            std::string readFile(const char* fileName) throw(std::invalid_argument, std::runtime_error);


    };

}

#endif

#ifndef _SALT2D_ENGINE_PCCLIENT_HPP
#define _SALT2D_ENGINE_PCCLIENT_HPP

#include <stdexcept>

#include <Engine/Client.hpp>
#include <Engine/Package.hpp>

namespace Engine {

    class PCClient: public Client {
    
        public:

            PCClient();
            ~PCClient();

            void connect(const char* address) throw(std::invalid_argument, std::runtime_error);

            void sendPackage(const Package& package) throw(std::runtime_error);

    };

}

#endif
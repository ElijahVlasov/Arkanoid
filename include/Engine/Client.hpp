#ifndef _SALT2D_ENGINE_CLIENT_HPP
#define _SALT2D_ENGINE_CLIENT_HPP

#include <stdexcept>
#include <string>

#include <boost/utility.hpp>

#include <Engine/Package.hpp>

namespace Engine {

    class Connection: public boost::noncopyable {

        public:

            virtual ~Client() = 0;

            virtual void connect(const char* address) throw(std::invalid_argument, std::runtime_error) = 0;
            inline void connect(const std::string& address) throw(std::invalid_argument, std::runtime_error);

            virtual void sendPackage(const Package& package) throw(std::runtime_error) = 0;


    };

    void Connection::connect(const std::string& address) throw(std::invalid_argument, std::runtime_error) {
    
        connect(address.c_str());

    }

}

#endif
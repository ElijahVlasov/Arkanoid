#ifndef _SALT2D_SERVER_HPP
#define _SALT2D_SERVER_HPP

#include <boost/utility.hpp>

class Server: public boost::noncopyable {

    public:

        Server(int argc, char* argv[]);
        ~Server();

        int run();

    private:

        

};

#endif

#ifndef _SALT2D_ENGINE_ENGINE_HPP
#define _SALT2D_ENGINE_ENGINE_HPP

#include <mutex>
#include <thread>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>

#include <Engine/Game.hpp>

namespace Engine {

    class SaltEngine: public Utils::Singleton<SaltEngine> {

        SINGLETON(SaltEngine)

        public:

            

            void run();

        protected:

            SaltEngine();
            virtual ~SaltEngine();

            //friend boost::thread;

        private:

            std::thread   engineThread;

            void operator() ();

            Utils::Lua*     lua_;

    };

}



#endif

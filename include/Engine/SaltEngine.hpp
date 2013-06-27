#ifndef _SALT2D_ENGINE_ENGINE_HPP
#define _SALT2D_ENGINE_ENGINE_HPP

#include <list>
#include <mutex>
#include <thread>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>
#include <Engine/Object.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {

    class SaltEngine: public Utils::Singleton<SaltEngine> {

        SINGLETON(SaltEngine)

        public:

            void run();

            std::list<ObjectPtr> getActiveObjects();

        protected:

            SaltEngine();
            ~SaltEngine();

            friend class std::thread;

        private:

            boost::shared_ptr<std::thread>   engineThread_;

            void engineLoop();

            boost::intrusive_ptr<Utils::Lua>     lua_;

    };

}



#endif

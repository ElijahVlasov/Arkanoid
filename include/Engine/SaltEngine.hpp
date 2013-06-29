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

            bool isCollision(const ObjectPtr& obj1, const ObjectPtr& obj2);

        protected:

            SaltEngine();
            ~SaltEngine();

            friend class std::thread;

        private:

            static const float COLLISION_RADIUS;

            boost::shared_ptr<std::thread>   engineThread_;

            void engineLoop();

            std::list<ObjectPtr> getNearObjects(const ObjectPtr& obj);

            boost::intrusive_ptr<Utils::Lua>     lua_;

    };

}



#endif

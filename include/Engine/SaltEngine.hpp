#ifndef _SALT2D_ENGINE_ENGINE_HPP
#define _SALT2D_ENGINE_ENGINE_HPP

#include <list>
#include <mutex>
#include <thread>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <Engine/Game.hpp>
#include <Engine/Object.hpp>
#include <Engine/World.hpp>

#include <Utils/Lua.hpp>
#include <Utils/SingletonPointer.hpp>

namespace Engine {

    class SaltEngine: public boost::noncopyable {

        public:

            SaltEngine(const WorldPtr& world);
            ~SaltEngine();

            void run();
            void stop();

            std::list<ObjectPtr> getActiveObjects();

            bool isCollision(const ObjectPtr& obj1, const ObjectPtr& obj2);

        private:

            static const float COLLISION_RADIUS;

            void engineLoop();

            std::list<ObjectPtr> getNearObjects(const ObjectPtr& obj);

            inline bool isRunning() const;

            boost::shared_ptr<std::thread>   engineThread_;

            mutable std::mutex synchroMutex_;
            mutable std::mutex isRunningAccessMutex_;

            bool isRunning_;

            WorldPtr world_;

            Utils::SingletonPointer<Utils::Lua>     lua_;

    };



    bool SaltEngine::isRunning() const {

        std::lock_guard<std::mutex> guard(isRunningAccessMutex_);

        return isRunning_;

    }

}



#endif

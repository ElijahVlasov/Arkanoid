#ifndef _SALT2D_ENGINE_WORLD_HPP
#define _WORLD_HPP

#include <list>
#include <mutex>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include "World.pb.h"

namespace Engine {

    class World: public Object {

        public:

            World();
            World(const EngineData::World&);

            void setName(const char* name);
            void setName(const std::string& name);
            const std::string& getName() const;

        private:

            mutable std::mutex synchroMutex_;

    };

}


#endif

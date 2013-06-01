#ifndef _SALT2D_ENGINE_WORLD_HPP
#define _WORLD_HPP

#include <list>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include "World.pb.h"

namespace Engine {

    class World: public Object {

        public:

            typedef boost::shared_ptr<Object> ObjectPtr;

            World();
            World(const EngineData::World&);

    };

}


#endif

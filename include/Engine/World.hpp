#ifndef _SALT2D_ENGINE_WORLD_HPP
#define _WORLD_HPP

#include <list>
#include <mutex>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include "World.pb.h"

namespace Engine {

    class Location;
    typedef boost::shared_ptr<Location> LocationPtr;

    class World {

        public:

            World();
            World(const EngineData::World&);

            void setName(const char* name);
            void setName(const std::string& name);
            const std::string& getName() const;

            void setDescription(const char* desc);
            void setDescription(const std::string& desc);
            const std::string& getDescription() const;

            void addLocation(const LocationPtr& location);
            const std::list<LocationPtr>& getLocations() const;

        private:

            mutable std::mutex synchroMutex_;

            std::string name_;
            std::string desc_;

            std::list<LocationPtr> locations_;

    };

}


#endif

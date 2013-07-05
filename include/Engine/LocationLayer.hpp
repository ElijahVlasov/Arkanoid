﻿#ifndef _SALT2D_ENGINE_WORLDLAYER_HPP
#define _SALT2D_ENGINE_WORLDLAYER_HPP

#include <list>
#include <mutex>
#include <stdexcept>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/geometry/geometry.hpp>

#include <Utils/Lua.hpp>
#include <Utils/SingletonPointer.hpp>

#include "geometry_defines.hpp"

#include "World.pb.h"

namespace Engine {

    using namespace boost::geometry;

    class Object;
    typedef boost::shared_ptr<Object> ObjectPtr;

    class LocationLayer {

        public:

            LocationLayer();
            LocationLayer(const EngineData::Layer* layer) throw(std::runtime_error);

            ~LocationLayer();

            void addObject(const ObjectPtr& object);
            const std::list<ObjectPtr>& getObjects() const;

            template<class AreaType> std::list<ObjectPtr> getObjectsInArea(const AreaType& area) const {

                std::lock_guard<std::mutex> guard(synchroMutex_);

                std::list<ObjectPtr> objects;

                BOOST_FOREACH(ObjectPtr obj, objects_) {

                    if(intersects(getObjectsPolygon(obj), area)) {
                        objects.push_back(obj);
                    }

                }

                return objects;

            }

            GeometryDefines::Box& box();

        private:

            mutable std::mutex synchroMutex_;

            Utils::SingletonPointer<Utils::Lua> lua_;

            GeometryDefines::Box box_;

            std::list<ObjectPtr> objects_;

            GeometryDefines::Polygon getObjectsPolygon(const ObjectPtr& obj) const;

    };

    typedef boost::shared_ptr<LocationLayer> LocationLayerPtr;

}

#endif

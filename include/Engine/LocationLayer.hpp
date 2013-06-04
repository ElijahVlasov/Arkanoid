#ifndef _SALT2D_ENGINE_WORLDLAYER_HPP
#define _SALT2D_ENGINE_WORLDLAYER_HPP

#include <list>
#include <mutex>

#include <boost/foreach.hpp>


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include "World.pb.h"

namespace Engine {

    using namespace boost::geometry;

    class LocationLayer {

        public:

            LocationLayer();
            LocationLayer(const EngineData::Layer* layer);
            
            void addObject(const ObjectPtr& object);
            const std::list<ObjectPtr>& getObjects() const;

            template<class AreaType> std::list<ObjectPtr> getObjectsInArea(const AreaType& area) const {

                std::lock_guard<std::mutex> guard(synchroMutex_);

                std::list<ObjectPtr> objects;

                BOOST_FOREACH(ObjectPtr obj, objects_) {

                    if(intersects(getObjectBox(obj), area)) {
                        objects.push_back(obj);
                    }

                }

                return objects;

            }
            
            model::box< model::d2::point_xy<float> >& box();
            
        private:
        
            mutable std::mutex synchroMutex_;
            
            model::box< model::d2::point_xy<float> > box_;

            std::list<ObjectPtr> objects_;

            model::box< model::d2::point_xy<float> > getObjectBox(const ObjectPtr& obj) const;

    };

    typedef boost::shared_ptr<LocationLayer> LocationLayerPtr;
    
}

#endif

namespace Engine {
 
    class WorldLayer;
    
    typedef boost::shared_ptr<WorldLayer> WorldLayerPtr;

}

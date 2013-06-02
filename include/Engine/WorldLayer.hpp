#ifndef _SALT2D_ENGINE_WORLDLAYER_HPP
#define _SALT2D_ENGINE_WORLDLAYER_HPP

#include <list>
#include <mutex>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include "World.pb.h"

namespace Engine {

    using namespace boost::geometry;

	class WorldLayer {
	
		public:
		
			WorldLayer();
			WorldLayer(const EngineData::Layer& layer);
            
            void addObject(const ObjectPtr& object);
            const std::list<ObjectPtr>& getObjects() const;
            
            std::list<ObjectPtr> getObjectsInBox(const model::box< model::d2::point_xy<float> >& box) const;
            
            model::box< model::d2::point_xy<float> >& box();
            
        private:
        
            std::mutex synchroMutex_;
            
            model::box< model::d2::point_xy<float> > box_;
        
            std::list<ObjectPtr> objects_;
	
	};

    typedef boost::shared_ptr<WorldLayer> WorldLayerPtr;
    
}

#endif

namespace Engine {
 
    class WorldLayer;
    
    typedef boost::shared_ptr<WorldLayer> WorldLayerPtr;

}
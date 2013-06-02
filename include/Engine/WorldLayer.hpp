#ifndef _SALT2D_ENGINE_WORLDLAYER_HPP
#define _SALT2D_ENGINE_WORLDLAYER_HPP

#include <list>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include "World.pb.h"

namespace Engine {

	class WorldLayer {
	
		public:
		
			WorldLayer();
			WorldLayer(const EngineData::Layer& layer);
            
            void addObject(const Object::ObjectPtr& object);
            
        private:
        
            std::list<ObjectPtr> objects_;
	
	};

    typedef boost::shared_ptr<WorldLayer> WorldLayerPtr;
    
}

#endif

namespace Engine {
 
    class WorldLayer;
    
    typedef boost::shared_ptr<WorldLayer> WorldLayerPtr;

}
#ifndef _ENGINE_OBJECT_HPP
#define _ENGINE_OBJECT_HPP

#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/IRenderer.hpp>
#include <Engine/LocationLayer.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Texture.hpp>

namespace Engine {

    using namespace boost::geometry;

    class Object {

        public:

            Object();
            virtual ~Object();

            virtual void onCollision() = 0;

            virtual void onRender();

            virtual void live() = 0;
            
            virtual void move(float xShift, float yShift);

            void setDirection(DIRECTION dir);
            DIRECTION getDirection() const;
            
            void setParentLayer(const LocationLayerPtr& layer);
            const LocationLayerPtr& getParentLayer() const;
            
            int getId() const;

            void setRenderer(const boost::shared_ptr<IRenderer>& renderer);

            model::box< model::d2::point_xy<float> >& box();

        private:
        
            mutable std::mutex synchroMutex_;
            
            LocationLayerPtr parentLayer_;

            model::box< model::d2::point_xy<float> > box_;

            boost::shared_ptr<IRenderer> renderer_;

            DIRECTION dir_;

            int id_;

    };
    
    typedef boost::shared_ptr<Object> ObjectPtr;

}

#endif

namespace Engine {

    class Object;
    
    typedef boost::shared_ptr<Object> ObjectPtr;
    
}

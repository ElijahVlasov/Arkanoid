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

            int getId() const;

            void setRenderer(const boost::shared_ptr<IRenderer>& renderer);

            model::box< model::d2::point_xy<float> >& box();

        private:

            model::box< model::d2::point_xy<float> > box_;

            boost::shared_ptr<IRenderer> renderer_;

            DIRECTION dir_;

            int id_;

    };

}


#endif

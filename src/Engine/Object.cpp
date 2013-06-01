#include <stdexcept>
#include <string>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>

#include <Utils/ResourceManager.hpp>

using namespace std;

using namespace Engine;

using namespace Utils;

using namespace boost::geometry::model;



Object::Object():
    renderer_((IRenderer*)0)
{}



Object::~Object() {}



int Object::getId() const {

    return id_;

}



void Object::onRender() {

    if(renderer_ != 0) {
        renderer_->onRender();
    }

}



void Object::setRenderer(const boost::shared_ptr<IRenderer>& renderer) {

    renderer_ = renderer;

}



box< d2::point_xy<float> >& Object::box() {

    return box_;

}

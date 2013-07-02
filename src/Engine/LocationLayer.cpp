#include <list>
#include <mutex>
#include <stdexcept>
#include <string>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Object.hpp>
#include <Engine/LocationLayer.hpp>

#include <Utils/Lua.hpp>

#include "geometry_defines.hpp"

#include "Box.pb.h"
#include "Point.pb.h"
#include "World.pb.h"

using namespace std;

using namespace GeometryDefines;

using namespace Engine;

using namespace Utils;



LocationLayer::LocationLayer():
    lua_(Lua::getInstance(), false)
{}



LocationLayer::LocationLayer(const EngineData::Layer* layer) throw(std::runtime_error):
    lua_(Lua::getInstance(), false)
{

    const EngineData::Box& box = layer->box();

    const EngineData::Point& e_min_corner = box.min_corner();
    const EngineData::Point& e_max_corner = box.max_corner();

    Point min_corner(e_min_corner.x(), e_min_corner.y());
    Point max_corner(e_max_corner.x(), e_max_corner.y());

    box_.min_corner() = min_corner;
    box_.max_corner() = max_corner;

    //TODO: добавить создание объектов

    const google::protobuf::RepeatedPtrField< EngineData::StaticObject > &objects = layer->objects();

    BOOST_FOREACH(const EngineData::StaticObject& obj, objects) {

        string className;

        if(obj.has_class_()) {

            className = obj.class_();

        }

        try {

            luabind::object luaStaticObj = luabind::call_function<luabind::object>(lua_->getLuaState(), className.c_str());

            //luabind::object []

            //luabind::call_function<void>(luaStaticObj)

        } catch(const luabind::error& err) {

            throw(runtime_error(err.what()));

        }



    }

}



void LocationLayer::addObject(const ObjectPtr& object) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    objects_.push_back(object);

}



const list<ObjectPtr>& LocationLayer::getObjects() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return objects_;

}



Box& LocationLayer::box() {

    return box_;

}



GeometryDefines::Polygon LocationLayer::getObjectsPolygon(const ObjectPtr& obj) const {

    return obj->getPolygon();

}

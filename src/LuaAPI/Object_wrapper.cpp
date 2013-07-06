#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Collision.hpp>
#include <Engine/Object.hpp>

#include <LuaAPI/Object_wrapper.hpp>

#include "geometry_defines.hpp"

using namespace Engine;

using namespace LuaAPI;



Object_wrapper::Object_wrapper():
    Object()
{}



void Object_wrapper::onCollision(const Collision& collision) {

    call<void>("on_collision", collision);

}



void Object_wrapper::onRender() {

    call<void>("on_render");

}



void Object_wrapper::default_onRender(ObjectPtr object) {

    object->onRender();

}



void Object_wrapper::live() {

    call<void>("live");

}



void Object_wrapper::move(float step) {

    call<void>("move", step);

}



void Object_wrapper::default_move(ObjectPtr object, float step) {

    object->move(step);

}



void Object_wrapper::spin(float step) {

    call<void>("spin", step);

}



void Object_wrapper::default_spin(ObjectPtr object, float step) {

    object->spin(step);

}



GeometryDefines::Point Object_wrapper::getCenter() const {

    return call<GeometryDefines::Point>("get_center");

}



GeometryDefines::Point Object_wrapper::default_getCenter(ObjectPtr object) {

    return object->getCenter();

}

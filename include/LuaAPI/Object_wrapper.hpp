#ifndef _SALT2D_LUAAPI_OBJECT_WRAPPER_HPP
#define _SALT2D_LUAAPI_OBJECT_WRAPPER_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Collision.hpp>
#include <Engine/Object.hpp>

#include "geometry_defines.hpp"

namespace LuaAPI {

    class Object_wrapper: public Engine::Object, public luabind::wrap_base {

        public:

            Object_wrapper();

            void onCollision(const Engine::Collision& collision);

            void onRender();
            static void default_onRender(Engine::ObjectPtr object);

            void live();

            void move(float step);
            static void default_move(Engine::ObjectPtr object, float step);

            void spin(float step);
            static void default_spin(Engine::ObjectPtr object, float step);

            GeometryDefines::Point getCenter() const;
            static GeometryDefines::Point default_getCenter(Engine::ObjectPtr object);

    };

}

#endif

#ifndef _SALT2D_LUAAPI_SPRITE_WRAPPER_HPP
#define _SALT2D_LUAAPI_SPRITE_WRAPPER_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils/Graphics/Sprite.hpp>

#include "geometry_defines.hpp"

namespace LuaAPI {

    class Sprite_wrapper: public Utils::Graphics::Sprite, public luabind::wrap_base {

        public:

            Sprite_wrapper();
            ~Sprite_wrapper();

            void onRender(const GeometryDefines::Point& point);

            void onRender(const GeometryDefines::PointI& point);
            static void default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::PointI& point);

            void onRender(const GeometryDefines::Box& box);

            void onRender(const GeometryDefines::BoxI& box);
            static void default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::BoxI& box);

            void onRender(const GeometryDefines::Polygon& polygon);

            void onRender(const GeometryDefines::PolygonI& polygon);
            static void default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::PolygonI& polygon);

    };

}

#endif

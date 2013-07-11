#ifndef _SALT2D_LUAAPI_BOX_WRAPPERS_HPP
#define _SALT2D_LUAAPI_BOX_WRAPPERS_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include "geometry_defines.hpp"

namespace LuaAPI {

    template <class BoxType, class PointType> class Box_wrapper: public BoxType, public luabind::wrap_base {

        public:

            PointType getMinCorner() const {

                return this->BoxType::min_corner();

            }



            PointType getMaxCorner() const {

                return this->BoxType::max_corner();

            }



            void setMinCorner(const PointType& min_corner) {

                this->BoxType::min_corner() = min_corner;

            }



            void setMaxCorner(const PointType& max_corner) {

                this->BoxType::max_corner() = max_corner;

            }

    };

}

#endif

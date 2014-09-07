#ifndef _SALT2D_LUAAPI_BLOCK_WRAPPER_HPP
#define _SALT2D_LUAAPI_BLOCK_WRAPPER_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Block.hpp>

#include "geometry_defines.hpp"

namespace LuaAPI {

    class Block_wrapper: public Engine::Block, public luabind::wrap_base {

        public:

            Block_wrapper(const GeometryDefines::Box&);

            virtual bool crash();


        private:

    };

}

#endif

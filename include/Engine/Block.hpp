#ifndef _SALT2D_ENGINE_BLOCK_HPP
#define _SALT2D_ENGINE_BLOCK_HPP

#include <Engine/Object.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class Block: public Object {

        public:

            Block(const GeometryDefines::Box& rect);
            virtual ~Block();

            virtual bool crash() = 0;

            void setNeedCount(bool isNeedCount);
            bool isNeedCount() const;

            GeometryDefines::Box getRect() const;

        private:

            GeometryDefines::Box rect_;

            bool isNeedCount_;

    };

}

#endif

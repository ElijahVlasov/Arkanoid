#ifndef _SALT2D_ENGINE_BLOCK_HPP
#define _SALT2D_ENGINE_BLOCK_HPP

#include "geometry_defines.hpp"

namespace Engine {

    class Block {

        public:

            Block(const GeometryDefines::Box& rect);
            virtual ~Block();

            virtual void draw()  = 0;
            virtual bool crash() = 0;

            const GeometryDefines::Box& getRect() const;

        private:

            GeometryDefines::Box rect_;

    };

}

#endif

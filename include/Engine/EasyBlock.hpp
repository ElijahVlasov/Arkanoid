#ifndef _SALT2D_ENGINE_EASYBLOCK_HPP
#define _SALT2D_ENGINE_EASYBLOCK_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Block.hpp>

#include <Utils/Graphics/Texture.hpp>

namespace Engine {

    class EasyBlock : public Block {

        public:

            EasyBlock(const GeometryDefines::Box& rect) throw(std::runtime_error);

            void draw();
            bool crash();

        private:

            boost::shared_ptr<Utils::Graphics::Texture> texture_;

    };

}

#endif

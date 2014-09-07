#ifndef _SALT2D_ENGINE_LEVEL_HPP
#define _SALT2D_ENGINE_LEVEL_HPP

#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <Engine/Block.hpp>

#include <Utils/Lua.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/Sound.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class Game;

    class Level {

        public:

            Level(const std::string& data) throw(std::invalid_argument, std::runtime_error);

            std::list< boost::shared_ptr<Block> > getBlocksInBox(GeometryDefines::Box box) const;

            size_t getBlocksCount() const;

            const boost::shared_ptr<Utils::Audio::Sound>& getSound() const;

            inline const GeometryDefines::Box& getRect() const { return rect_; }

            void crashBlock(const boost::shared_ptr<Block>& block);

            void draw();

            void clear();

        private:

            static const char* LEVEL_SIGNATURE;

            struct LEVEL {

                unsigned char sig[3];

                char music[80];
                char background[80];

                int x, y;
                unsigned int width, height;

                unsigned int blockWidth, blockHeight;

                unsigned int rows, cols;

                unsigned int blocksOffset;

            };

            const unsigned int blockWidth_, blockHeight_;

            Utils::SingletonPointer<Game> game_;

            Utils::SingletonPointer<Utils::Lua> lua_;

            GeometryDefines::Box rect_;

            std::vector< std::vector< boost::shared_ptr<Block> > > blocks_;

            boost::shared_ptr<Utils::Audio::Sound> sound_;
            boost::shared_ptr<Utils::Graphics::Texture> background_;

            size_t blocksCount_;

    };

}

#endif

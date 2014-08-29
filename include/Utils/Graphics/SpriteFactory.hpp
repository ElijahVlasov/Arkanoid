#ifndef _SALT2D_UTILS_GRAPHICS_SPRITEFACTORY_HPP
#define _SALT2D_UTILS_GRAPHICS_SPRITEFACTORY_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/Sprite.hpp>

namespace Utils {

    namespace Graphics {

        class SpriteFactory: public Singleton<SpriteFactory> {

            SINGLETON(SpriteFactory)

            public:

                enum SpriteType {

                    STATIC,
                    ANIMATION

                };

                static boost::shared_ptr<Sprite> createSprite(const char* fileName,        SpriteType spriteType) throw(std::invalid_argument, std::runtime_error);
                static boost::shared_ptr<Sprite> createSprite(const std::string& fileName, SpriteType spriteType) throw(std::invalid_argument, std::runtime_error);

            protected:

                SpriteFactory();

            private:

                static const std::string SPRITE_ROOT_ELEMENT;

                SingletonPointer<ResourceManager> resourceManager_;

                boost::shared_ptr<Sprite> createStaticSprite(const std::string& fileName) throw(std::runtime_error);
                boost::shared_ptr<Sprite> createAnimationSprite(const std::string& fileName) throw(std::runtime_error);

        };

    }
}

#endif

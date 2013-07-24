#ifndef _SALT2D_UTILS_SPRITEFACTORY_HPP
#define _SALT2D_UTILS_SPRITEFACTORY_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>
#include <Utils/Sprite.hpp>

namespace Utils {

    class SpriteFactory: public Singleton<SpriteFactory> {

        SINGLETON(SpriteFactory)

        public:

            boost::shared_ptr<Sprite> createSprite(const char* spriteType, const char* fileName)
                                                        throw(std::invalid_argument, std::runtime_error);

            boost::shared_ptr<Sprite> createSprite(const std::string& spriteType, const std::string& fileName)
                                                        throw(std::invalid_argument, std::runtime_error);

        protected:

            SpriteFactory();

        private:

            static const std::string ANIMATION_SPRITE_TYPE;
            static const std::string STATIC_SPRITE_TYPE;

            SingletonPointer<ResourceManager> resourceManager_;

            boost::shared_ptr<Sprite> createAnimationSprite(const std::string& animationFileName) throw(std::runtime_error);
            boost::shared_ptr<Sprite> createStaticSprite(const std::string& textureFileName)      throw(std::runtime_error);

    };

}

#endif

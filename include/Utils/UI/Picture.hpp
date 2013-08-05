#ifndef _SALT2D_UTILS_UI_PICTURE_HPP
#define _SALT2D_UTILS_UI_PICTURE_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {

        class Picture: public Component {

            public:

                Picture()                               throw(std::runtime_error);
                Picture(const char* textureName)        throw(std::invalid_argument, std::runtime_error);
                Picture(const std::string& textureName) throw(std::invalid_argument, std::runtime_error);
                Picture(const boost::shared_ptr<Graphics::Texture>& texture) throw(std::runtime_error);

                ~Picture();

                boost::shared_ptr<Graphics::Texture> getTexture() const;
                void setTexture(const boost::shared_ptr<Graphics::Texture>& texture);

            private:

                boost::shared_ptr<Graphics::Texture> loadTexture(const std::string& textureName) throw(std::invalid_argument, std::runtime_error);

                static void onDraw(Component* sender, Event&);

                boost::shared_ptr<Graphics::Texture> texture_;

        };

    }

}

#endif

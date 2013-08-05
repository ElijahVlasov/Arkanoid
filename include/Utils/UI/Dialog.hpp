#ifndef _SALT2D_UTILS_UI_DIALOG_HPP
#define _SALT2D_UTILS_UI_DIALOG_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Container.hpp>

namespace Utils {

    namespace UI {

        class Dialog: public Container {

            public:

                Dialog();
                ~Dialog();


            protected:

                void drawSelf();

            private:

                boost::shared_ptr<Utils::Graphics::Texture> frame_;

        };

    }

}

#endif

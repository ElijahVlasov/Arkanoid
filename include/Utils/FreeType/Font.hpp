#ifndef _SALT2D_UTILS_FONT_HPP
#define _SALT2D_UTILS_FONT_HPP

#include <boost/cstdint.hpp>

#include <string>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>
#include <Utils/Resource.hpp>
#include <Utils/Texture.hpp>

#include <Utils/FreeType/Library.hpp>

namespace Utils {

    namespace FreeType {

        /** Класс шрифта.
          * @author Elijah Vlasov
        */

        class Font: public Resource {

            public:

                Font();
                Font(const Font& font);

                ~Font();

                Font& operator=(const Font& font);

                /** Отрендерить текст в OpenGL-текстуру.
                  * @param text Текст для рендеринга 
                  * @throws Генерирует std::invalid_argument, если text == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2
                */

                Texture renderText(const char* text)        throw(std::invalid_argument, std::runtime_error);

                /** Отрендерить текст в OpenGL-текстуру.
                  * @param text Текст для рендеринга 
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2
                */

                Texture renderText(const std::string& text) throw(std::runtime_error);

                /** Кегль шрифта.
                */

                unsigned int getSize() const;

                /** Установить кегль шрифта.
                  * @throw Генерирует std::invalid_argument, если size == 0.
                */

                void setSize(unsigned int size)             throw(std::invalid_argument);

                /** Цвет шрифта.
                */

                const Utils::Color& getColor() const;

                /** Установить цвет шрифта.
                */

                void setColor(const Utils::Color& color);

                std::string getData() const;
                void setData(const std::string& data);

            private:

                Library* lib_;

                std::string fontBuffer_;

                FT_Face face_;

                unsigned int size_;

                Utils::Color color_;

        };

    }

}

#endif

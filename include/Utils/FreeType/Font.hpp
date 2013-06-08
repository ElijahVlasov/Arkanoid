#ifndef _SALT2D_UTILS_FONT_HPP
#define _SALT2D_UTILS_FONT_HPP

#include <boost/cstdint.hpp>

#include <climits>

#include <mutex>
#include <string>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <boost/array.hpp>
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

                /** Отрендерить текст.
                  * @param text Текст для рендеринга 
                  * @throws Генерирует std::invalid_argument, если text == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2
                */

                void renderText(const char* text, float x, float y)        throw(std::invalid_argument, std::runtime_error);

                /** Отрендерить текст.
                  * @param text Текст для рендеринга 
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2
                */

                void renderText(const std::string& text, float x, float y) throw(std::runtime_error);

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

                //void testDraw();

            private:
                
                /*inline void renderFace();

                // Возвращает следующую степень двойки, после val.
                inline int next_p2(int val);

                void createSymbolVisual(unsigned char ch) throw(std::runtime_error);*/

                void setData_(const std::string& data);

                mutable std::mutex synchroMutex_;

                bool isRendered_;

                GLuint listBase_;

                // Текстуры символов.
                boost::array< boost::shared_ptr<Utils::Texture>, UCHAR_MAX + 1 > symbols_;

                Library* lib_;

                std::string fontBuffer_;

                FT_Face face_;

                unsigned int size_;

                Utils::Color color_;

        };



        /*int Font::next_p2(int val) {
        
            int result = 1;

            while(result < val) {
                result <<= 1;
            }

            return result;

        }



        void Font::renderFace() {

            FT_Set_Char_Size(face_, size_ << 6, size_ << 6, 96, 96);

            for(unsigned char ch = 0; ch < UCHAR_MAX; ch++) {
    
                createSymbolVisual(ch);

            }

            isRendered_ = true;

        }*/

    }

}

#endif

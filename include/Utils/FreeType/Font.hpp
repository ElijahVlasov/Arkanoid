#ifndef _SALT2D_UTILS_FONT_HPP
#define _SALT2D_UTILS_FONT_HPP

#include <cwchar>

#include <mutex>
#include <string>
#include <stdexcept>

#include <FTGL/ftgl.h>

#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>
#include <Utils/Resource.hpp>

namespace Utils {

    namespace FreeType {

        /** Класс шрифта.
          * @author Elijah Vlasov
        */

        class Font: public Resource {

            public:

                /** Размер текста.
                */

                typedef struct _FONT_RECT {

                    float width, height;

                } FONT_RECT;

                Font();
                Font(const Font& font);

                ~Font();

                Font& operator=(const Font& font);

                /** Измерить UTF-8 текст.
                  * @param text UTF-8 текст.
                  * @throws Генерирует std::invalid_argument, если text == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2 или если text не UTF-8.
                */

                FONT_RECT measureText(const char* text)                     throw(std::invalid_argument, std::runtime_error);

                /** Измерить UTF-8 текст.
                  * @param text UTF-8 текст.
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2 или если text не UTF-8.
                */

                FONT_RECT measureText(const std::string& text)              throw(std::runtime_error);

                /** Измерить UTF-16 текст.
                  * @param text UTF-16 текст.
                  * @throws Генерирует std::invalid_argument, если wText == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2.
                */

                FONT_RECT measureText(const wchar_t* wText)                 throw(std::invalid_argument, std::runtime_error);

                /** Отрендерить UTF-16 текст.
                  * @param text Текст для рендеринга
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2
                */

                FONT_RECT measureText(const std::wstring& wText)            throw(std::runtime_error);

                /** Отрендерить UTF-8 текст.
                  * @param text Текст для рендеринга
                  * @param width Длина текста. Если результирующая длина текста больше этой величины, то текст обрезается.
                  * @param height Высота текста. Если результирующая высота текста больше этой величины, то текст обрезается.
                  * @throws Генерирует std::invalid_argument, если text == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2 или если text не UTF-8.
                */

                void renderText(const char* text, float x, float y, float width = -1.0f, float height = -1.0f)
                                                                            throw(std::invalid_argument, std::runtime_error);

                /** Отрендерить UTF-16 текст.
                  * @param wText Текст для рендеринга.
                  * @see renderText
                  * @throws Генерирует std::invalid_argument, если wText == NULL.
                  *         Генерирует std::runtime_error, при ошибке Freetype2.
                */

                void renderText(const wchar_t* wText, float x, float y, float width = -1.0f, float height = -1.0f)
                                                                            throw(std::invalid_argument, std::runtime_error);

                /** Отрендерить UTF-8 текст.
                  * @param text Текст для рендеринга.
                  * @see renderText
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2 или если text не UTF-8.
                */

                void renderText(const std::string& text, float x, float y, float width = -1.0f, float height = -1.0f)
                                                                           throw(std::runtime_error);

                /** Отрендерить UTF-16 текст.
                  * @param wText Текст для рендеринга
                  * @see renderText
                  * @throws Генерирует std::runtime_error, при ошибке Freetype2
                */

                void renderText(const std::wstring& wText, float x, float y, float width = -1.0f, float height = -1.0f)
                                                                           throw(std::runtime_error);

                /** Размер шрифта.
                */

                unsigned int getSize() const;

                /** Установить размер шрифта.
                  * @throw Генерирует std::invalid_argument, если size == 0.
                */

                void setSize(unsigned int size)                            throw(std::invalid_argument);

                /** Цвет шрифта.
                */

                const Utils::Color& getColor() const;

                /** Установить цвет шрифта.
                */

                void setColor(const Utils::Color& color);

                std::string getData() const;
                void setData(const std::string& data);

            private:


                void setData_(const std::string& data);

                mutable std::mutex synchroMutex_;

                Utils::Color color_;

                FTFont* font_;

                std::string fontBuffer_;

        };

    }

}

#endif

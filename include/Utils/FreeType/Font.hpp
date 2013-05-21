#ifndef _SALT2D_UTILS_FONT_HPP
#define _SALT2D_UTILS_FONT_HPP

#include <boost/cstdint.hpp>

#include <string>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>

#include <Utils/Texture.hpp>

#include <Utils/FreeType/Library.hpp>

namespace Utils {

    namespace FreeType {

        /** ����� ������.
          * @author Elijah Vlasov
        */

        class Font {

            public:

                /** ��������� ����� �� �����.
                  * ����� ������ � ����� FONT_PATH
                  * @param filePath ��� ����� ������.
                  * @throws ���������� std::invalid_argument, ���� filePath == NULL,
                  *         ��� ������ ������. ���������� std::runtime_error, ���� ���������
                  *         ������ ��������.
                */

                explicit Font(const char* filePath)         throw(std::invalid_argument, std::runtime_error);

                /** ��������� ����� �� �����.
                  * ����� ������ � ����� FONT_PATH
                  * @param filePath ��� ����� ������.
                  * @throws ���������� std::invalid_argument, ���� filePath - ������ ������. 
                  *         ���������� std::runtime_error, ���� ��������� ������ ��������.
                */

                explicit Font(const std::string& filePath)  throw(std::invalid_argument, std::runtime_error);
                Font(const Font& font);

                ~Font();

                Font& operator=(const Font& font);

                /** ����������� ����� � OpenGL-��������.
                  * @param text ����� ��� ���������� 
                  * @throws ���������� std::invalid_argument, ���� text == NULL.
                  *         ���������� std::runtime_error, ��� ������ Freetype2
                */

                Texture renderText(const char* text)        throw(std::invalid_argument, std::runtime_error);

                /** ����������� ����� � OpenGL-��������.
                  * @param text ����� ��� ���������� 
                  * @throws ���������� std::runtime_error, ��� ������ Freetype2
                */

                Texture renderText(const std::string& text) throw(std::runtime_error);

                /** ����� ������.
                */

                unsigned int getSize() const;

                /** ���������� ����� ������.
                  * @throw ���������� std::invalid_argument, ���� size == 0.
                */

                void setSize(unsigned int size)             throw(std::invalid_argument);

                /** ���� ������.
                */

                const Utils::Color& getColor() const;

                /** ���������� ���� ������.
                */

                void setColor(const Utils::Color& color);

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

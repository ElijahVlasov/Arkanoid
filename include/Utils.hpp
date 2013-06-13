/** Классы и функции утилитарного назначения.
  * @author Elijah Vlasov
*/


#ifndef _SALT2D_UTILS_HPP
#define _SALT2D_UTILS_HPP

#include <cstdlib>
#include <cwchar>

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/array.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/assert.hpp>
#include <Utils/Audio.hpp>
#include <Utils/Color.hpp>
#include <Utils/FreeType.hpp>
#include <Utils/Graphics.hpp>
#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/PCResourceLoader.hpp>
#include <Utils/Resource.hpp>
#include <Utils/ResourceFile.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/Sound.hpp>
#include <Utils/Texture.hpp>
#include <Utils/UI.hpp>

namespace Utils {

    /** Чтение потока до символа EOF в std::string.
      * @param stream Поток для чтения
    */

    std::string readStreamToString(std::ifstream& stream);

    /** Полное чтение двоичного потока.
      * @param stream Поток для чтения
    */

    std::string readBinaryStream(std::ifstream& stream);

    //inline std::wstring stringToWString(const std::string& str, std::locale loc = std::locale());

    inline std::wstring UTF8_to_UTF16(const std::string utf8) throw(std::runtime_error);

}

std::wstring Utils::UTF8_to_UTF16(const std::string utf8) throw(std::runtime_error) {

    std::vector<unsigned long> unicode;
    size_t i = 0;

    while (i < utf8.size()) {

        unsigned long uni;
        size_t todo;
        unsigned char ch = utf8[i++];

        if (ch <= 0x7F) {

            uni = ch;
            todo = 0;

        } else if (ch <= 0xBF) {

            throw std::runtime_error("Not a UTF-8 string");

        } else if (ch <= 0xDF) {

            uni = ch&0x1F;
            todo = 1;

        } else if (ch <= 0xEF) {

            uni = ch&0x0F;
            todo = 2;

        } else if (ch <= 0xF7) {

            uni = ch&0x07;
            todo = 3;

        } else {

            throw std::runtime_error("not a UTF-8 string");

        }

        for (size_t j = 0; j < todo; ++j) {

            if (i == utf8.size()) {

                throw std::runtime_error("not a UTF-8 string");

            }

            unsigned char ch = utf8[i++];

            if (ch < 0x80 || ch > 0xBF) {

                throw std::runtime_error("not a UTF-8 string");

            }

            uni <<= 6;
            uni += ch & 0x3F;

        }

        if (uni >= 0xD800 && uni <= 0xDFFF) {

            throw std::runtime_error("Not a UTF-8 string");

        }

        if (uni > 0x10FFFF) {

            throw std::runtime_error("Not a UTF-8 string");

        }

        unicode.push_back(uni);

    }

    std::wstring utf16;

    for (size_t i = 0; i < unicode.size(); ++i) {

        unsigned long uni = unicode[i];

        if (uni <= 0xFFFF) {

            utf16 += static_cast<wchar_t>(uni);

        } else {

            uni -= 0x10000;
            utf16 += static_cast<wchar_t>((uni >> 10) + 0xD800);
            utf16 += static_cast<wchar_t>((uni & 0x3FF) + 0xDC00);

        }

    }

    return utf16;

}

#endif

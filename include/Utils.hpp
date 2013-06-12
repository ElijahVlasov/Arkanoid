/** Классы и функции утилитарного назначения.
  * @author Elijah Vlasov
*/


#ifndef _SALT2D_UTILS_HPP
#define _SALT2D_UTILS_HPP

#include <cstdlib>
#include <cwchar>

#include <fstream>
#include <string>

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

    inline std::wstring stringToWString(const std::string& str, std::locale loc = std::locale());

}

std::wstring Utils::stringToWString( const std::string& in, std::locale loc) {

    std::wstring                out( in.length(), 0 );

    mbstowcs(const_cast<wchar_t*>(out.c_str()), in.c_str(), in.length());

    return out;

}

#endif

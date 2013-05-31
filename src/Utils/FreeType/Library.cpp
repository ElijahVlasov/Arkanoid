#include <cstring>

#include <fstream>
#include <stdexcept>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/format.hpp>

#include <Utils.hpp>

#include <Utils/FreeType/Library.hpp>

#include "config.h"

using namespace std;

using namespace Utils::FreeType;



Library::Library() throw(runtime_error) {

    ASSERT( 
        (FT_Init_FreeType(&library_) == 0),
        runtime_error("Failed to load FreeType Library!\nTry to install FreeType library.")
    );

}



Library::~Library() {

    FT_Done_FreeType(library_);

}



FT_Face Library::createFaceFromBuffer(const string& buffer, unsigned int index) throw(invalid_argument, runtime_error) {

    ASSERT(
        (buffer.length() != 0),
        invalid_argument(buffer)
    );

    FT_Face face;

    FT_Byte* bufferData = new FT_Byte[buffer.length()]; //reinterpret_cast<const FT_Byte*>(buffer.data());

    memcpy(bufferData, buffer.data(), buffer.length());

    FT_Error err = FT_New_Memory_Face(library_, bufferData, buffer.length(), index + 1, &face);

    delete bufferData;

    ASSERT(
        (err == 0),
        runtime_error("Font buffer has unknown type!")
    );

    return face;

}

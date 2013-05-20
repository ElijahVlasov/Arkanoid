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



string Library::loadFaceFile(const char* filePath) throw(invalid_argument, runtime_error) {

    ASSERT(
        (filePath != 0),
        invalid_argument("filePath")
    );

    ASSERT(
        (strlen(filePath) != 0),
        invalid_argument("filePath")
    );

    // путь к шрифту
    string fontPath = (boost::format("%1%/%2%") % FONT_PATH % filePath).str();

    ifstream fontStream(fontPath, ios::binary);

    string fontBuf(Utils::readBinaryStream(fontStream));

    return fontBuf;

}



string Library::loadFaceFile(const string& filePath) throw(invalid_argument, runtime_error) {

    return loadFaceFile(filePath.c_str());

}



FT_Face Library::createFaceFromBuffer(const string& buffer, unsigned int index) throw(invalid_argument, runtime_error) {

    ASSERT(
        (buffer.length() != 0),
        invalid_argument(buffer)
    );

    FT_Face face;

    FT_Error err = FT_New_Memory_Face(library_,
                                      reinterpret_cast<const FT_Byte*>(buffer.c_str()),
                                      buffer.length(),
                                      index,
                                      &face
                                     );

    ASSERT(
        (err == 0),
        runtime_error("Font buffer has unknown type!")
    );

    return face;

}

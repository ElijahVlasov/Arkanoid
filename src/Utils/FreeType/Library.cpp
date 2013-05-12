#include <cstring>

#include <stdexcept>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/format.hpp>

#include <Utils.hpp>

#include <Utils/FreeType/Library.hpp>

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



FT_Face* Library::loadFace(const char* filePath, unsigned int index, FT_Face* faceBuf) throw(invalid_argument, runtime_error) {

    ASSERT(
        (filePath != 0),
        invalid_argument("filePath")
    );

    ASSERT(
        (strlen(filePath) != 0),
        invalid_argument("filePath")
    );

    ASSERT(
        (faceBuf != 0),
        invalid_argument("faceBuf")
    );

    FT_Error err = FT_New_Face(library_, filePath, index, faceBuf);

    ASSERT(
        (err == 0),
        runtime_error((boost::format("Can't load face \"%1%\".") % filePath).str())
    );

    return faceBuf;

}



FT_Face* Library::loadFace(const string& filePath, unsigned int index, FT_Face* faceBuf) throw(invalid_argument, runtime_error) {

    return loadFace(filePath.c_str(), index, faceBuf);

}

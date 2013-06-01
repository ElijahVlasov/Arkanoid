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
        invalid_argument("buffer")
    );

    FT_Face face;

    FT_Open_Args args;

    memset(&args, 0, sizeof(FT_Open_Args));

    args.flags          =   FT_OPEN_MEMORY;
    args.memory_base    =   reinterpret_cast<const FT_Byte*>(buffer.data());
    args.memory_size    =   static_cast<FT_Long>(buffer.length());

    FT_Error err = FT_Open_Face(library_, &args, index, &face);


    ASSERT(
        (err == 0),
        runtime_error("Font buffer has unknown type!")
    );

    return face;

}

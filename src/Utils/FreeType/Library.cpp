#include <cstdlib>
#include <cstring>

#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <thread>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <Utils.hpp>

#include <Utils/FreeType/Library.hpp>

#include "config.h"

using namespace std;

using namespace Utils::FreeType;



Library::Library() throw(runtime_error) {

    getLibrary();

}



Library::~Library() {

    BOOST_FOREACH(auto pair, libraries_) {
    
        FT_Done_FreeType(pair.second);

    }

}



FT_Face Library::createFaceFromFile(const char* fileName, unsigned int index) throw(invalid_argument, runtime_error) {

    ASSERT(
        (fileName != 0),
        invalid_argument("fileName")
    );

    ASSERT(
        (strlen(fileName) != 0),
        invalid_argument("fileName")
    );

    FT_Library lib = getLibrary();

    FT_Face face;

    FT_Error err = FT_New_Face(lib, fileName, static_cast<FT_Long>(index), &face);

    ASSERT(
        (err == 0),
        runtime_error(
            (boost::format("Can't load face from \"%1%\"")
                % fileName
            ).str()
        )
    );

    return face;

}



FT_Face Library::createFaceFromFile(const string& fileName, unsigned int index) throw(invalid_argument, runtime_error) {

    return createFaceFromFile(fileName.c_str(), index);

}



FT_Face Library::createFaceFromBuffer(const string& buffer, unsigned int index) throw(invalid_argument, runtime_error) {

    ASSERT(
        (buffer.length() != 0),
        invalid_argument("buffer")
    );

    FT_Library lib = getLibrary();

    FT_Face face;

    FT_Open_Args args;

    memset(&args, 0, sizeof(FT_Open_Args));

    args.flags          =   FT_OPEN_MEMORY;
    args.memory_base    =   reinterpret_cast<const FT_Byte*>(buffer.data());
	args.memory_size    =   static_cast<FT_Long>(buffer.size());

    FT_Error err = FT_Open_Face(lib, &args, index, &face);

    ASSERT(
        (err == 0),
        runtime_error("Font buffer has unknown type!")
    );

    return face;

}



FT_Library Library::getLibrary() throw(runtime_error) {

    FT_Library lib;

    std::lock_guard<std::mutex> guard(synchroMutex_);

    try {
        
        lib = libraries_.at(this_thread::get_id());

    } catch(const out_of_range&) {

        ASSERT(
            (FT_Init_FreeType(&lib) == 0),
            runtime_error("Can't initialize Freetype")
        );

        libraries_[this_thread::get_id()] = lib;

    }

    return lib;

}
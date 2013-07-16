#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <png.h>

#include <Utils/assert.hpp>
#include <Utils/Texture.hpp>
#include <Utils/TextureFactory.hpp>

using namespace std;

using namespace Utils;



TextureFactory::TextureFactory() {}



boost::shared_ptr<Texture> TextureFactory::createFromPNGBuffer(const string& buffer) throw(invalid_argument, runtime_error) {

    boost::shared_ptr<Texture> texture(new Texture());

    TextureFactory::PNGReadStruct readStruct;

    istringstream is(buffer);

    ASSERT(
        (buffer.size() != 0),
        invalid_argument("buffer")
    );

    ASSERT(
        checkPNG( is ),
        runtime_error("Unknown data format")
    );

    png_set_read_fn(readStruct.readStruct, reinterpret_cast<png_voidp>(&is), TextureFactory::PNGReadFunc);

    png_set_sig_bytes(readStruct.readStruct, PNG_SIG_SIZE);

    PNGToTexture(readStruct.readStruct, readStruct.infoStruct, texture);

    return texture;

}



void TextureFactory::PNGToTexture(png_structp readStruct, png_infop infoStruct, boost::shared_ptr<Texture> texture) throw(runtime_error) {

    png_read_info(readStruct, infoStruct);

    png_uint_32 width       =   png_get_image_width(readStruct, infoStruct);
    png_uint_32 height      =   png_get_image_height(readStruct, infoStruct);

    png_uint_32 bitdepth    =   png_get_bit_depth(readStruct, infoStruct);
    png_uint_32 channels    =   png_get_channels(readStruct, infoStruct);

    png_uint_32 color_type  =   png_get_color_type(readStruct, infoStruct);

    texture->setWidth(width);
    texture->setHeight(height);

    switch(color_type) {

        case PNG_COLOR_TYPE_RGB: {

            channels = 3;
            bitdepth = 8;

            texture->setFormat(GL_RGB);

        }
        break;

        case PNG_COLOR_TYPE_RGBA: {

            channels = 4;
            bitdepth = 8;

            texture->setFormat(GL_RGBA);

        }
        break;

        default: {

            throw(runtime_error("Image has unknown format!"));

        }

    }

    string textureData;

    textureData.resize(width * height * (bitdepth * channels) / 8);

    char* data = const_cast<char*>(textureData.data());

    const unsigned int colLength = width * bitdepth * channels / 8;

    boost::shared_array< png_bytep > rowPtrs(new png_bytep[height]);

    for(size_t i = 0; i < height; i++) {

        png_uint_32 offset = (height - i - 1) * colLength;

        rowPtrs[i] = reinterpret_cast<png_bytep>(data) + offset;

    }

    png_read_image(readStruct, rowPtrs.get());

    texture->setData(textureData);

}



void TextureFactory::PNGReadFunc(png_structp readStruct, png_bytep data, png_size_t length) {

    png_voidp s = png_get_io_ptr(readStruct);

    auto stream = reinterpret_cast<istream*>(s);

    stream->read(reinterpret_cast< char* >(data), length);

}



void TextureFactory::PNGErrFunc(png_structp readStruct, const char* errString) {

    throw(runtime_error(
            (boost::format("PNG error: %1%")
                % errString
            ).str()
         )
    );

}

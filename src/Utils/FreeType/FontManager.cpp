#include <algorithm>
#include <stdexcept>
#include <string>
#include <thread>

#include <boost/foreach.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <FTGL/ftgl.h>

#include <Utils/assert.hpp>

#include <Utils/FreeType/FontManager.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::FreeType;

FontManager::FontManager():
    mainThreadID_(std::this_thread::get_id())
{}



void FontManager::update() throw(runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    createFonts();
    deleteFonts();

}



unsigned int FontManager::createFont(const string& fontData) throw(invalid_argument, runtime_error) {

    ASSERT(
        !fontData.empty(),
        invalid_argument("fontData")
    );

    std::lock_guard<std::mutex> guard(synchroMutex_);

    FontManager::PFontStruct fontStruct = createFontStruct();

    fontStruct->data = boost::shared_ptr<string>(new string(fontData));

    if(mainThreadID_ == std::this_thread::get_id()) {

        fontStruct->font = createFont(fontData.data(), fontData.size());

    } else {

        fontsForCreate_.push_back(fontStruct);

    }

    return fontStruct->uid;

}



unsigned int FontManager::createFontCopy(unsigned int srcFont) throw(invalid_argument, runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    FontManager::PFontStruct srcFontStruct = getFontStruct(srcFont);
    FontManager::PFontStruct dstFontStruct = createFontStruct();

    dstFontStruct->data = srcFontStruct->data;

    if(mainThreadID_ == std::this_thread::get_id()) {

        dstFontStruct->font = createFont(dstFontStruct->data->data(), dstFontStruct->data->size());

    } else {

        fontsForCreate_.push_back(dstFontStruct);

    }

    return dstFontStruct->uid;

}



void FontManager::deleteFont(unsigned int font) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(mainThreadID_ == std::this_thread::get_id()) {

        eraseFontStruct(font);

    } else {

        fontsForDelete_.push_back(font);

    }

}



boost::shared_ptr<FTFont> FontManager::getFont(unsigned int font) const {

    return getFontStruct(font)->font;

}



void FontManager::createFonts() throw(runtime_error) {

    BOOST_FOREACH(FontManager::PFontStruct& fontStruct, fontsForCreate_) {

        fontStruct->font = createFont(fontStruct->data->data(), fontStruct->data->size());

    }

    fontsForCreate_.clear();

}



void FontManager::deleteFonts() {

    BOOST_FOREACH(unsigned int font, fontsForDelete_) {

        eraseFontStruct(font);

    }

    fontsForDelete_.clear();

}



boost::shared_ptr<FTFont> FontManager::createFont(const char* data, size_t dataSize) throw(runtime_error) {

    boost::shared_ptr<FTFont> font(new FTTextureFont((const unsigned char*)data, dataSize));

    font->FaceSize(12);

    ASSERT(
        !font->Error(),
        runtime_error("Can't create font")
    );

    font->CharMap(ft_encoding_unicode);

    return font;

}



FontManager::PFontStruct FontManager::createFontStruct() {

    FontManager::PFontStruct fontStruct(new FontStruct);

    if(fonts_.empty()) {
        fontStruct->uid = 1;
    } else {
        fontStruct->uid = fonts_.back()->uid + 1;
    }

    fonts_.push_back(fontStruct);

    return fontStruct;

}



void FontManager::eraseFontStruct(unsigned int font) {

    auto pred = [font](const PFontStruct& ps) {

                    if(ps->uid == font) {
                        return true;
                    }

                    return false;

                };

    auto fontStruct = find_if(fonts_.begin(), fonts_.end(),  pred);

    if(fontStruct == fonts_.end()) {
        return;
    }

    fonts_.erase(fontStruct);

}



FontManager::PFontStruct FontManager::getFontStruct(unsigned int font) const {

    auto pred = [font](const PFontStruct& ps) {

                    if(ps->uid == font) {
                        return true;
                    }

                    return false;

                };

    auto fontStruct = find_if(fonts_.begin(), fonts_.end(),  pred);

    if(fontStruct == fonts_.end()) {
        return 0;
    }

    return *fontStruct;

}

#ifndef _SALT2D_UTILS_FREETYPE_FONTMANAGER_HPP
#define _SALT2D_UTILS_FREETYPE_FONTMANAGER_HPP

#include <list>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <FTGL/ftgl.h>

#include <Utils/Singleton.hpp>

namespace Utils {

    namespace FreeType {

        class FontManager: public Singleton<FontManager> {

            SINGLETON(FontManager)

            public:

                void update() throw(std::runtime_error);

                unsigned int createFont(const std::string& fontData) throw(std::invalid_argument, std::runtime_error);
                unsigned int createFontCopy(unsigned int srcFont)    throw(std::invalid_argument, std::runtime_error);
                void deleteFont(unsigned int font);

                boost::shared_ptr<FTFont> getFont(unsigned int font) const;

            protected:

                FontManager();

            private:

                void createFonts() throw(std::runtime_error);
                void deleteFonts();

                boost::shared_ptr<FTFont> createFont(const char* data, size_t dataSize) throw(std::runtime_error);

                const std::thread::id mainThreadID_;

                mutable std::mutex synchroMutex_;

                struct FontStruct {

                    unsigned int                    uid;
                    boost::shared_ptr<FTFont>       font;
                    boost::shared_ptr<std::string>  data;

                };

                typedef boost::shared_ptr< FontStruct > PFontStruct;

                PFontStruct createFontStruct();
                void eraseFontStruct(unsigned int font);
                PFontStruct getFontStruct(unsigned int font) const;

                std::list< PFontStruct > fonts_;

                std::list<PFontStruct> fontsForCreate_;
                std::map< unsigned int, unsigned int > fontsForCopy_;

                std::list< unsigned int > fontsForDelete_;


        };

    }

}

#endif

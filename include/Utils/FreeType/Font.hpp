#ifndef _SALT2D_UTILS_FONT_HPP
#define _SALT2D_UTILS_FONT_HPP

#include <cstdint>

#include <string>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <boost/array.hpp>

#include <boost/shared_ptr.hpp>

#include <Utils/Texture.hpp>

#include <Utils/FreeType/Library.hpp>

namespace Utils {

	namespace FreeType {

		class Font {
	
			public:

				typedef boost::array<uint8_t, 3> Color;

				explicit Font(const char* filePath) throw(std::runtime_error, std::invalid_argument);
				explicit Font(const std::string& filePath) throw(std::runtime_error, std::invalid_argument);
				Font(const Font& font);

				~Font();

				Font& operator=(const Font& font);

				// генерирует invalid_argument, если text == 0.
				// runtime_error, если 
				Texture renderText(const char* text) throw(std::invalid_argument, std::runtime_error);
				Texture renderText(const std::string& text) throw(std::runtime_error);

				unsigned int getSize() const;
				void setSize(unsigned int size) throw(std::invalid_argument);

				Color getColor() const;
				void setColor(const Color& color);

			private:

				Library* lib_;
				
				boost::shared_ptr<FT_Face> facePtr_;

				Color color_;

				unsigned int size_;

		};

	}

}

#endif
#ifndef _SALT2D_UTILS_FREETYPE_LIBRARY_HPP
#define _SALT2D_UTILS_FREETYPE_LIBRARY_HPP

#include <stdexcept>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Utils/Singleton.hpp>

namespace Utils {

	namespace FreeType {
	
		class Library: public Utils::Singleton<Library> {
		
			SINGLETON(Library)

			public:

				// filePath - ���� �� ����� � �������, index - ������ � �����
				// � faceBuf ����� ��������� ��������� FT_Face
				FT_Face* loadFace(const char* filePath, unsigned int index, FT_Face* faceBuf) 
																throw(std::invalid_argument, std::runtime_error);
				FT_Face* loadFace(const std::string& filePath, unsigned int index, FT_Face* faceBuf) 
																throw(std::invalid_argument, std::runtime_error);

			protected:

				// ���������� runtime_error, ���� ����������
				// ��������� FreeType ����������
				Library() throw(std::runtime_error);

				~Library();

			private:

				FT_Library library_;

		};

	}

}

#endif
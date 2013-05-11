#ifndef _ALREADY_EXIST_ERROR
#define _ALREADY_EXIST_ERROR

#include <stdexcept>

class already_exist_error: public std::runtime_error {
	
	public:

		already_exist_error(const char* text): std::runtime_error(text) {}

};


#endif
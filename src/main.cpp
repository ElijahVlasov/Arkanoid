#include <cstdlib>

#include <memory>
#include <stdexcept>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <Application.hpp>

#include <Exceptions/already_exist_error.hpp>

using namespace std;



void ProcessError(const runtime_error& err) {
	
	try {

		dynamic_cast<const already_exist_error&>(err);

		// Действия при уже запущенном приложении

	} catch(std::bad_cast&) {

 		#ifdef WINDOWS

		::MessageBoxA(0, err.what(), "Runtime error", MB_OK | MB_ICONERROR);

		#endif

	}



}



int main(int argc, char* argv[]) {

	try {
		auto_ptr<Application> app(new Application());

		int result = app->run();

		return result;

	} catch (runtime_error& err) {

		::ProcessError(err);

		return EXIT_FAILURE;

	}
		 
	return EXIT_SUCCESS;

}

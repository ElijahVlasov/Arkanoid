#include <cstdlib>
#include <csignal>

#include <memory>
#include <stdexcept>

#ifdef MS_WINDOWS

#include <Windows.h>

#else

#include <gtk/gtk.h>

#endif

#include <Application.hpp>

using namespace std;

#ifndef MS_WINDOWS

static void display_dialog(const char* caption, const char* text)
{

    GtkWidget  *dialog;

    dialog = gtk_message_dialog_new(0, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, text);

    gtk_window_set_title(GTK_WINDOW(dialog), caption);

    gtk_dialog_run(GTK_DIALOG(dialog));

}

static void MessageBox(const char* caption, const char* text)
{

    gtk_init(0, 0);
    
    display_dialog(caption, text);
    
}

#endif



static void ProcessError(const runtime_error& err) {
	
    #ifdef MS_WINDOWS

    ::MessageBoxA(0, err.what(), "Runtime error", MB_OK | MB_ICONERROR);

    #else 

    ::MessageBox("Runtime error", err.what());

    #endif

}



static void SignalDispatcher(int sig) {

    switch(sig) {

        case SIGSEGV: {
            ::ProcessError(runtime_error("Segmentation Fault!"));
            exit(EXIT_FAILURE);
        }
        break;  

    }

}



static void SetSignals() {

    signal(SIGINT, SignalDispatcher);
    signal(SIGILL, SignalDispatcher);
    signal(SIGABRT, SignalDispatcher);
    signal(SIGFPE, SignalDispatcher);
    signal(SIGSEGV, SignalDispatcher);
    signal(SIGTERM, SignalDispatcher);

}



#ifdef MS_WINDOWS

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

#else

int main(int argc, char* argv[]) {

#endif

    ::SetSignals();

    try {

        auto_ptr<Application> app(new Application());

        return app->run();

    } catch (const runtime_error& err) {

        ::ProcessError(err);

        return EXIT_FAILURE;

    }
		 
    return EXIT_SUCCESS;

}

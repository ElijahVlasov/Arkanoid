#ifndef _SALT2D_ENGINE_DEBUGOUTPUT_HPP
#define _SALT2D_ENGINE_DEBUGOUTPUT_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/SingletonPointer.hpp>

#include <Utils/FreeType/Font.hpp>

namespace Engine {

    class Game;

    class DebugOutput {

        public:

            DebugOutput() throw(std::runtime_error);

            void printf(const char* format, ...);

            void clear();

            void onRender();

        private:

            static const size_t MAX_LINE_SIZE;

            Utils::SingletonPointer<Game> game_;

            boost::shared_ptr<Utils::FreeType::Font> font_;

            std::string outputString_;

    };

}

#endif

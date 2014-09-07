#include <cstdarg>
#include <cstdio>

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <stdexcept>
#include <string>

#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>

#include <Engine/DebugOutput.hpp>
#include <Engine/Game.hpp>

#include <Utils/Color.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/FreeType/Font.hpp>

#include "salt_defines.h"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::FreeType;

const size_t DebugOutput::MAX_LINE_SIZE = 2048;

#ifndef NDEBUG
ofstream DebugOutput::outputStream_("log.txt");
#endif



DebugOutput::DebugOutput() throw(runtime_error):
    game_(Game::getInstance())
{

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    font_ = resourceManager->getResource<Font>(DEBUG_OUTPUT_FONT);

    Color color = {1.0f, 1.0f, 1.0f};

    font_->setColor(color);
    font_->setSize(24);

}



void DebugOutput::printf(const char* format, ...) {

    char* newCString = new char[MAX_LINE_SIZE];

    string newString;

    va_list vl;

    va_start(vl, format);

    vsprintf(newCString, format, vl);

    newString.assign(newCString);

    delete newCString;

    outputString_ += newString;

#ifndef NDEBUG
    outputStream_ << newString;
#endif

}



void DebugOutput::clear() {

    outputString_.clear();

}



void DebugOutput::onRender() {

    list< string > lines;

    boost::split(lines, outputString_, bind2nd(equal_to<char>(), '\n'));

    float y = game_->getScreenHeight() - 20.0f;

    BOOST_FOREACH(string& line, lines) {

        font_->renderText(line, 0.0f, y);

        y -= 20.0f;

    }

}

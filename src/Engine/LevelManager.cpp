#include <cstring>

#include <algorithm>
#include <stdexcept>
#include <string>

#include <boost/algorithm/string.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>
#include <Engine/Level.hpp>
#include <Engine/LevelManager.hpp>

#include <Utils/assert.hpp>
#include <Utils/ResourceManager.hpp>

using namespace std;

using namespace Engine;

using namespace Utils;



LevelManager::LevelManager(const char* levelsFileName) throw(invalid_argument, runtime_error):
    resourceManager_(ResourceManager::getInstance())
{

    ASSERT(
        (levelsFileName != 0),
        invalid_argument("levelsFileName")
    );

    ASSERT(
        (strlen(levelsFileName) != 0),
        invalid_argument("levelsFileName")
    );

    parseLevels(levelsFileName);

}



LevelManager::LevelManager(const string& levelsFileName) throw(invalid_argument, runtime_error):
    resourceManager_(ResourceManager::getInstance())
{

    ASSERT(
        !levelsFileName.empty(),
        invalid_argument("levelsFileName")
    );

    parseLevels(levelsFileName.c_str());

}



boost::shared_ptr<Level> LevelManager::loadNextLevel() throw(runtime_error) {

    if(!hasNextLevel()) {
        return boost::shared_ptr<Level>();
    }

    string data = resourceManager_->getFileData(getNextLevelName());

    return boost::shared_ptr<Level>(new Level(data));

}



void LevelManager::parseLevels(const char* fileName) throw(runtime_error) {

    string levels = resourceManager_->getFileData(fileName);

    boost::algorithm::split(levels_, levels, boost::is_any_of("\t\r\n "));

    nextLevel_ = levels_.cbegin();

}

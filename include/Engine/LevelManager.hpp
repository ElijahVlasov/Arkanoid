#ifndef _SALT2D_ENGINE_LEVELMANAGER_HPP
#define _SALT2D_ENGINE_LEVELMANAGER_HPP

#include <list>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Engine/Level.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

namespace Engine {

    class LevelManager {

        public:

            LevelManager(const char* levelsFileName)        throw(std::invalid_argument, std::runtime_error);
            LevelManager(const std::string& levelsFileName) throw(std::invalid_argument, std::runtime_error);

            inline bool hasNextLevel() const { return nextLevel_ != levels_.cend(); }

            boost::shared_ptr<Level> loadNextLevel() throw(std::runtime_error);

        private:

            inline const std::string& getNextLevelName() { return *nextLevel_++; }

            void parseLevels(const char* fileName) throw(std::runtime_error);

            Utils::SingletonPointer<Utils::ResourceManager> resourceManager_;

            std::list< std::string > levels_;

            std::list< std::string >::const_iterator nextLevel_;

    };

}

#endif

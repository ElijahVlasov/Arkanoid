#ifndef _SALT2D_UTILS_LOCALIZATIONMANAGER_HPP_
#define _SALT2D_UTILS_LOCALIZATIONMANAGER_HPP_

#include <map>
#include <stdexcept>
#include <string>

namespace Utils {

	class LocalizationManager {

		public:

			LocalizationManager(const char* localeName) 			throw(std::runtime_error);
			LocalizationManager(const std::string& localeName) 		throw(std::runtime_error);

			inline std::string getString(const char* key);
			inline std::string getString(const std::string& key);

		private:

			void loadLocalization(const char* locale) 				throw(std::runtime_error);

			static const std::string LOCALIZATION_DOCUMENT_ROOT_ELEMENT;
			static const std::string LOCALIZATION_DOCUMENT_ELEMENT;

			std::map< std::string, std::string > localization_;


	};



	std::string LocalizationManager::getString(const char* key) {

		if(key == 0) {
			return std::string(key);
		}

		return getString(std::string(key));

	}



	std::string LocalizationManager::getString(const std::string& key) {

		auto strIter = localization_.find(key);

		if(strIter == localization_.end()) {
			return key;
		}

		return strIter->second;

	}

}

#endif

#ifndef _SALT2D_UTILS_LOCALIZATIONMANAGER_HPP_
#define _SALT2D_UTILS_LOCALIZATIONMANAGER_HPP_

#include <map>
#include <stdexcept>
#include <string>

#include <Utils/Singleton.hpp>

namespace Utils {

    /** Менеджер локализации.
      * Хранит локализованный текст, для текущей локали.
      * @author Elijah Vlasov
    */

	class LocalizationManager: public Singleton<LocalizationManager> {

		SINGLETON(LocalizationManager)

		public:

		    /** Установить локаль. Менеджер будет загружать
		      * XML-документ localeName.xml, если не удастся
		      * загрузить сгенерирует исключение.
		    */

			void setLocale(const char* localeName) 				throw(std::runtime_error);
			void setLocale(const std::string& localeName) 		throw(std::runtime_error);

			/** Получить локализованную версию строкки.
			*/

			inline std::string getString(const char* key) const;
			inline std::string getString(const std::string& key) const;

		private:

			static const std::string LOCALIZATION_DOCUMENT_ROOT_ELEMENT;
			static const std::string LOCALIZATION_DOCUMENT_ELEMENT;

			std::map< std::string, std::string > localization_;


	};



	std::string LocalizationManager::getString(const char* key) const {

		if(key == 0) {
			return std::string();
		}

		return getString(std::string(key));

	}



	std::string LocalizationManager::getString(const std::string& key) const {

		auto strIter = localization_.find(key);

		if(strIter == localization_.end()) {
			return key;
		}

		return strIter->second;

	}

}

#endif

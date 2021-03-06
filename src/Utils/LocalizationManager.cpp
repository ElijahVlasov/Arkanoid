#include <cstring>

#include <locale>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#include <tinyxml.h>

#include <Utils/assert.hpp>

#include <Utils/LocalizationManager.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

using namespace std;

using namespace Utils;



const string LocalizationManager::LOCALIZATION_DOCUMENT_ROOT_ELEMENT = "localization";
const string LocalizationManager::LOCALIZATION_DOCUMENT_ELEMENT = "string";



void LocalizationManager::setLocale(const char* localeName) throw(runtime_error) {

	if(localeName == 0) {
		return;
	}

	if(strlen(localeName) == 0) {
		return;
	}

	localization_.clear(); // localization_ может содержать предыдущую локализацию

	SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

	string fileName = (boost::format("locale/%1%.xml")
						  % localeName
					  ).str();


	string locText = resourceManager->getFileData(fileName);

	TiXmlDocument doc;

	doc.Parse(locText.c_str());

	ASSERT(
		!doc.Error(),
		runtime_error(doc.ErrorDesc())
	);

	TiXmlElement* rootElement = doc.RootElement();

	ASSERT(
	    (rootElement != 0),
	    runtime_error("Document hasn't root element")
	);

	ASSERT( // провереяем корневой элемент
		(rootElement->ValueStr() == LOCALIZATION_DOCUMENT_ROOT_ELEMENT),
		runtime_error(
				(boost::format("Root node of menu document must have \"%1%\" value")
					% LOCALIZATION_DOCUMENT_ROOT_ELEMENT
				).str()
		)
	);

	locale_ = localeName;

	for(TiXmlNode* node = rootElement->FirstChild(); node != 0; node = node->NextSibling()) {

		TiXmlElement* localElement = node->ToElement();

		if(localElement == 0) {
			continue;
		}

		ASSERT( // проверяем элемент, нет ли ошибки в записи элемента
			(localElement->ValueStr() == LOCALIZATION_DOCUMENT_ELEMENT),
			runtime_error(
				(boost::format("Unknown element type: \"%1%\"")
					% localElement->ValueStr()
				).str()
			)
		);

		string key, text;

		localElement->QueryStringAttribute("name", &key);

		if(key.length() == 0) {
			continue;
		}

		for(TiXmlNode* textNode = localElement->FirstChild(); textNode != 0; textNode = textNode->NextSibling()) {

			TiXmlText* localText = textNode->ToText();

			if(localText == 0) {
				continue;
			}

			text += localText->ValueStr();

		}

		localization_[key] = text;

	}

}



void LocalizationManager::setLocale(const string& localeName) throw(runtime_error) {

	setLocale(localeName.c_str());

}



const string& LocalizationManager::getLocale() const {

    return locale_;

}

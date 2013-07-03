#include <cstring>

#include <locale>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/intrusive_ptr.hpp>

#include <tinyxml.h>

#include <Utils/LocalizationManager.hpp>
#include <Utils/ResourceManager.hpp>

using namespace std;

using namespace Utils;



const string LocalizationManager::LOCALIZATION_DOCUMENT_ROOT_ELEMENT = "localization";
const string LocalizationManager::LOCALIZATION_DOCUMENT_ELEMENT = "string";



LocalizationManager::LocalizationManager(const char* localeName) throw(runtime_error) {

	loadLocalization(localeName);

}



LocalizationManager::LocalizationManager(const string& localeName) throw(runtime_error) {

	loadLocalization(localeName.c_str());

}



void LocalizationManager::loadLocalization(const char* localeName) throw(runtime_error) {

	if(localeName == 0) {
		return;
	}

	if(strlen(localeName) == 0) {
		return;
	}

	boost::intrusive_ptr<ResourceManager> resourceManager(ResourceManager::getInstance(), false);

	string fileName = (boost::format("locale/%1%.xml")
						  % localeName
					  ).str();

	string locText = resourceManager->getResource(ResourceManager::ResourceType::PLAIN_TEXT, fileName)->getData();

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

	ASSERT(
		(rootElement->ValueStr() == LOCALIZATION_DOCUMENT_ROOT_ELEMENT),
		runtime_error(
				(boost::format("Root node of menu document must have \"%1%\" value")
					% LOCALIZATION_DOCUMENT_ROOT_ELEMENT
				).str()
		)
	);

	for(TiXmlNode* node = rootElement->FirstChild(); node != 0; node = node->NextSibling()) {

		TiXmlElement* localElement = node->ToElement();

		if(localElement == 0) {
			continue;
		}

		ASSERT(
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

		for(TiXmlNode* textNode = localElement->FirstChild(); textNode != 0; node = node->NextSibling()) {

			TiXmlText* localText = textNode->ToText();

			if(localText == 0) {
				continue;
			}

			text += localText->ValueStr();

		}

		localization_[key] = text;

	}

}
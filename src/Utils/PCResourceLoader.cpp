#include <cstring>

#include <ios>
#include <fstream>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>
#include <Utils/PCResourceLoader.hpp>

#include "salt_defines.h"

using namespace std;

using namespace Utils;



string PCResourceLoader::readFile(const char* fileName) throw(invalid_argument, runtime_error) {

    ASSERT(
        (fileName != 0),
        invalid_argument("fileName")
    );

    ASSERT(
        (strlen(fileName) != 0),
        invalid_argument("fileName")
    );

    string strFileName = (boost::format("%1%/%2%")
                            % RESOURCE_PATH
                            % fileName
                         ).str();

    ifstream fileStream(strFileName, ios::binary);

    ASSERT(
        (fileStream.good()),
        runtime_error(
            (boost::format("Can't load file \"%1%\"")
                % fileName
            ).str()
        )
    );

    string streamData;

    fileStream.seekg(0, ios_base::end);
    streamData.resize(fileStream.tellg());
    fileStream.seekg(0, ios_base::beg);

    fileStream.read(const_cast<char*>(streamData.data()), streamData.size());

    return streamData;

}

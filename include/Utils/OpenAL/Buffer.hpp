#ifndef _SALT2D_UTILS_OPENAL_BUFFER_HPP
#define _SALT2D_UTILS_OPENAL_BUFFER_HPP

#include <stdexcept>
#include <string>

#include <boost/utility.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace OpenAL {

        class Buffer: public boost::noncopyable {

            public:

                Buffer(const std::string& data, ALenum format, ALsizei frequency) throw(std::runtime_error);

                ~Buffer();

                void setData(const std::string& data);

                inline ALuint getID() const { return id_; }
                inline ALenum getFormat() const { return format_; }
                inline ALsizei getFrequency() const { return frequency_; }

            private:

                ALuint  id_;
                ALenum  format_;
                ALsizei frequency_;

        };

    }

}

#endif

#ifndef _SALT2D_UTILS_AUDIO_ISTREAM_HPP
#define _SALT2D_UTILS_AUDIO_ISTREAM_HPP

#include <Utils/Audio/Buffer.hpp>

namespace Utils {

    namespace Audio {

        /** Поток аудио.
          * @author Elijah Vlasov
        */

        class IStream {

            public:

                virtual ~IStream();

                /** Получить следующий буфер из потока.
                  * @param buffer Ссылка на буфер.
                  * @return Если поток не закончился возвращает false, иначе
                  *         возвращает true и переводит поток на начало.
                */

                virtual bool nextBuffer(Buffer& buffer) = 0;

        };

    }

}

#endif

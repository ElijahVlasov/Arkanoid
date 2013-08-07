#ifndef _SALT2D_UTILS_AUDIO_AUDIOMANAGER_HPP
#define _SALT2D_UTILS_AUDIO_AUDIOMANAGER_HPP


#include <list>
#include <stdexcept>

#include <Utils/Singleton.hpp>

#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace Audio {

        /** Менеджер аудио.
          * Используется для инициализации звуковой системы и проверки ошибок.
          * Для коректности вывода звука, необходимо вызывать AudioManager::update().
          * @author Elijah Vlasov
        */

        class AudioManager: public Singleton<AudioManager> {

            SINGLETON(AudioManager)

            public:

                /** Создать проигрыватель для звука.
                  * Следует использывать этот метод, а не конструктор проигрывателя.
                */

                boost::shared_ptr<SoundPlayer> createSoundPlayer(const boost::shared_ptr<Sound>& sound);

                /** Обновить состояние аудио.
                  * Может быть очень затратным при большом количестве проигрываемых звуков.
                */

                void update()                   throw(std::runtime_error);

                /** Проверить OpenAL-ошибки.
                  * @throws Генерирует std::runtime_error, если ошибки есть.
                */

                static void CheckALErrors()     throw(std::runtime_error);

                /** Проверить ALC-ошибки.
                  * @throws Генерирует std::runtime_error, если ошибки есть.
                */

                static void CheckALCErrors()    throw(std::runtime_error);

            protected:

                AudioManager() throw(std::runtime_error);
                ~AudioManager();

            private:

                std::list< boost::shared_ptr<SoundPlayer> > players_;

                ALCdevice*  device_;
                ALCcontext* context_;

        };

    }

}

#endif

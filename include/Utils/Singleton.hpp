/*******************************************
    
    Шаблонный класс - синглтон. Для 
    создания синглтона использовать этот 
    класс.

*******************************************/

#ifndef _SALT2D_UTILS_SINGLETON_HPP
#define _SALT2D_UTILS_SINGLETON_HPP

#include <cstdint>

#include <stdexcept>

#include <boost/thread/mutex.hpp>

#include <boost/utility.hpp>

#define SINGLETON(CLASS_NAME) friend class Utils::Singleton<CLASS_NAME>;

namespace Utils {	

    template <class T> class Singleton: public boost::noncopyable {
		
        public:

            // Получить объект синглтона, конструктор
            // объекта может сгенерировать runtime_error
            static T* getInstance() throw(std::runtime_error) {
	
                boost::lock_guard<boost::mutex> guard(singletonMutex_);

                if(instance_ == 0) {
	
                    instance_ = new T();
					
                }

                refCount_++;

                return instance_;

            }

            // освободить синглтон
            void Free() {
 
                boost::lock_guard<boost::mutex> guard(singletonMutex_);

                if(instance_ == 0) {
                    return;
                }

                if(--refCount_ <= 0) {
                    delete instance_;
                }

            }

        protected:		

            Singleton() {}

            virtual ~Singleton() {
                instance_ = 0;
            }

            static boost::mutex singletonMutex_;

        private:

            static T* instance_;
            // кол - во указателей на синглтон
            static size_t refCount_;

    };

    template <class T> T*			Singleton<T>::instance_		 = 0;
    template <class T> size_t		Singleton<T>::refCount_		 = 0;
    template <class T> boost::mutex	Singleton<T>::singletonMutex_;

}

#endif

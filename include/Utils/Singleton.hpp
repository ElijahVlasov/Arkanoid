/*******************************************
    
    ��������� ����� - ��������. ��� 
    �������� ��������� ������������ ���� 
    �����.

*******************************************/

#ifndef _SALT2D_UTILS_SINGLETON_HPP
#define _SALT2D_UTILS_SINGLETON_HPP

#include <boost/cstdint.hpp>

#include <stdexcept>

#include <mutex>

#include <boost/thread/lock_guard.hpp>

#include <boost/utility.hpp>

#define SINGLETON(CLASS_NAME) friend class Utils::Singleton<CLASS_NAME>;

namespace Utils {	

    template <class T> class Singleton: public boost::noncopyable {
		
        public:

            // �������� ������ ���������, �����������
            // ������� ����� ������������� runtime_error
            static T* getInstance() throw(std::runtime_error) {
	
                boost::lock_guard<std::mutex> guard(singletonMutex_);

                if(instance_ == 0) {
	
                    instance_ = new T();
					
                }

                refCount_++;

                return instance_;

            }

            // ���������� ��������
            void Free() {
 
                boost::lock_guard<std::mutex> guard(singletonMutex_);

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

            static std::mutex singletonMutex_;

        private:

            static T* instance_;
            // ��� - �� ���������� �� ��������
            static size_t refCount_;

    };

    template <class T> T*           Singleton<T>::instance_      = 0;
    template <class T> size_t       Singleton<T>::refCount_      = 0;
    template <class T> std::mutex   Singleton<T>::singletonMutex_;

}

#endif

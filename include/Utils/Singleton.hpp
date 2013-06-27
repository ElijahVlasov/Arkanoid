#ifndef _SALT2D_UTILS_SINGLETON_HPP
#define _SALT2D_UTILS_SINGLETON_HPP

#include <boost/cstdint.hpp>

#include <stdexcept>

#include <mutex>

#include <boost/utility.hpp>

#define SINGLETON(CLASS_NAME)   friend class Utils::Singleton<CLASS_NAME>; \
                                friend void boost::intrusive_ptr_add_ref<CLASS_NAME>(CLASS_NAME*); \
                                friend void boost::intrusive_ptr_release<CLASS_NAME>(CLASS_NAME*);

namespace Utils {

    /** Шаблон для создания синглтонов.
      * Чтобы создать синглтон T нужно отнаследовать от Singleton<T>
      * и в любом месте класса поместить макрос SINGLETON(T).
      * @author Elijah Vlasov
    */

    template <class T> class Singleton: public boost::noncopyable {

        public:

            /** Получить объект синглтона.
              * Создает синглтон или увеличивает счетчик ссылок.
              * @throw Конструктор дочернего класса может сгенерировать std::runtime_error
            */

            static T* getInstance() throw(std::runtime_error) {

                std::lock_guard<std::mutex> guard(singletonMutex_);

                if(instance_ == 0) {

                    instance_ = new T();

                }

                refCount_++;

                return instance_;

            }



            /** Освободить синглтон.
              * Уменьшает счетчик ссылок или удаляет синглтон.
            */

            void Free() {
 
                std::lock_guard<std::mutex> guard(singletonMutex_);

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

            static T* instance_;
            // кол - во указателей на синглтон
            static size_t refCount_;

    };

    template <class T> T*           Singleton<T>::instance_      = 0;
    template <class T> size_t       Singleton<T>::refCount_      = 0;
    template <class T> std::mutex   Singleton<T>::singletonMutex_;

}


namespace boost {

    template <class T> void intrusive_ptr_add_ref(T* singleton) {
        singleton->refCount_ ++;
    }



    template <class T> void intrusive_ptr_release(T* singleton) {
        singleton->Free();
    }

}


#endif

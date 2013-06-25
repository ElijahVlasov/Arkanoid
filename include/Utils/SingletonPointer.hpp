#ifndef _SALT2D_UTILS_SINGLETONPOINTER_HPP
#define _SALT2D_UTILS_SINGLETONPOINTER_HPP

#include <stdexcept>

namespace Utils {

    template <class T> class SingletonPointer {

        public:

            SingletonPointer() throw(std::runtime_error):
                singletonPointer_(T::getInstance())
            {}

            SingletonPointer(T* pointer):
                singletonPointer_(pointer)
            {}



            SingletonPointer(const SingletonPointer& singletonPointer) {

                if(singletonPointer.singletonPointer_ == 0) {

                    singletonPointer_ = 0;
                    return;

                }

                try {
                    singletonPointer_ = T::getInstance();
                } catch(const std::runtime_error&) {
                    singletonPointer_ = 0;
                }

            }



            ~SingletonPointer() {

                if(singletonPointer_ != 0) {
                    singletonPointer_->Free();
                }

            }



            T* operator -> () {
                return singletonPointer_;
            }



            T& operator * () {
                return *singletonPointer_;
            }



            SingletonPointer <T>& operator = (T* pointer) {

                if(singletonPointer_ != 0) {
                    singletonPointer_->Free();
                }

                singletonPointer_ = pointer;

                return *this;

            }



            SingletonPointer <T>& operator = (const SingletonPointer <T>& singletonPointer) {

                if(singletonPointer_ != 0) {
                    singletonPointer_->Free();
                }

                singletonPointer_ = singletonPointer.singletonPointer_;

                return *this;

            }



            T* get() {
                return singletonPointer_;
            }



        private:

            T* singletonPointer_;

    };

}

#endif

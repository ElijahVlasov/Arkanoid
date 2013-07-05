#ifndef _SALT2D_UTILS_SINGLETONPOINTER_HPP
#define _SALT2D_UTILS_SINGLETONPOINTER_HPP

namespace Utils {

	template <class T> class SingletonPointer {

		public:

			SingletonPointer():
				singleton_(0)
			{}



			SingletonPointer(T* singleton):
				singleton_(singleton)
			{}



			SingletonPointer(const SingletonPointer<T>& pointer):
				singleton_(pointer.singleton_)
			{
				singleton_->addRef();
			}



			~SingletonPointer() {

				if(singleton_ == 0) {
					return;
				}

				singleton_->Free();
			}



			SingletonPointer<T>& operator = (T* pointer) {

				if(singleton_ != 0) {
					singleton_->Free();
				}

				singleton_ = pointer;

				return *this;

			}



			inline bool operator == (const SingletonPointer<T>& singletonPointer) { return singleton_ == singletonPointer.singleton_; }
			inline bool operator != (const SingletonPointer<T>& singletonPointer) { return singleton_ != singletonPointer.singleton_; }
			inline bool operator == (const T* pointer) { return singleton_ == pointer; }
			inline bool operator != (const T* pointer) { return singleton_ != pointer; }



			T* get() {
				return singleton_;
			}



			T* operator -> () {
				return singleton_;
			}

		private:

			SingletonPointer<T>& operator = (const SingletonPointer<T>&){ return *this; }

			T* singleton_;

	};

}

#endif

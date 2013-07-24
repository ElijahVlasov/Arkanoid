#ifndef _SALT2D_UTILS_SINGLETONPTR_HPP
#define _SALT2D_UTILS_SINGLETONPTR_HPP

namespace boost {

    template <class T> void intrusive_ptr_add_ref(T* singleton) {
        singleton->addRef();
    }



    template <class T> void intrusive_ptr_release(T* singleton) {
        singleton->Free();
    }

}

#endif

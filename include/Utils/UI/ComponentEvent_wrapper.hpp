#ifndef _SALT2D_UTILS_UI_COMPONENTEVENT_WRAPPER_HPP
#define _SALT2D_UTILS_UI_COMPONENTEVENT_WRAPPER_HPP

#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils.hpp>

#include <Utils/assert.hpp>

namespace Utils {

    namespace UI {
    
        /** Класс-обертка над вызовом Lua-функции
          * обработчика события.
          * @author Elijah Vlasov
        */

        template<class EventType> class ComponentEvent_wrapper {
	
            public:
            
                /** Создать обертку над функцией.
                  * @param funcName имя функции
                  * @throws Генерирует std::invalid_argument, если
                  *         funcName == NULL или funcName - пустая строка.
                  *         Генерирует std::runtime_error, если произошла ошибка
                  *         Lua.
                */
			
                explicit ComponentEvent_wrapper(const char* funcName)		
                                    throw(std::invalid_argument, std::runtime_error):
                            lua_(Lua::getInstance()),
                            functionObject_()
                {
                    ASSERT(
                        (funcName != 0),
                        std::invalid_argument("funcName")
                    );

                    ASSERT(
                        (strlen(funcName) != 0),
                        std::invalid_argument("funcName")
                    );

                    functionObject_ = lua_->getFunctionObject(funcName);

                }

                /** Создать обертку над функцией.
                  * @param funcName имя функции
                  * @throw Генерирует std::invalid_argument, если funcName
                  *        пустая строка. Генерирует std::runtime_error, если
                  *        произошла ошибка Lua.
                */

                explicit ComponentEvent_wrapper(const std::string& funcName)	
                                    throw(std::invalid_argument, std::runtime_error):
                            lua_(Lua::getInstance()),
                            functionObject_()
                {

                    ASSERT(
                        (!funcName.empty()),
                        std::invalid_argument("funcName")
                    );

                    functionObject_ = lua_->getFunctionObject(funcName);

                }



                ComponentEvent_wrapper(const ComponentEvent_wrapper& wrapper)			
                                    throw(std::runtime_error):
                            lua_(Lua::getInstance()),
                            functionObject_(wrapper.functionObject_) 
                {}



                ~ComponentEvent_wrapper() {
				
                    if(lua_ != 0) {
                        lua_->Free();
                    }

                }


				
                ComponentEvent_wrapper& operator= (const ComponentEvent_wrapper& wrapper) {
					
                    functionObject_ = wrapper.functionObject_;

                    return *this;

                }

                /** Вызвать функцию.
                */

                void operator() (EventType& event) {
				
                    try {
		
                        luabind::call_function<void>(functionObject_, boost::ref(event));

                    } catch(const luabind::error&) {
                        return;
                    }

                }

            private:

                Utils::Lua* lua_;
				
                luabind::object functionObject_;

        };

    }

}

#endif

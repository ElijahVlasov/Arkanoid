/****************************************

        Обертка над вызовом, Lua-
        обработчика	события.

*****************************************/

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

        template<class EventType> class ComponentEvent_wrapper {
	
            public:
			
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

                    functionObject_ = lua_->getFunctionObject(string(funcName));

                }



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
#ifndef _SALT2D_ENGINE_ENGINE_HPP
#define _SALT2D_ENGINE_ENGINE_HPP

#include <boost/thread/thread.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>

#include <Engine/Game.hpp>

using Utils::Singleton;

namespace Engine {
	
	class SaltEngine: public Singleton<SaltEngine> {
		
		SINGLETON(SaltEngine)

		public:

//			void setGame(const Game* game);

			void onRender();

			void run();

		protected:

			SaltEngine();
			virtual ~SaltEngine();

			//friend boost::thread;

		private:

			boost::thread engineThread;

			void operator() ();

			Utils::Lua*	lua_;

		//	Game* game;

	};

}



#endif

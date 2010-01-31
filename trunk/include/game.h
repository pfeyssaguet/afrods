#ifndef __GAME_H_
#define __GAME_H_

#include "context.h"

namespace AfroDS {

	class Game {
		public:
			void init();
			void run();

			static Game * getInstance();

		private:
			Game();

			Context * m_context;

			/** Le Singleton */
			static Game * m_Instance;
	};

}

#endif

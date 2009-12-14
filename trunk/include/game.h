#ifndef __GAME_H__
#define __GAME_H__

#include "map.h"
#include "module.h"
#include "character.h"

#define AFRODS_GAME_OFFSET_ICONS_X 216
#define AFRODS_GAME_OFFSET_ICONS_Y 8
#define AFRODS_GAME_OFFSET_ICONS_SPACE 0


namespace AfroDS {

	class Game : public AfroDS::Module {
		public:
			Game();
			~Game();
			void moduleEvents();

		private:
			void initMenu();
			bool moveChar();
			void quit();
			AfroDS::Character m_activeChar;
			AfroDS::Map m_activeMap;
	};

}

#endif

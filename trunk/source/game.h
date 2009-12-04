#ifndef __GAME_H__
#define __GAME_H__

#include "module.h"
#include "character.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

class Game : public Module {
	public:
		Game();
		~Game();
		void moduleEvents();

		void quit();

	private:
		Character m_activeChar;
};

#endif

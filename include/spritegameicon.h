#ifndef __SPRITEGAMEICON_H__
#define __SPRITEGAMEICON_H__

#include "sprite.h"

namespace AfroDS {
	/**
	 * Repr�sente les frames des diff�rentes ic�nes
	 */
	enum GameIconType {ICON_STATUS = 0, ICON_INVENTORY = 1, ICON_EQUIPMENT = 2, ICON_OPTIONS = 3, ICON_QUIT = 4};

	class SpriteGameIcon : public Sprite {
		public:
			/**
			 * Constructeur : cr�e un sprite avec l'ic�ne demand�e
			 * @param GameIconType type type d'ic�ne
			 */
			SpriteGameIcon(GameIconType type);
		private:
			/** Type d'ic�ne */
			GameIconType m_type;
	};
}

#endif

#ifndef __SPRITEGAMEICON_H__
#define __SPRITEGAMEICON_H__

#include "sprite.h"

namespace AfroDS {
	/**
	 * Représente les frames des différentes icônes
	 */
	enum GameIconType {ICON_STATUS = 0, ICON_INVENTORY = 1, ICON_EQUIPMENT = 2, ICON_OPTIONS = 3, ICON_QUIT = 4};

	class SpriteGameIcon : public Sprite {
		public:
			/**
			 * Constructeur : crée un sprite avec l'icône demandée
			 * @param GameIconType type type d'icône
			 */
			SpriteGameIcon(GameIconType type);
		private:
			/** Type d'icône */
			GameIconType m_type;
	};
}

#endif

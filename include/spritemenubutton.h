#ifndef __SPRITEMENUBUTTON_H__
#define __SPRITEMENUBUTTON_H__


#include "sprite.h"
#include <vector>

namespace AfroDS {
	/**
	 * Repr�sente un sprite de bouton de menu dans le module Menu.
	 * Le sprite est compos� de 6 petits sprites de 32x32 les uns � c�t� des autres
	 */
	class SpriteMenuButton {
		public:
			/**
			 * Constructeur : cr�e les 6 sous-sprites
			 * @param Coords coords coordonn�es d'origine du 1er sprite
			 */
			SpriteMenuButton(Coords coords);

			/**
			 * Destructeur : d�truit les 6 sous-sprites
			 */
			~SpriteMenuButton();

			/**
			 * Appelle les 6 m�thodes updates des sous-sprites
			 */
			void update();

			/**
			 * Positionne les 6 sprites par rapport aux coordonn�es du 1er
			 * @param Coords coords coordonn�es d'origine du 1er sprite
			 */
			void setPos(Coords coords);

			/**
			 * Permet de savoir si les coordonn�es demand�es sont dans la zone du sprite
			 * @param int x coordonn�e X
			 * @param int y coordonn�e Y
			 * @return bool true si les coordonn�es sont dans la zone du sprite
			 */
			bool isInZone(int x, int y);

			/**
			 * Permet de savoir si les coordonn�es demand�es sont dans la zone du sprite
			 * @param Coords coords coordonn�es
			 * @return bool true si les coordonn�es sont dans la zone du sprite
			 */
			bool isInZone(Coords coords);

			/**
			 * Renvoie le num�ro du 1er sprite.
			 * Attention : les 5 suivants ne sont pas forc�ment adjacents.
			 * @return short num�ro du 1er sprite
			 */
			short getFirstSpriteNum();
		private:
			/** Coordonn�es du 1er sprite */
			Coords m_coords;

			/** Vector contenant les 6 sprites */
			std::vector<Sprite *> m_sprites;
	};
}

#endif

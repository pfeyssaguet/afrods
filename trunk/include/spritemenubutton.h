#ifndef __SPRITEMENUBUTTON_H__
#define __SPRITEMENUBUTTON_H__


#include "sprite.h"
#include <vector>

namespace AfroDS {
	/**
	 * Représente un sprite de bouton de menu dans le module Menu.
	 * Le sprite est composé de 6 petits sprites de 32x32 les uns à côté des autres
	 */
	class SpriteMenuButton {
		public:
			/**
			 * Constructeur : crée les 6 sous-sprites
			 * @param Coords coords coordonnées d'origine du 1er sprite
			 */
			SpriteMenuButton(Coords coords);

			/**
			 * Destructeur : détruit les 6 sous-sprites
			 */
			~SpriteMenuButton();

			/**
			 * Appelle les 6 méthodes updates des sous-sprites
			 */
			void update();

			/**
			 * Positionne les 6 sprites par rapport aux coordonnées du 1er
			 * @param Coords coords coordonnées d'origine du 1er sprite
			 */
			void setPos(Coords coords);

			/**
			 * Permet de savoir si les coordonnées demandées sont dans la zone du sprite
			 * @param int x coordonnée X
			 * @param int y coordonnée Y
			 * @return bool true si les coordonnées sont dans la zone du sprite
			 */
			bool isInZone(int x, int y);

			/**
			 * Permet de savoir si les coordonnées demandées sont dans la zone du sprite
			 * @param Coords coords coordonnées
			 * @return bool true si les coordonnées sont dans la zone du sprite
			 */
			bool isInZone(Coords coords);

			/**
			 * Renvoie le numéro du 1er sprite.
			 * Attention : les 5 suivants ne sont pas forcément adjacents.
			 * @return short numéro du 1er sprite
			 */
			short getFirstSpriteNum();
		private:
			/** Coordonnées du 1er sprite */
			Coords m_coords;

			/** Vector contenant les 6 sprites */
			std::vector<Sprite *> m_sprites;
	};
}

#endif

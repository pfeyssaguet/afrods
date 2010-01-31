#ifndef __SPRITECHAR_H__
#define __SPRITECHAR_H__

#include "sprite.h"

// nombre de frames pour une animation dans la planche
#define AFRODS_SPRITECHAR_NB_FRAMES 3

namespace AfroDS {
	/**
	 * Repr�sente les directions dans les animations
	 */
	enum SpriteDirection {DIR_NOTHING = -1, DIR_UP = 0, DIR_RIGHT = 1, DIR_DOWN = 2, DIR_LEFT = 3};

	/**
	 * Repr�sente un sprite de perso (h�rite de Sprite).
	 * Permet de g�rer finement les animations du perso
	 */
	class SpriteChar : public Sprite {
		public:
			/**
			 * Constructeur : cr�e un sprite de character sur l'�cran demand�
			 * @param short screen �cran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 */
			SpriteChar(short screen);

			/**
			 * Constructeur qui permet d'utiliser un autre graphisme que celui par d�faut
			 * @param short screen �cran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite : graphisme � utiliser
			 */
			SpriteChar(short screen, GraphicsSprite sprite);

			/**
			 * Destructeur : supprime le sprite
			 */
			~SpriteChar();

			/**
			 * Renvoie la direction courante
			 * @return SpriteDirection direction
			 */
			SpriteDirection getCurrentDir();

			/**
			 * D�finit la direction courante
			 * @param SpriteDirection direction
			 */
			void setCurrentDir(SpriteDirection direction);

			/**
			 * Anime le perso avec sa direction courante,
			 * sur le nombre de frames d�fini par AFRODS_SPRITECHAR_NB_FRAMES
			 */
			void animate();

			/**
			 * Remet le perso sur l'animation par d�faut,
			 * selon sa direction courante
			 */
			void setDefaultAnim();
		private:
			/** Direction couranet du perso */
			SpriteDirection m_current_dir;
	};
}

#endif

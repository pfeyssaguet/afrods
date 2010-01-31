#ifndef __SPRITECHAR_H__
#define __SPRITECHAR_H__

#include "sprite.h"

// nombre de frames pour une animation dans la planche
#define AFRODS_SPRITECHAR_NB_FRAMES 3

namespace AfroDS {
	/**
	 * Représente les directions dans les animations
	 */
	enum SpriteDirection {DIR_NOTHING = -1, DIR_UP = 0, DIR_RIGHT = 1, DIR_DOWN = 2, DIR_LEFT = 3};

	/**
	 * Représente un sprite de perso (hérite de Sprite).
	 * Permet de gérer finement les animations du perso
	 */
	class SpriteChar : public Sprite {
		public:
			/**
			 * Constructeur : crée un sprite de character sur l'écran demandé
			 * @param short screen écran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 */
			SpriteChar(short screen);

			/**
			 * Constructeur qui permet d'utiliser un autre graphisme que celui par défaut
			 * @param short screen écran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite : graphisme à utiliser
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
			 * Définit la direction courante
			 * @param SpriteDirection direction
			 */
			void setCurrentDir(SpriteDirection direction);

			/**
			 * Anime le perso avec sa direction courante,
			 * sur le nombre de frames défini par AFRODS_SPRITECHAR_NB_FRAMES
			 */
			void animate();

			/**
			 * Remet le perso sur l'animation par défaut,
			 * selon sa direction courante
			 */
			void setDefaultAnim();
		private:
			/** Direction couranet du perso */
			SpriteDirection m_current_dir;
	};
}

#endif

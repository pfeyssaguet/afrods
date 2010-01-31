#ifndef __SPRITEBATTLE_H__
#define __SPRITEBATTLE_H__

#include "sprite.h"

// nombre de frames pour une animation dans la planche du sprite  (1 animation par ligne)
#define AFRODS_SPRITEBATTLE_NB_FRAMES 3

namespace AfroDS {
	/** Animations du sprite de combat (1 animation par ligne) */
	enum SpriteBattleAnim {ANIM_0 = 0, ANIM_ATTACK = 1, ANIM_STUN = 2, ANIM_HIT = 3};

	/**
	 * Repr�sente un sprite de perso (h�rite de Sprite).
	 * Permet de g�rer finement les animations du perso
	 */
	class SpriteBattle : public Sprite {
		public:
			/**
			 * Constructeur : cr�e un sprite de character sur l'�cran demand�
			 * @param short screen �cran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 */
			SpriteBattle(short screen);

			/**
			 * Constructeur qui permet d'utiliser un autre graphisme que celui par d�faut
			 * @param short screen �cran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite : graphisme � utiliser
			 */
			SpriteBattle(short screen, GraphicsSprite sprite);

			/**
			 * Destructeur : supprime le sprite
			 */
			~SpriteBattle();

			SpriteBattleAnim getCurrentAnim();
			void setCurrentAnim(SpriteBattleAnim anim);

			/**
			 * Anime le perso avec sa direction courante,
			 * sur le nombre de frames d�fini par AFRODS_SPRITEBATTLE_NB_FRAMES
			 */
			void animate();

			/**
			 * Remet le perso sur l'animation par d�faut,
			 * selon sa direction courante
			 */
			void setDefaultAnim();

			void launchAnim(SpriteBattleAnim anim);
		private:
			SpriteBattleAnim m_current_anim;
	};
}

#endif

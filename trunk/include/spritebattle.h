#ifndef __SPRITEBATTLE_H__
#define __SPRITEBATTLE_H__

#include "sprite.h"

// nombre de frames pour une animation dans la planche du sprite  (1 animation par ligne)
#define AFRODS_SPRITEBATTLE_NB_FRAMES 3

namespace AfroDS {
	/** Animations du sprite de combat (1 animation par ligne) */
	enum SpriteBattleAnim {ANIM_0 = 0, ANIM_ATTACK = 1, ANIM_STUN = 2, ANIM_HIT = 3};

	/**
	 * Représente un sprite de perso (hérite de Sprite).
	 * Permet de gérer finement les animations du perso
	 */
	class SpriteBattle : public Sprite {
		public:
			/**
			 * Constructeur : crée un sprite de character sur l'écran demandé
			 * @param short screen écran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 */
			SpriteBattle(short screen);

			/**
			 * Constructeur qui permet d'utiliser un autre graphisme que celui par défaut
			 * @param short screen écran : utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite : graphisme à utiliser
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
			 * sur le nombre de frames défini par AFRODS_SPRITEBATTLE_NB_FRAMES
			 */
			void animate();

			/**
			 * Remet le perso sur l'animation par défaut,
			 * selon sa direction courante
			 */
			void setDefaultAnim();

			void launchAnim(SpriteBattleAnim anim);
		private:
			SpriteBattleAnim m_current_anim;
	};
}

#endif

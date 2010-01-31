#include "spritebattle.h"
#include "constants.h"

using namespace AfroDS;

/**
 * Constructeur : crée un sprite de character sur l'écran demandé
 * @param short screen écran : utiliser SCREEN_MAIN ou SCREEN_SUB
 */
SpriteBattle::SpriteBattle(short screen) : Sprite(screen, SPRITE_BATTLE_WARRIOR) {
	setDefaultAnim();
}

SpriteBattle::SpriteBattle(short screen, GraphicsSprite sprite) : Sprite(screen, sprite) {
	setDefaultAnim();
}

/**
 * Destructeur : supprime le sprite
 */
SpriteBattle::~SpriteBattle() {

}

void SpriteBattle::setCurrentAnim(SpriteBattleAnim anim) {
	m_current_anim = anim;
}

SpriteBattleAnim SpriteBattle::getCurrentAnim() {
	return m_current_anim;
}

/**
 * Anime le perso avec sa direction courante,
 * sur le nombre de frames défini par AFRODS_SPRITEBATTLE_NB_FRAMES
 */
void SpriteBattle::animate() {
	// on calcule la frame courante
	int pix_per_frame = m_dimensions.x * m_dimensions.y;
	int frame = m_current_anim * AFRODS_SPRITEBATTLE_NB_FRAMES + m_current_frame;
	u8* offset = (u8*)m_description.tiles + frame * pix_per_frame;

	// on copie la frame en mémoire
	dmaCopy(offset, m_gfx, pix_per_frame);

	// toutes les X frames on change de frame
	static int iAnims = 0;
	static bool sens = true;

	iAnims++;
	if (iAnims > 10) {
		iAnims = 0;
		if (sens) {
			m_current_frame++;
			if (m_current_frame == AFRODS_SPRITEBATTLE_NB_FRAMES - 1)
				sens = false;
		}
		else {
			m_current_frame--;
			if (m_current_frame == 0)
				sens = true;
		}
	}
}

/**
 * Remet le perso sur l'animation par défaut,
 * selon sa direction courante
 */
void SpriteBattle::setDefaultAnim() {
	m_current_anim = ANIM_ATTACK;
	m_current_frame = 0;
	animate();
}

void SpriteBattle::launchAnim(SpriteBattleAnim anim) {
	m_current_anim = anim;
	m_current_frame = 0;
	Coords oldPos = m_pos;

	if (anim == ANIM_ATTACK) {
		m_pos.x += 30;
	} else if (anim == ANIM_HIT) {
		m_pos.x -= 20;
	}

	do {
		// on calcule la frame courante
		int pix_per_frame = m_dimensions.x * m_dimensions.y;
		int frame = m_current_anim * AFRODS_SPRITEBATTLE_NB_FRAMES + m_current_frame;
		u8* offset = (u8*)m_description.tiles + frame * pix_per_frame;

		// on copie la frame en mémoire
		dmaCopy(offset, m_gfx, pix_per_frame);

		for (int i = 0 ; i < 10 ; i++) {

			update();
			swiWaitForVBlank();
			GraphicsEngine::updateOam(m_screen);
		}
		m_current_frame++;
	} while (m_current_frame != AFRODS_SPRITEBATTLE_NB_FRAMES);
	m_pos = oldPos;
	setDefaultAnim();
}

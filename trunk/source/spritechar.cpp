#include "spritechar.h"

using namespace AfroDS;

/**
 * Constructeur : cr�e un sprite de character sur l'�cran demand�
 * @param short screen �cran : utiliser SCREEN_MAIN ou SCREEN_SUB
 */
SpriteChar::SpriteChar(short screen) : Sprite(screen, SPRITE_HUMAN) {
	m_current_dir = DIR_DOWN;
	setDefaultAnim();
}

SpriteChar::SpriteChar(short screen, GraphicsSprite sprite) : Sprite(screen, sprite) {
	m_current_dir = DIR_DOWN;
	setDefaultAnim();
}

/**
 * Destructeur : supprime le sprite
 */
SpriteChar::~SpriteChar() {

}

/**
 * Renvoie la direction courante
 * @return SpriteDirection direction
 */
SpriteDirection SpriteChar::getCurrentDir() {
	return m_current_dir;
}

/**
 * D�finit la direction courante
 * @param SpriteDirection direction
 */
void SpriteChar::setCurrentDir(SpriteDirection direction) {
	m_current_dir = direction;
}

/**
 * Anime le perso avec sa direction courante,
 * sur le nombre de frames d�fini par AFRODS_SPRITECHAR_NB_FRAMES
 */
void SpriteChar::animate() {
	// on calcule la frame courante
	int pix_per_frame = 32*32;
	int frame = m_current_dir * AFRODS_SPRITECHAR_NB_FRAMES + m_current_frame;
	u8* offset = (u8*)m_description.tiles + frame * pix_per_frame;

	// on copie la frame en m�moire
	dmaCopy(offset, m_gfx, pix_per_frame);

	// toutes les X frames on change de frame
	static int iAnims = 0;
	static bool sens = true;

	iAnims++;
	if (iAnims > 10) {
		iAnims = 0;
		if (sens) {
			m_current_frame++;
			if (m_current_frame == AFRODS_SPRITECHAR_NB_FRAMES - 1)
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
 * Remet le perso sur l'animation par d�faut,
 * selon sa direction courante
 */
void SpriteChar::setDefaultAnim() {
	m_current_frame = 1;
	animate();
}

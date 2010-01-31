#include "spritegameicon.h"
#include "constants.h"

using namespace AfroDS;

/**
 * Constructeur : cr�e un sprite avec l'ic�ne demand�e
 * @param GameIconType type type d'ic�ne
 */
SpriteGameIcon::SpriteGameIcon(GameIconType type) : Sprite(SCREEN_SUB, SPRITE_GAME_ICONS), m_type(type) {
	// on calcule la frame courante
	setCurrentFrame(m_type);
}

#include "spritegameicon.h"
#include "constants.h"

using namespace AfroDS;

/**
 * Constructeur : crée un sprite avec l'icône demandée
 * @param GameIconType type type d'icône
 */
SpriteGameIcon::SpriteGameIcon(GameIconType type) : Sprite(SCREEN_SUB, SPRITE_GAME_ICONS), m_type(type) {
	// on calcule la frame courante
	setCurrentFrame(m_type);
}

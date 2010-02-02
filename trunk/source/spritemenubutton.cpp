#include "spritemenubutton.h"
#include "constants.h"

#include <nds.h>
#include <vector>

using namespace AfroDS;

/**
 * Constructeur : crée les 6 sous-sprites
 * @param Coords coords coordonnées d'origine du 1er sprite
 */
SpriteMenuButton::SpriteMenuButton(Coords coords) : m_coords(coords) {
	// on crée les 6 sprites
	for (int i = 0 ; i <= 5 ; i++) {
		// on crée un sprite
		Sprite * sprite = new Sprite(SCREEN_SUB, SPRITE_MENU_BUTTON);

		// on choisit la frame correspondant au numéro
		sprite->setCurrentFrame(i);

		// on place le sprite
		sprite->setPosY(m_coords.y);
		sprite->setPosX(m_coords.x + i * sprite->getWidth());

		// on le met dans le vector
		m_sprites.push_back(sprite);
	}
}

/**
 * Destructeur : détruit les 6 sous-sprites
 */
SpriteMenuButton::~SpriteMenuButton() {
	// on parcourt les sprites tant qu'il y en a
	while (!m_sprites.empty()) {
		delete m_sprites.at(0);
		m_sprites.erase(m_sprites.begin());
	}
}

/**
 * Appelle les 6 méthodes updates des sous-sprites
 */
void SpriteMenuButton::update() {
	// on parcourt les 6 sprites
	for (unsigned int i = 0 ; i < m_sprites.size() ; i++) {
		// on récupère le sprite
		Sprite * sprite = m_sprites.at(i);

		// on l'update
		sprite->update();
	}
}

/**
 * Positionne les 6 sprites par rapport aux coordonnées du 1er
 * @param Coords coords coordonnées d'origine du 1er sprite
 */
void SpriteMenuButton::setPos(Coords coords) {
	m_coords = coords;
	// on parcourt les 6 sprites
	for (unsigned int i = 0 ; i < m_sprites.size() ; i++) {
		// on récupère le sprite
		Sprite * sprite = m_sprites.at(i);

		// on le positionne
		sprite->setPosY(m_coords.y);
		sprite->setPosX(m_coords.x + i * sprite->getWidth());
	}
}

/**
 * Permet de savoir si les coordonnées demandées sont dans la zone du sprite
 * @param int x coordonnée X
 * @param int y coordonnée Y
 * @return bool true si les coordonnées sont dans la zone du sprite
 */
bool SpriteMenuButton::isInZone(int x, int y) {
	// on appelle l'autre version de la méthode
	return isInZone(Coords(x, y));
}

/**
 * Permet de savoir si les coordonnées demandées sont dans la zone du sprite
 * @param Coords coords coordonnées
 * @return bool true si les coordonnées sont dans la zone du sprite
 */
bool SpriteMenuButton::isInZone(Coords coords) {
	// on parcourt les 6 sprites
	for (unsigned int i = 0 ; i < m_sprites.size() ; i++) {
		// on récupère le sprite
		Sprite * sprite = m_sprites.at(i);

		// si le sprite courant est dans la zone, on renvoie true
		if (sprite->isInZone(coords)) {
			return true;
		}
	}
	// on a aucun sprite dans la zone, on renvoie false
	return false;
}

/**
 * Renvoie le numéro du 1er sprite.
 * Attention : les 5 suivants ne sont pas forcément adjacents.
 * @return short numéro du 1er sprite
 */
short SpriteMenuButton::getFirstSpriteNum() {
	Sprite * sprite = m_sprites.at(0);
	return sprite->getSpriteNum();
}

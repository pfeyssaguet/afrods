#include "sprite.h"
#include "constants.h"

#include <nds.h>

#include <set>
#include <stdio.h>

using namespace AfroDS;

/**
 * Constructeur : crée le sprite
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param GraphicsSprite sprite sprite à utiliser
 */
Sprite::Sprite(short screen, GraphicsSprite sprite) {
	m_gfx = NULL;
	m_screen = screen;
	m_description = GraphicsEngine::getInstance()->getSpriteDescription(sprite);

	/*
	 * Les différentes tailles de sprites de l'enum SpriteSize (libnds)
	 *    SpriteSize_8x8
	 *    SpriteSize_16x16
	 *    SpriteSize_32x32
	 *    SpriteSize_64x64
	 *
	 *    SpriteSize_16x8
	 *    SpriteSize_32x8
	 *    SpriteSize_32x16
	 *    SpriteSize_64x32
	 *
	 *    SpriteSize_8x16
	 *    SpriteSize_8x32
	 *    SpriteSize_16x32
	 *    SpriteSize_32x64
	 */

	// pour le doigt on utilise un sprite de 16x16
	if (sprite == SPRITE_FINGER) {
		m_size = SpriteSize_16x16;
		m_dimensions = Coords(16, 16);
	}
	// pour les mobs on utilise des sprites de 64x64
	else if (sprite == SPRITE_MONSTERS64_1) {
		m_size = SpriteSize_64x64;
		m_dimensions = Coords(64, 64);
	}
	// pour tous les autres sprites on utilise du 32x32
	else {
		m_size = SpriteSize_32x32;
		m_dimensions = Coords(32, 32);
	}
	m_color_format = SpriteColorFormat_256Color;
	m_current_frame = 0;
	m_pos.x = 0;
	m_pos.y = 0;
	m_priority = 1;
	m_visible = true;

	// on réserve un numéro de sprite
	m_num_sprite = GraphicsEngine::getInstance()->pickSpriteNum(m_screen);

	// création du sprite
	if (m_screen == SCREEN_MAIN) {
		m_gfx = oamAllocateGfx(&oamMain, m_size, m_color_format);
	} else {
		m_gfx = oamAllocateGfx(&oamSub, m_size, m_color_format);
	}

	// on copie les tiles
	dmaCopy(m_description.tiles, m_gfx, m_description.tilesLen);

	// on charge la palette
	m_pal = GraphicsEngine::getInstance()->getSpritePalette(m_screen, sprite);
	m_pal_len = GraphicsEngine::getInstance()->getSpritePaletteLen(m_screen, sprite);
	m_pal_num = GraphicsEngine::getInstance()->getSpritePaletteNum(m_screen, sprite);
}

/**
 * Destructeur : Supprime le sprite
 * Il est virtuel pour être appelé par les classes qui héritent de Sprite
 */
Sprite::~Sprite() {
	// on relâche le numéro de sprite qu'on a réservé
	GraphicsEngine::getInstance()->releaseSpriteNum(m_screen, m_num_sprite);

	if (m_gfx != NULL) {
		if (m_screen == SCREEN_MAIN) {
			// on cache le sprite
			oamClear(&oamMain, m_num_sprite, 1);
			// on libère la mémoire
			oamFreeGfx(&oamMain, m_gfx);
		} else {
			// on cache le sprite
			oamClear(&oamSub, m_num_sprite, 1);
			// on libère la mémoire
			oamFreeGfx(&oamSub, m_gfx);
		}
	}
}

/**
 * Renvoie le numéro du sprite
 * @return short numéro de sprite
 */
short Sprite::getSpriteNum() {
	return m_num_sprite;
}

/**
 * Met à jour le sprite par rapport à ses paramètres courants avec oamSet()
 */
void Sprite::update() {
	// on affiche le sprite
	if (m_screen == SCREEN_MAIN) {
		oamSet(
			&oamMain, // oam must be: &oamMain or &oamSub
			m_num_sprite, // id the oam number to be set [0 - 127]
			m_pos.x, // x the x location of the sprite in pixels
			m_pos.y, // y the y location of the sprite in pixels
			m_priority, // priority The sprite priority (0 to 3)
			m_pal_num, // palette_alpha the palette number for 4bpp and 8bpp (extended palette mode), or the alpha value for bitmap sprites (bitmap sprites must specify a value > 0 to display) [0-15]
			m_size, // size the size of the sprite
			m_color_format, // format the color format of the sprite
			m_gfx, // gfxOffset the video memory address of the sprite graphics (not an offset)
			-1, // affineIndex affine index to use (if < 0 or > 31 the sprite will be unrotated)
			false, // sizeDouble if affineIndex >= 0 this will be used to double the sprite size for rotation
			!m_visible, // hide if non zero (true) the sprite will be hidden
			false, // vflip flip the sprite vertically
			false, // hflip flip the sprite horizontally
			false // mosaic if true mosaic will be applied to the sprite
		);
	} else {
		oamSet(
			&oamSub, // oam must be: &oamMain or &oamSub
			m_num_sprite, // id the oam number to be set [0 - 127]
			m_pos.x, // x the x location of the sprite in pixels
			m_pos.y, // y the y location of the sprite in pixels
			m_priority, // priority The sprite priority (0 to 3)
			m_pal_num, // palette_alpha the palette number for 4bpp and 8bpp (extended palette mode), or the alpha value for bitmap sprites (bitmap sprites must specify a value > 0 to display) [0-15]
			m_size, // size the size of the sprite
			m_color_format, // format the color format of the sprite
			m_gfx, // gfxOffset the video memory address of the sprite graphics (not an offset)
			-1, // affineIndex affine index to use (if < 0 or > 31 the sprite will be unrotated)
			false, // sizeDouble if affineIndex >= 0 this will be used to double the sprite size for rotation
			!m_visible, // hide if non zero (true) the sprite will be hidden
			false, // vflip flip the sprite vertically
			false, // hflip flip the sprite horizontally
			false // mosaic if true mosaic will be applied to the sprite
		);
	}
}

/**
 * Définit la priorité du sprite (le layer sur lequel il est affiché)
 * Un sprite est toujours devant un background pour un layer donné.
 * Donc les sprites auront par défaut 1 comme priorité pour être derrière
 * le background 0 utilisé pour le texte
 * @param short priority priorité
 */
void Sprite::setPriority(short priority) {
	m_priority = priority;
}

/**
 * Renvoie la priorité du sprite
 * @return short priorité
 */
short Sprite::getPriority() {
	return m_priority;
}

/**
 * Renvoie la position X
 * @return int position X
 */
int Sprite::getPosX() const {
	return m_pos.x;
}

/**
 * Définit la position X
 * @param int x position X
 */
void Sprite::setPosX(const int x) {
	m_pos.x = x;
}

/**
 * Renvoie la position Y
 * @return int position Y
 */
int Sprite::getPosY() const {
	return m_pos.y;
}

/**
 * Définit la position Y
 * @param int y position Y
 */
void Sprite::setPosY(const int y) {
	m_pos.y = y;
}

/**
 * Renvoie la position avec un type personnalisé
 * @return AF_Coords position
 */
Coords Sprite::getPos() const {
	return m_pos;
}

/**
 * Définit la position avec un type personnalisé
 * @param AF_Coords pos position
 */
void Sprite::setPos(const Coords pos) {
	m_pos = pos;
}

Coords Sprite::getDimensions() const {
	return m_dimensions;
}

int Sprite::getWidth() const {
	return m_dimensions.x;
}

int Sprite::getHeight() const {
	return m_dimensions.y;
}

/**
 * Définit les positions de X et Y
 * @param int x position X
 * @param int y position Y
 */
void Sprite::setPos(const int x, const int y) {
	m_pos.x = x;
	m_pos.y = y;
}

/**
 * Affiche ou masque un sprite
 * @param bool visible true pour afficher le sprite
 */
void Sprite::setVisible(bool visible) {
	m_visible = visible;
}

/**
 * Permet de savoir si un point est dans la zone du sprite
 * @param int x coordonnée X
 * @param int y coordonnée Y
 * @return bool true si le point est dans la zone du sprite
 */
bool Sprite::isInZone(int x, int y) {
	Coords coords;
	coords.x = x;
	coords.y = y;
	return isInZone(coords);
}

/**
 * Permet de savoir si un point est dans la zone du sprite
 * @param Coords zone coordonnées
 * @return bool true si le point est dans la zone du sprite
 */
bool Sprite::isInZone(Coords zone) {
	if (zone.x >= m_pos.x && zone.x <= m_pos.x + getWidth()) {
		if (zone.y >= m_pos.y && zone.y <= m_pos.y + getHeight()) {
			return true;
		}
	}
	return false;
}

/**
 * Définit la frame courante du sprite
 * @param short frame frame à sélectionner
 */
void Sprite::setCurrentFrame(short frame) {
	m_current_frame = frame;
	// on calcule la frame courante
	int pix_per_frame = getWidth() * getHeight();
	u8* offset = (u8*)m_description.tiles + m_current_frame * pix_per_frame;

	// on copie la frame en mémoire
	dmaCopy(offset, m_gfx, pix_per_frame);
}

/**
 * Renvoie la frame courante
 * @return short frame courante
 */
short Sprite::getCurrentFrame() {
	return m_current_frame;
}

/**
 * Pour faire clignoter le sprite
 */
void Sprite::blink() {
	for (int i = 0 ; i < 8 ; i++) {
		m_visible = !m_visible;
		update();
		swiWaitForVBlank();
		GraphicsEngine::updateOam(m_screen);
	}
}

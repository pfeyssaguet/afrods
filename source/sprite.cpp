#include "sprite.h"
#include "constants.h"

#include <nds.h>

#include <set>
#include <stdio.h>

using namespace AfroDS;

/**
 * Constructeur : cr�e le sprite
 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param GraphicsSprite sprite sprite � utiliser
 */
Sprite::Sprite(short screen, GraphicsSprite sprite) {
	m_gfx = NULL;
	m_screen = screen;
	m_description = GraphicsEngine::getInstance()->getSpriteDescription(sprite);

	/*
	 * Les diff�rentes tailles de sprites de l'enum SpriteSize (libnds)
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

	// on r�serve un num�ro de sprite
	m_num_sprite = GraphicsEngine::getInstance()->pickSpriteNum(m_screen);

	// cr�ation du sprite
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
 * Il est virtuel pour �tre appel� par les classes qui h�ritent de Sprite
 */
Sprite::~Sprite() {
	// on rel�che le num�ro de sprite qu'on a r�serv�
	GraphicsEngine::getInstance()->releaseSpriteNum(m_screen, m_num_sprite);

	if (m_gfx != NULL) {
		if (m_screen == SCREEN_MAIN) {
			// on cache le sprite
			oamClear(&oamMain, m_num_sprite, 1);
			// on lib�re la m�moire
			oamFreeGfx(&oamMain, m_gfx);
		} else {
			// on cache le sprite
			oamClear(&oamSub, m_num_sprite, 1);
			// on lib�re la m�moire
			oamFreeGfx(&oamSub, m_gfx);
		}
	}
}

/**
 * Renvoie le num�ro du sprite
 * @return short num�ro de sprite
 */
short Sprite::getSpriteNum() {
	return m_num_sprite;
}

/**
 * Met � jour le sprite par rapport � ses param�tres courants avec oamSet()
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
 * D�finit la priorit� du sprite (le layer sur lequel il est affich�)
 * Un sprite est toujours devant un background pour un layer donn�.
 * Donc les sprites auront par d�faut 1 comme priorit� pour �tre derri�re
 * le background 0 utilis� pour le texte
 * @param short priority priorit�
 */
void Sprite::setPriority(short priority) {
	m_priority = priority;
}

/**
 * Renvoie la priorit� du sprite
 * @return short priorit�
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
 * D�finit la position X
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
 * D�finit la position Y
 * @param int y position Y
 */
void Sprite::setPosY(const int y) {
	m_pos.y = y;
}

/**
 * Renvoie la position avec un type personnalis�
 * @return AF_Coords position
 */
Coords Sprite::getPos() const {
	return m_pos;
}

/**
 * D�finit la position avec un type personnalis�
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
 * D�finit les positions de X et Y
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
 * @param int x coordonn�e X
 * @param int y coordonn�e Y
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
 * @param Coords zone coordonn�es
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
 * D�finit la frame courante du sprite
 * @param short frame frame � s�lectionner
 */
void Sprite::setCurrentFrame(short frame) {
	m_current_frame = frame;
	// on calcule la frame courante
	int pix_per_frame = getWidth() * getHeight();
	u8* offset = (u8*)m_description.tiles + m_current_frame * pix_per_frame;

	// on copie la frame en m�moire
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

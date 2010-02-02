#include "map.h"
#include "debug.h"

#include <nds.h>
#include <stdio.h>

using namespace AfroDS;


/**
 * Constructeur de map
 */
Map::Map() {
}

/**
 * Chargement des graphismes. Les graphismes doivent
 * d'abord avoir été définis
 */
void Map::loadGraphics() {
	m_visible = true;
	// on crée un background
	m_bgFloor = bgInit(AFRODS_LAYER_GAME_TOP_MAP_FLOOR, BgType_Text8bpp, m_bgSize, 0, 1);
	bgSetPriority(m_bgFloor, AFRODS_LAYER_GAME_TOP_MAP_FLOOR);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	dmaCopy(m_FloorTiles, bgGetGfxPtr(m_bgFloor), m_FloorTilesLen);
#else
	//dmaCopy(bg_world0_colTiles, bgGetGfxPtr(m_bgFloor), bg_world0_colTilesLen);
	dmaCopy(m_ColTiles, bgGetGfxPtr(m_bgFloor), m_ColTilesLen);
#endif

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	if (m_AboveTiles != NULL) {
		// on crée un 2e background pour l'autre layer
		m_bgAbove = bgInit(AFRODS_LAYER_GAME_TOP_MAP_ABOVE, BgType_Text8bpp, m_bgSize, 24, 4);
		bgSetPriority(m_bgAbove, AFRODS_LAYER_GAME_TOP_MAP_ABOVE);
		dmaCopy(m_AboveTiles, bgGetGfxPtr(m_bgAbove), m_AboveTilesLen);
	}
#endif
	// on copie les maps des 2 layers
	//dmaCopy(m_FloorMap, bgGetMapPtr(m_bgFloor), m_FloorMapLen);
	//dmaCopy(m_AboveMap, bgGetMapPtr(m_bgAbove), m_AboveMapLen);

	if (m_bgSize == BgSize_T_512x512) {
		u16* map = (u16*)bgGetMapPtr(m_bgFloor);
		//draw top half
		for(int iy = 0; iy < 32; iy++) {

	#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
			dmaCopy(m_FloorMap + iy * 64, map + iy * 32,  32 * 2);
			dmaCopy(m_FloorMap + iy * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
	#else
			dmaCopy(m_CollisionMap + iy * 64, map + iy * 32,  32 * 2);
			dmaCopy(m_CollisionMap + iy * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
	#endif
			}

		map += 32 * 32 * 2;

		//draw bottom half
		for(int iy = 0; iy < 32; iy++) {
			//copy one line at a time
	#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
			dmaCopy(m_FloorMap + (iy + 32) * 64, map + iy * 32,  32 * 2);
			dmaCopy(m_FloorMap + (iy + 32) * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
	#else
			dmaCopy(m_CollisionMap + (iy + 32) * 64, map + iy * 32,  32 * 2);
			dmaCopy(m_CollisionMap + (iy + 32) * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
	#endif
		}

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		if (m_AboveTiles != NULL) {
			map = (u16*)bgGetMapPtr(m_bgAbove);
			//draw top half
			for(int iy = 0; iy < 32; iy++) {
				dmaCopy(m_AboveMap + iy * 64, map + iy * 32,  32 * 2);
				dmaCopy(m_AboveMap + iy * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
			}

			map += 32 * 32 * 2;

			//draw bottom half
			for(int iy = 0; iy < 32; iy++) {
				//copy one line at a time
				dmaCopy(m_AboveMap + (iy + 32) * 64, map + iy * 32,  32 * 2);
				dmaCopy(m_AboveMap + (iy + 32) * 64 + 32, map + (32 * 32) + iy * 32,  32 * 2);
			}
		}
#endif

	} else {
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		dmaCopy(m_FloorMap, bgGetMapPtr(m_bgFloor), m_FloorMapLen);
		if (m_AboveTiles != NULL) {
			dmaCopy(m_AboveMap, bgGetMapPtr(m_bgAbove), m_AboveMapLen);
		}
#else
		dmaCopy(m_CollisionMap, bgGetMapPtr(m_bgFloor), m_FloorMapLen);
#endif
	}

	// comme on a décidé d'utiliser des palettes étendues on doit le faire ici aussi
	vramSetBankE(VRAM_E_LCD);

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	dmaCopy(m_FloorPal, VRAM_E_EXT_PALETTE[AFRODS_LAYER_GAME_TOP_MAP_FLOOR], m_FloorPalLen);
	if (m_AboveTiles != NULL) {
		dmaCopy(m_AbovePal, VRAM_E_EXT_PALETTE[AFRODS_LAYER_GAME_TOP_MAP_ABOVE], m_AbovePalLen);
	}
#else
	dmaCopy(m_ColPal, VRAM_E_EXT_PALETTE[AFRODS_LAYER_GAME_TOP_MAP_FLOOR], m_ColPalLen);
#endif

	vramSetBankE(VRAM_E_BG_EXT_PALETTE);

	// on s'assure quand même qu'on utilise les palettes étendues
	REG_DISPCNT |= DISPLAY_BG_EXT_PALETTE;
	setVisible(false);

	// si la map est trop petite, on calcule un offset
	if (m_Size.x * 16 < AFRODS_SCREEN_WIDTH)
		m_Offset.x = -1 * ((15 - m_Size.x)*16) / 2 - AFRODS_MAP_OFFSET_PIXELS_X;
	else if (m_Size.x * 16 == AFRODS_SCREEN_WIDTH)
		m_Offset.x = 0;
	else
		m_Offset.x = AFRODS_MAP_OFFSET_PIXELS_X;

	if (m_Size.y * 16 < AFRODS_SCREEN_HEIGHT)
		m_Offset.y = -1 * ((11 - m_Size.y)*16) / 2 - AFRODS_MAP_OFFSET_PIXELS_Y;
	else if (m_Size.y * 16 == AFRODS_SCREEN_HEIGHT)
		m_Offset.y = 0;
	else
		m_Offset.y = AFRODS_MAP_OFFSET_PIXELS_Y;
}

Map::~Map() {
	setVisible(false);

	// on vire les sprites s'il y en a
	while (!m_sprites.empty()) {
		delete m_sprites.at(0).sprite;
		m_sprites.erase(m_sprites.begin());
	}
}

void Map::update() {
	for (unsigned int i = 0 ; i < m_sprites.size() ; i++) {
		MapSprite mapSprite = m_sprites.at(i);
		Sprite * sprite = mapSprite.sprite;
		Coords pos = mapSprite.pos;
		pos.x = pos.x * 16 - (m_ScrollingOffset.x + m_Offset.x) - AFRODS_GAME_OFFSET_CENTER_CHAR_X;
		pos.y = pos.y * 16 - (m_ScrollingOffset.y + m_Offset.y) - AFRODS_GAME_OFFSET_CENTER_CHAR_Y;
		if (pos.x < 0 - (AFRODS_CHAR_WIDTH - 1) ||
			pos.y < 0 - (AFRODS_CHAR_HEIGHT - 1) ||
			pos.x > AFRODS_SCREEN_WIDTH ||
			pos.y > AFRODS_SCREEN_HEIGHT) {
			sprite->setVisible(false);
		} else {
			sprite->setVisible(m_visible);
			sprite->setPos(pos);
		}
		sprite->update();
	}
}

Coords Map::getOffset() const {
	return m_Offset;
}

int Map::getBgId() const {
	return m_bgFloor;
}

void Map::scrollX(int x) {
	m_ScrollingOffset.x = x;
	bgSetScroll(m_bgFloor, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	if (m_AboveTiles != NULL) {
		bgSetScroll(m_bgAbove, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
	}
#endif
}

void Map::scrollY(int y) {
	m_ScrollingOffset.y = y;
	bgSetScroll(m_bgFloor, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	if (m_AboveTiles != NULL) {
		bgSetScroll(m_bgAbove, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
	}
#endif
}

void Map::scroll(int x, int y) {
	m_ScrollingOffset.x = x;
	m_ScrollingOffset.y = y;
	bgSetScroll(m_bgFloor, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	if (m_AboveTiles != NULL) {
		bgSetScroll(m_bgAbove, m_ScrollingOffset.x + m_Offset.x, m_ScrollingOffset.y + m_Offset.y);
	}
#endif
}

/**
 * Renvoie les coordonnées de départ du perso dans la map
 */
Coords Map::getStartingPos() const {
	return m_StartingPos;
}

/**
 * Renvoie la taille de la map
 */
Coords Map::getSize() const {
	return m_Size;
}

/**
 * Renvoie la largeur de la map
 */
int Map::getWidth() const {
	return m_Size.x;
}

/**
 * Renvoie la hauteur de la map
 */
int Map::getHeight() const {
	return m_Size.y;
}

/**
 * Charge la map dans la mémoire vidéo
 */
void Map::setVisible(bool visible) {
	if (m_visible == visible)
		return;

	m_visible = visible;

	// on l'affiche proprement
	if (m_visible) {
		bgShow(m_bgFloor);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		if (m_AboveTiles != NULL) {
			bgShow(m_bgAbove);
		}
#endif
	} else {
		bgHide(m_bgFloor);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		if (m_AboveTiles != NULL) {
			bgHide(m_bgAbove);
		}
#endif
	}

	if (m_visible == false) {
		for (unsigned int i = 0 ; i < m_sprites.size() ; i++) {
			Sprite * sprite = m_sprites.at(i).sprite;
			sprite->setVisible(false);
		}
	}
}

bool Map::canMove(const Coords coords) const {
#ifdef AFRODS_DEBUG_NOCLIP
	return true;
#endif

	if (coords.x < 0 || coords.y < 0 || coords.x > getWidth() * 16 || coords.y > getHeight() * 16)
		return false;

	// on doit convertir les coordonnées de pixels en tiles
	int iTile1 = (coords.x + AFRODS_MAP_OFFSET_CHAR_LEFT)/8 + ((coords.y + AFRODS_MAP_OFFSET_CHAR_TOP)/8 * getWidth() * 2);
	int iTile2 = ((coords.x + (AFRODS_CHAR_WIDTH - 1) - AFRODS_MAP_OFFSET_CHAR_RIGHT)/8 + ((coords.y + AFRODS_MAP_OFFSET_CHAR_TOP)/8 * getWidth() * 2));
	int iTile3 = (coords.x + AFRODS_MAP_OFFSET_CHAR_LEFT)/8 + ((coords.y + (AFRODS_CHAR_HEIGHT - 1) - AFRODS_MAP_OFFSET_CHAR_BOTTOM)/8 * getWidth() * 2);
	int iTile4 = ((coords.x + (AFRODS_CHAR_WIDTH - 1) - AFRODS_MAP_OFFSET_CHAR_RIGHT)/8 + ((coords.y + (AFRODS_CHAR_HEIGHT - 1) - AFRODS_MAP_OFFSET_CHAR_BOTTOM)/8 * getWidth() * 2));

	// on regarde les 2 tiles correspondantes
	if (m_CollisionMap[iTile1] != 2 || m_CollisionMap[iTile2] != 2 || m_CollisionMap[iTile3] != 2 || m_CollisionMap[iTile4] != 2) {
		return false;
	}

	// on regarde s'il n'y a pas un PNJ à cet endroit-là
	// TODO collision des PNJ
	if (false) {
		return false;
	}

	return true;
}

bool Map::isOnWarp(const Coords coords) const {
	int x = (coords.x + AFRODS_MAP_OFFSET_CHAR_LEFT)/16;
	int y = (coords.y + AFRODS_MAP_OFFSET_CHAR_TOP)/16;

//	if ((coords.x + AFRODS_MAP_OFFSET_CHAR_LEFT) % 16 > 0) x++;
//	if ((coords.y + AFRODS_MAP_OFFSET_CHAR_TOP)%16 == 0) y++;

	if (m_tabTilesFloor[x][y].warp)
		return true;
	else
		return false;
}

void Map::addWarp(const MapWarp warp) {
	// on met le warp dans le vector
	m_warps.push_back(warp);

	// on indique sur la tile qu'il y a un warp
	m_tabTilesFloor[warp.pos1.x][warp.pos1.y].warp = true;
}

MapWarp Map::findWarp(const Coords coords) const {
	MapWarp warp;
	// on parcourt les warps pour chercher celui qui correspond aux coordonnÃ©es
	for (unsigned int i = 0 ; i < m_warps.size() ; i++) {
		warp = m_warps.at(i);

		// si les coordonnÃ©es sont identiques on renvoie le warp
		if (warp.pos1 == coords) {
			return warp;
		}
	}
	return warp;
}

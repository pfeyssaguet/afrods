#include "mapfixed.h"

#include "bg_world0_floor.h"
#include "bg_world0_above.h"
#include "bg_world0_col.h"

using namespace AfroDS;

MapFixed::MapFixed(const MapWarp warp) : Map() {
	// on initialise la taille de la map
	m_Size.x = AFRODS_MAP_FIXED_X;
	m_Size.y = AFRODS_MAP_FIXED_Y;
	m_bgSize = BgSize_T_512x512;

	// on définit tous les graphismes pour les 2 layers
	m_FloorTiles = bg_world0_floorTiles;
	m_FloorTilesLen = bg_world0_floorTilesLen;
	m_FloorPal = bg_world0_floorPal;
	m_FloorPalLen = bg_world0_floorPalLen;
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveTiles = bg_world0_aboveTiles;
	m_AboveTilesLen = bg_world0_aboveTilesLen;
	m_AbovePal = bg_world0_abovePal;
	m_AbovePalLen = bg_world0_abovePalLen;
#else
	m_ColTiles = bg_world0_colTiles;
	m_ColTilesLen = bg_world0_colTilesLen;
	m_ColPal = bg_world0_colPal;
	m_ColPalLen = bg_world0_colPalLen;
#endif

	// on pointe sur les tableaux globaux de world0 ici donc pas besoin d'allocation mémoire
	m_CollisionMap = (unsigned short int *)bg_world0_colMap;
	m_CollisionMapLen = bg_world0_colMapLen;
	m_FloorMap = (unsigned short int *)bg_world0_floorMap;
	m_FloorMapLen = bg_world0_floorMapLen;
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveMap = (unsigned short int *)bg_world0_aboveMap;
	m_AboveMapLen = bg_world0_aboveMapLen;
#endif
	// création d'un warp
	addWarp(MapWarp(MAP_FIXED, AFRODS_MAP_WARP_CAVE, MAP_GENERATED));
	addWarp(MapWarp(MAP_FIXED, AFRODS_MAP_WARP_HOUSE_4, MAP_SHOP));
	addWarp(MapWarp(MAP_FIXED, AFRODS_MAP_WARP_HOUSE_1, MAP_SHOP_ARMORY));
	addWarp(MapWarp(MAP_FIXED, AFRODS_MAP_WARP_HOUSE_2, MAP_SHOP_MAGIC));
	addWarp(MapWarp(MAP_FIXED, AFRODS_MAP_WARP_HOUSE_3, MAP_SHOP_BANK));

	// chargement des graphismes
	loadGraphics();

	// on charge la position de départ
	if (warp.map1 == warp.map2) {
		m_StartingPos = AFRODS_MAP_FIXED_STARTING_POS;
	} else {
		m_StartingPos = warp.pos2;
	}

	// on ajoute des PNJ sur la map
	// TODO ajout des characters correspondant aux PNJ
	m_sprites.push_back(AFRODS_MAP_NPC_OLDMAN);
	m_sprites.push_back(AFRODS_MAP_NPC_OLDWOMAN);
	m_sprites.push_back(AFRODS_MAP_NPC_FROG);
}

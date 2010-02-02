#include "mapshoparmory.h"

#include "bg_map_shop_armory_floor.h"
#include "bg_map_shop_armory_col.h"

using namespace AfroDS;

MapShopArmory::MapShopArmory(const MapWarp warp) {
	// on initialise la taille de la map
	m_Size = MAPSHOPARMORY_SIZE;
	m_bgSize = BgSize_T_256x256;

	// on définit tous les graphismes pour les 2 layers
	m_FloorTiles = bg_map_shop_armory_floorTiles;
	m_FloorTilesLen = bg_map_shop_armory_floorTilesLen;
	m_FloorPal = bg_map_shop_armory_floorPal;
	m_FloorPalLen = bg_map_shop_armory_floorPalLen;

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveTiles = NULL;
	m_AboveTilesLen = 0;
	m_AbovePal = NULL;
	m_AbovePalLen = 0;
#else
	m_ColTiles = bg_map_shop_armory_colTiles;
	m_ColTilesLen = bg_map_shop_armory_colTilesLen;
	m_ColPal = bg_map_shop_armory_colPal;
	m_ColPalLen = bg_map_shop_armory_colPalLen;
#endif

	// on pointe sur les tableaux globaux de world0 ici donc pas besoin d'allocation mémoire
	m_CollisionMap = (unsigned short int *)bg_map_shop_armory_colMap;
	m_CollisionMapLen = bg_map_shop_armory_colMapLen;
	m_FloorMap = (unsigned short int *)bg_map_shop_armory_floorMap;
	m_FloorMapLen = bg_map_shop_armory_floorMapLen;
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveMap = NULL;
	m_AboveMapLen = 0;
#endif

	// création d'un warp Coords(10, 11)
	addWarp(MapWarp(MAP_SHOP_ARMORY, MAPSHOPARMORY_DOOR, warp.map1, warp.pos1));

	// chargement des graphismes
	loadGraphics();

	// on ajoute des PNJ sur la map
	m_sprites.push_back(AFRODS_MAP_NPC_ARMORY);

	// on charge la position de départ
	m_StartingPos = MAPSHOPARMORY_DOOR;
}

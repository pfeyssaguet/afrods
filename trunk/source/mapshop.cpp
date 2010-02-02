#include "mapshop.h"

#include "bg_map_shop_above.h"
#include "bg_map_shop_floor.h"
#include "bg_map_shop_col.h"

using namespace AfroDS;

MapShop::MapShop(const MapWarp warp) {
	// on initialise la taille de la map
	m_Size = MAPSHOP_SIZE;
	m_bgSize = BgSize_T_256x256;

	// on définit tous les graphismes pour les 2 layers
	m_FloorTiles = bg_map_shop_floorTiles;
	m_FloorTilesLen = bg_map_shop_floorTilesLen;
	m_FloorPal = bg_map_shop_floorPal;
	m_FloorPalLen = bg_map_shop_floorPalLen;

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveTiles = bg_map_shop_aboveTiles;
	m_AboveTilesLen = bg_map_shop_aboveTilesLen;
	m_AbovePal = bg_map_shop_abovePal;
	m_AbovePalLen = bg_map_shop_abovePalLen;
#else
	m_ColTiles = bg_map_shop_colTiles;
	m_ColTilesLen = bg_map_shop_colTilesLen;
	m_ColPal = bg_map_shop_colPal;
	m_ColPalLen = bg_map_shop_colPalLen;
#endif

	// on pointe sur les tableaux globaux de world0 ici donc pas besoin d'allocation mémoire
	m_CollisionMap = (unsigned short int *)bg_map_shop_colMap;
	m_CollisionMapLen = bg_map_shop_colMapLen;
	m_FloorMap = (unsigned short int *)bg_map_shop_floorMap;
	m_FloorMapLen = bg_map_shop_floorMapLen;
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveMap = (unsigned short int *)bg_map_shop_aboveMap;
	m_AboveMapLen = bg_map_shop_aboveMapLen;
#endif

	// création d'un warp Coords(10, 11)
	addWarp(MapWarp(MAP_SHOP, MAPSHOP_DOOR, warp.map1, warp.pos1));

	// chargement des graphismes
	loadGraphics();

	// on ajoute des PNJ sur la map
	m_sprites.push_back(AFRODS_MAP_NPC_BAZAR);

	// on charge la position de départ
	m_StartingPos = MAPSHOP_DOOR;
}

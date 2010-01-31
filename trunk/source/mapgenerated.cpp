#include "mapgenerated.h"

#include "bg_game_tiles.h"


using namespace AfroDS;

int MapGenerated::s_depth = 0;

MapGenerated::MapGenerated(const MapWarp warp) : Map() {

	// on d�finit tous les graphismes pour les 2 layers
	m_FloorTiles = bg_game_tilesTiles;
	m_FloorTilesLen = bg_game_tilesTilesLen;
	m_FloorPal = bg_game_tilesPal;
	m_FloorPalLen = bg_game_tilesPalLen;

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveTiles = bg_game_tilesTiles;
	m_AboveTilesLen = bg_game_tilesTilesLen;
	m_AbovePal = bg_game_tilesPal;
	m_AbovePalLen = bg_game_tilesPalLen;
#else
	m_ColTiles = bg_game_tilesTiles;
	m_ColTilesLen = bg_game_tilesTilesLen;
	m_ColPal = bg_game_tilesPal;
	m_ColPalLen = bg_game_tilesPalLen;
#endif

	// on alloue de la m�moire pour stocker tous les tiles
	m_FloorMapLen = AFRODS_MAP_MAX_TILES_X * AFRODS_MAP_MAX_TILES_Y * 4;
	m_FloorMap = (unsigned short int *)malloc(m_FloorMapLen * sizeof(unsigned short int));

#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	m_AboveMapLen = AFRODS_MAP_MAX_TILES_X * AFRODS_MAP_MAX_TILES_Y * 4;
	m_AboveMap = (unsigned short int *)malloc(m_AboveMapLen * sizeof(unsigned short int));
#endif

	m_CollisionMapLen = AFRODS_MAP_MAX_TILES_X * AFRODS_MAP_MAX_TILES_Y * 4;
	m_CollisionMap = (unsigned short int *)malloc(m_CollisionMapLen * sizeof(unsigned short int));

	if (s_depth == 0) {
		m_initWarp = warp;
	}

	// on g�n�re une map
	generateMap();

	// position de d�part dans la map
	generateWarps(warp);

	/*
	m_StartingPos.x = m_rooms.at(0).pos.x + 2;
	m_StartingPos.y = m_rooms.at(0).pos.y + 2;
	*/

	//m_StartingPos = AFRODS_MAP_GENERATED_STARTING_POS;

	// on charge la map
	loadMap();

	// on charge les graphismes en m�moire
	loadGraphics();
}

MapGenerated::~MapGenerated() {
	free(m_FloorMap);
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	free(m_AboveMap);
#endif
	free(m_CollisionMap);
}

/**
 * Permet de charger la map dans les tableaux m_FloorMap et m_AboveMap
 */
void MapGenerated::loadMap() {
	for (s16 y = 0 ; y < AFRODS_MAP_MAX_TILES_Y ; y++) {
		for (s16 x = 0 ; x < AFRODS_MAP_MAX_TILES_X ; x++) {

			// si on a une tile...
			if (x < m_Size.x && y < m_Size.y) {
				// on affiche la tile
				setTile(LAYER_FLOOR, Coords(x, y), m_tabTilesFloor[x][y]);
				setTile(LAYER_ABOVE, Coords(x, y), m_tabTilesAbove[x][y]);
			} else {
				// sinon on affiche du vide
				setTile(LAYER_FLOOR, Coords(x, y), AFRODS_TILE_EMPTY);
				setTile(LAYER_ABOVE, Coords(x, y), AFRODS_TILE_EMPTY);
			}

			/*
			// pour afficher la tilemap
			setTile(true, Coords(x, y), Coords(x, y));
			setTile(false, Coords(x, y), Coords(x, y));
			 */
		}
	}
}

/**
 * Permet de g�n�rer la map dans son tableau m_iTiles
 */
void MapGenerated::generateMap() {
	// on initialise la taille de la map
	m_Size.x = AFRODS_MAP_GENERATED_X;
	m_Size.y = AFRODS_MAP_GENERATED_Y;
	m_bgSize = BgSize_T_512x512;

	// on boucle sur tout le tableau
	MapTile tile;
	for (s16 y = 0 ; y < m_Size.y ; y++) {
		for (s16 x = 0 ; x < m_Size.x ; x++) {
			// on calcule le tile � afficher
			/*
			if (x == 0 || y == 0 || x == m_Size.x-1 || y == m_Size.y-1) {
				// un mur
				tile = AFRODS_TILE_WALL;
			} else {
				// du sol
				tile = AFRODS_TILE_FLOOR;
			}
			*/
			tile = AFRODS_TILE_WALL;

			// on le met dans le tableau
			m_tabTilesFloor[x][y] = tile;

			// pour l'instant on met du vide sur l'autre layer
			tile = AFRODS_TILE_EMPTY;
			m_tabTilesAbove[x][y] = tile;
		}
	}

	for (int i = 0 ; i < 5 ; i++) {
		generateRoom();
	}

	connectRooms();

}

void MapGenerated::generateRoom() {
	Room room;
	room.size = Coords(2 + rand() % 8, 2 + rand() % 8);

	int maxx = m_Size.x - room.size.x - 1;
	int maxy = m_Size.y - room.size.y - 1;

	bool bOk = false;

	while (!bOk) {
		room.pos.x = rand() % (maxx-1) + 1;
		room.pos.y = rand() % (maxy-1) + 1;
		bOk = true;
		for (int x = room.pos.x - 1 ; x <= room.pos.x + room.size.x + 1 ; x++) {
			for (int y = room.pos.y - 1 ; y <= room.pos.y + room.size.y + 1 ; y++) {
				if (m_tabTilesFloor[x][y] != AFRODS_TILE_WALL) {
					bOk = false;
					break;
				}
			}
			if (!bOk)
				break;
		}

		if (bOk) {
			for (int x = room.pos.x ; x <= room.pos.x + room.size.x ; x++) {
				for (int y = room.pos.y ; y <= room.pos.y + room.size.y ; y++) {
					m_tabTilesFloor[x][y] = AFRODS_TILE_DIRT;
				}
			}
		}
	}
	m_rooms.push_back(room);
}

void MapGenerated::connectRooms() {
	for (unsigned int i=0; i < m_rooms.size(); i++)
	{
		int h,w;
		Room myRoomOrg = m_rooms.at(i);
		unsigned int iRnd;
		Room myRoomDest;
		do{
			iRnd = rand() % m_rooms.size();
		}while(iRnd==i);
		myRoomDest = m_rooms.at(iRnd);
		h = myRoomOrg.pos.x + myRoomOrg.size.x/2 - (myRoomDest.pos.x + myRoomDest.size.x/2);
		w = myRoomOrg.pos.y + myRoomOrg.size.y/2 - (myRoomDest.pos.y + myRoomDest.size.y/2);
		while(!(h==0 && w==0))
		{
			h==0?w<0?w++:w--:h<0?h++:h--;
			m_tabTilesFloor[myRoomDest.pos.x + myRoomDest.size.x/2+h][myRoomDest.pos.y + myRoomDest.size.y/2+w] = AFRODS_TILE_DIRT;
		}

	}
}


Coords MapGenerated::findFreePos() {
	/* on cherche une zone faite comme �a :
	 * xxx
	 * xXx
	 * .o.
	 * - on veut mettre la porte sur le X
	 * - un x repr�sente un mur
	 * - un o repr�sente du sol
	 *
	 * on doit trouver une zone de ce genre
	 */
	bool bFound = false;
	Coords pos;
	// on cherche dans les rooms
	for (int i = 0 ; i < 5 ; i++) {
		pos.x = m_rooms.at(i).pos.x + m_rooms.at(0).size.x/2;
		pos.y = m_rooms.at(i).pos.y - 1;

		if (pos.x > 0 && pos.x < m_Size.y &&
			pos.y > 0 && pos.y < m_Size.y &&
			m_tabTilesFloor[pos.x - 1][pos.y - 1] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x][pos.y - 1] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x + 1][pos.y - 1] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x - 1][pos.y] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x][pos.y] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x + 1][pos.y] == AFRODS_TILE_WALL &&
			m_tabTilesFloor[pos.x][pos.y + 1] == AFRODS_TILE_DIRT) {
			bFound = true;
			break;
		}
	}

	if (!bFound) {
		// si on n'a pas encore trouv�, on cherche partout sur la map
		for (int x = 1 ; x < m_Size.x -1 ; x++) {
			for (int y = 1 ; y <= m_Size.y - 1 ; y++) {
				if (pos.x > 0 && pos.x < m_Size.y &&
					pos.y > 0 && pos.y < m_Size.y &&
					m_tabTilesFloor[pos.x - 1][pos.y - 1] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x][pos.y - 1] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x + 1][pos.y - 1] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x - 1][pos.y] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x][pos.y] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x + 1][pos.y] == AFRODS_TILE_WALL &&
					m_tabTilesFloor[pos.x][pos.y + 1] == AFRODS_TILE_DIRT) {
					bFound = true;
					break;
				}
			}
			if (bFound)
				break;
		}
	}
	return pos;
}

void MapGenerated::generateWarps(const MapWarp initWarp) {
	// on récupère une position pour la porte d'entrée
	Coords pos = findFreePos();

	if (s_depth == 0) {
		addWarp(MapWarp(MAP_GENERATED, pos, initWarp.map1, initWarp.pos1));
		m_tabTilesFloor[pos.x][pos.y] = AFRODS_TILE_DOOR;
	} else {
		addWarp(MapWarp(MAP_GENERATED, pos, initWarp.map1, initWarp.pos1));
		m_tabTilesFloor[pos.x][pos.y] = AFRODS_TILE_STAIRS_UP;
	}
	m_tabTilesFloor[pos.x][pos.y].warp = true;

	// on se place sur la position de la 1ère porte
	m_StartingPos = pos;

	// on génère un escalier qui descend
	pos = findFreePos();
	if (s_depth == 0) {
		addWarp(MapWarp(MAP_GENERATED, pos, MAP_GENERATED));
	} else {
		addWarp(MapWarp(MAP_GENERATED, pos, MAP_GENERATED));
	}
	m_tabTilesFloor[pos.x][pos.y] = AFRODS_TILE_STAIRS_DOWN;
	m_tabTilesFloor[pos.x][pos.y].warp = true;
}

/**
 * D�finit une tile dans la map
 * @param MapLayer layer true pour floor, false pour above
 * @param Coords pos position de la tile sur la map
 * @param MapTile tile tile dans le tileset, avec ses caract�ristiques de blocage
 */
void MapGenerated::setTile(MapLayer layer, Coords pos, MapTile tile) {
	// on appelle l'autre m�thode
	setTile(layer, pos.x, pos.y, tile);
}

/**
 * D�finit une tile dans la map
 * @param MapLayer layer true pour floor, false pour above
 * @param s16 x position X de la tile sur la map
 * @param s16 y position Y de la tile sur la map
 * @param MapTile tile tile dans le tileset, avec ses caract�ristiques de blocage
 */
void MapGenerated::setTile(MapLayer layer, s16 x, s16 y, MapTile tile) {
	// on a des tiles de 16x16
	// la NDS utilise des tiles de 8x8
	// on doit passer d'un rep�re de coordonn�es � l'autre
	// d'o� les *2
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
	s16 iTile = (tile.Graphics.x + tile.Graphics.y * AFRODS_MAP_NBTILES_PER_LINE*2)*2;
#endif
	s16 iPos = (x + y * AFRODS_MAP_MAX_TILES_X*2)*2;

	// si on doit utiliser floor
	if (layer == LAYER_FLOOR) {
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		m_FloorMap[iPos] = bg_game_tilesMap[iTile];
		m_FloorMap[iPos + 1] = bg_game_tilesMap[iTile + 1];
		m_FloorMap[iPos + AFRODS_MAP_MAX_TILES_X*2] = bg_game_tilesMap[iTile + AFRODS_MAP_NBTILES_PER_LINE*2];
		m_FloorMap[iPos + AFRODS_MAP_MAX_TILES_X*2 + 1] = bg_game_tilesMap[iTile + AFRODS_MAP_NBTILES_PER_LINE*2 + 1];
#endif

		// on doit aussi s'occuper des collisions qui sont sur le layer floor
		// 1 = blocage, 2 = pas de blocage
		m_CollisionMap[iPos] = (tile.blockNW) ? 1 : 2;
		m_CollisionMap[iPos + 1] = (tile.blockNE) ? 1 : 2;
		m_CollisionMap[iPos + AFRODS_MAP_MAX_TILES_X*2] = (tile.blockSW) ? 1 : 2;
		m_CollisionMap[iPos + AFRODS_MAP_MAX_TILES_X*2 + 1] = (tile.blockSE) ? 1 : 2;
	} else if (layer == LAYER_ABOVE) {
#ifndef AFRODS_DEBUG_SHOW_COLLISION_MAP
		m_AboveMap[iPos] = bg_game_tilesMap[iTile];
		m_AboveMap[iPos + 1] = bg_game_tilesMap[iTile + 1];
		m_AboveMap[iPos + AFRODS_MAP_MAX_TILES_X*2] = bg_game_tilesMap[iTile + AFRODS_MAP_NBTILES_PER_LINE*2];
		m_AboveMap[iPos + AFRODS_MAP_MAX_TILES_X*2 + 1] = bg_game_tilesMap[iTile + AFRODS_MAP_NBTILES_PER_LINE*2 + 1];
#endif
	}
}


#include "map.h"
#include "all_gfx.h"

using namespace AfroDS;


/**
 * Constructeur de map
 */
Map::Map() {
	// chargement du background
	//u32 Blank[130000>>2];
	//PA_EasyBgLoad(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_game_tiles);
	//PA_LoadSimpleBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_game_tiles_Tiles, Blank, BG_256X256, 0, 1);
	// on charge la palette des tiles
	PA_LoadBgPal(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, (void *)bg_game_tiles_Pal);

	PA_LoadLargeBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_game_tiles_Tiles, bg_game_tiles_Map, 1, 128, 128);

	// chargement de la map en mémoire
	loadMap();
}

/**
 * Renvoie les coordonnées de départ du perso dans la map
 */
Coords Map::getStartingPos() {
	return m_StartingPos;
}

/**
 * Renvoie la taille de la map
 */
Coords Map::getSize() {
	return m_Size;
}

/**
 * Renvoie la largeur de la map
 */
int Map::getWidth() {
	return m_Size.x;
}

/**
 * Renvoie la hauteur de la map
 */
int Map::getHeight() {
	return m_Size.y;
}

/**
 * Permet de charger la map dans son tableau
 */
void Map::loadMap() {
	// on initialise la taille de la map
	m_Size.x = AFRODS_MAP_X;
	m_Size.y = AFRODS_MAP_Y;

	// on boucle sur tout le tableau
	AF_Tile tile;
	for (s16 y = 0 ; y < m_Size.y ; y++) {
		for (s16 x = 0 ; x < m_Size.x ; x++) {
			// on calcule le tile à afficher
			if (x == 0 || y == 0 || x == m_Size.x-1 || y == m_Size.y-1) {
			//if (x %2 == 0 || y % 2 == 0) {

				// un mur
				tile.Graphics.x = 5;
				tile.Graphics.y = 1;
			} else {
				// du sol
				tile.Graphics.x = 14;
				tile.Graphics.y = 1;
			}

			// on le met dans le tableau
			m_iTiles[x][y] = tile;
		}
	}

	// on charge la position de départ
	m_StartingPos.x = 4;
	m_StartingPos.y = 4;
}

/**
 * Affiche la fraction visible de la map à l'écran,
 * en fonction des coordonnées d'origine (du centre)
 */
void Map::prepareTiles() {
	for (s16 y2 = 0 ; y2 < AFRODS_MAP_MAX_TILES_Y ; y2++) {
		for (s16 x2 = 0 ; x2 < AFRODS_MAP_MAX_TILES_X ; x2++) {
			// si on a une tile...
			if (x2 < m_Size.x && y2 < m_Size.y) {
				// on affiche la tile
				showTile(x2, y2, m_iTiles[x2][y2].Graphics.x, m_iTiles[x2][y2].Graphics.y);
				//showTile(x2, y2, 0, 0);
			} else {
				// sinon on affiche du vide
				showTile(x2, y2, 0, 0);
			}
		}
	}
}

/**
 * Affiche une tile à l'écran
 * @param s16 x position X de la tile sur la map
 * @param s16 y position Y de la tile sur la map
 * @param s16 tilex position X de la tile dans son tileset
 * @param s16 tiley position Y de la tile dans son tileset
 */
void Map::showTile(s16 x, s16 y, s16 tilex, s16 tiley) {
	// on a des tiles de 16x16
	// la NDS utilise des tiles de 8x8
	// on doit passer d'un repère de coordonnées à l'autre
	s16 iTile = (tilex + tiley * AFRODS_MAP_NBTILES_PER_LINE)*2;


	PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2, y*2, bg_game_tiles_Map[iTile]);
	PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2+1, y*2, bg_game_tiles_Map[iTile + 1]);
	PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2, y*2+1, bg_game_tiles_Map[iTile + AFRODS_MAP_NBTILES_PER_LINE]);
	PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2+1, y*2+1, bg_game_tiles_Map[iTile + AFRODS_MAP_NBTILES_PER_LINE + 1]);
return;

	// on veut commencer à la moitié du 1er tile
	// étant donné qu'on a des tiles en 16x16 et qu'on travaille en 8x8,
	// on saute la 1ère et la dernière ligne,
	// et on saute la 1ère et la dernière colonne

	// en haut à gauche : pas sur la 1ère ligne ni la 1ère colonne
	if (y != 0 && x != 0) {
		PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2-1, y*2-1, bg_game_tiles_Map[iTile]);
	}

	// en haut à droite : pas sur la 1ère ligne ni la dernière colonne
	if (y != 0 && x != AFRODS_MAP_NBTILES_VISIBLE_X) {
		PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2+1-1, y*2-1, bg_game_tiles_Map[iTile + 1]);
	}

	// en bas à gauche : pas sur la dernière ligne ni sur la 1ère colonne
	if (y != AFRODS_MAP_NBTILES_VISIBLE_Y && x != 0) {
		PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2-1, y*2+1-1, bg_game_tiles_Map[iTile + AFRODS_MAP_NBTILES_PER_LINE]);
	}

	// en bas à droite : pas sur la dernière ligne ni sur la dernière colonne
	if (y != AFRODS_MAP_NBTILES_VISIBLE_Y && x != AFRODS_MAP_NBTILES_VISIBLE_X) {
		PA_SetLargeMapTile(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, x*2+1-1, y*2+1-1, bg_game_tiles_Map[iTile + AFRODS_MAP_NBTILES_PER_LINE + 1]);
	}
}

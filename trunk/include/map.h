#ifndef __MAP_H__
#define __MAP_H__

#include "constants.h"
#include "types.h"
#include <PA9.h>

// nombre de tiles max dans une map
#define AFRODS_MAP_MAX_TILES_X 64
#define AFRODS_MAP_MAX_TILES_Y 64

// nombre de tiles par ligne dans le tileset
#define AFRODS_MAP_NBTILES_PER_LINE 128

// nombre de tiles visibles à l'écran au maximum
#define AFRODS_MAP_NBTILES_VISIBLE_X 17
#define AFRODS_MAP_NBTILES_VISIBLE_Y 13

// nombre de tiles dans la map
#define AFRODS_MAP_X 20
#define AFRODS_MAP_Y 20


namespace AfroDS {

	/**
	 * Structure qui permet de définir une tile dans la map
	 */
	struct AF_Tile {
		/** Graphisme du tile sur son tileset */
		AfroDS::Coords Graphics;
	};

	class Map {
		public:
			/**
			 * Constructeur de map
			 */
			Map();

			/**
			 * Affiche la fraction visible de la map à l'écran,
			 * en fonction des coordonnées d'origine (du centre)
			 */
			void prepareTiles();

			/**
			 * Renvoie les coordonnées de départ du perso dans la map
			 */
			AfroDS::Coords getStartingPos();

			/**
			 * Renvoie la taille de la map
			 */
			AfroDS::Coords getSize();

			/**
			 * Renvoie la largeur de la map
			 */
			int getWidth();

			/**
			 * Renvoie la hauteur de la map
			 */
			int getHeight();
		private:
			/**
			 * Affiche une tile à l'écran
			 * @param s16 x position X de la tile sur la map
			 * @param s16 y position Y de la tile sur la map
			 * @param s16 tilex position X de la tile dans son tileset
			 * @param s16 tiley position Y de la tile dans son tileset
			 */
			void showTile(s16 x, s16 y, s16 tilex, s16 tiley);

			/**
			 * Permet de charger la map dans son tableau
			 */
			void loadMap();

			/**
			 * Taille de la map
			 */
			AfroDS::Coords m_Size;

			/**
			 * Le tableau qui représente les tiles de la map
			 */
			AfroDS::AF_Tile m_iTiles[AFRODS_MAP_X][AFRODS_MAP_Y];

			/**
			 * Position de départ du perso dans la map
			 */
			AfroDS::Coords m_StartingPos;
	};

}
#endif

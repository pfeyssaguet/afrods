#ifndef __MAP_H__
#define __MAP_H__

#include "constants.h"
#include "types.h"
#include "spritechar.h"

#include <nds.h>
#include <vector>

// nombre de tiles dans la map générée
#define AFRODS_MAP_GENERATED_X 32
#define AFRODS_MAP_GENERATED_Y 32
//#define AFRODS_MAP_GENERATED_X 6
//#define AFRODS_MAP_GENERATED_Y 6

// nombre de tiles max dans une map
#define AFRODS_MAP_MAX_TILES_X 32
#define AFRODS_MAP_MAX_TILES_Y 32

// décalage des tiles par rapport à l'écran
#define AFRODS_MAP_OFFSET_PIXELS_X 8
#define AFRODS_MAP_OFFSET_PIXELS_Y 8

// offset de collision du perso à gauche
#define AFRODS_MAP_OFFSET_CHAR_LEFT 8
// offset de collision du perso à droite
#define AFRODS_MAP_OFFSET_CHAR_RIGHT 8
// offset de collision du perso en haut
#define AFRODS_MAP_OFFSET_CHAR_TOP 16
// offset de collision du perso en bas
#define AFRODS_MAP_OFFSET_CHAR_BOTTOM 0


namespace AfroDS {

	enum MapType {MAP_FIXED, MAP_GENERATED, MAP_SHOP, MAP_SHOP_ARMORY, MAP_SHOP_MAGIC, MAP_SHOP_BANK};

	struct MapWarp {

		MapWarp() {

		}

		MapWarp(const MapType p_map) {
			map1 = p_map;
			map2 = p_map;
		}

		MapWarp(const MapType p_map1, const Coords p_pos1, const MapType p_map2) {
			map1 = p_map1;
			pos1 = p_pos1;
			map2 = p_map2;
			pos2 = Coords();
		}

		MapWarp(const MapType p_map1, const Coords p_pos1, const MapType p_map2, const Coords p_pos2) {
			map1 = p_map1;
			pos1 = p_pos1;
			map2 = p_map2;
			pos2 = p_pos2;
		}

		bool operator==(const MapWarp warp) {
			if (warp.map1 == map1 && warp.map2 == map2 &&
					warp.pos1.x == pos1.x  && warp.pos1.y == pos1.y &&
					warp.pos2.x == pos2.x && warp.pos2.y == pos2.y) {
				return true;
			} else {
				return false;
			}
		}

		bool operator!=(const MapWarp warp) {
			if (warp.map1 != map1 || warp.map2 != map2 ||
					warp.pos1.x != pos1.x || warp.pos1.y != pos1.y ||
					warp.pos2.x != pos2.x || warp.pos2.y != pos2.y) {
				return true;
			} else {
				return false;
			}
		}

		/** Map de dÃ©part */
		MapType map1;
		/** CoordonnÃ©es de la porte sur la map de dÃ©part */
		Coords pos1;

		/** Map d'arrivÃ©e */
		MapType map2;
		/** CoordonnÃ©es de la porte sur la map d'arrivÃ©e */
		Coords pos2;
	};

	/**
	 * Structure qui permet de définir une tile dans la map
	 */
	struct MapTile {
		MapTile() {
			blockNW = false;
			blockNE = false;
			blockSW = false;
			blockSE = false;
			warp = false;
		}

		MapTile(const Coords coords, const bool p_blockNW, const bool p_blockNE, const bool p_blockSW, const bool p_blockSE) {
			Graphics = coords;
			blockNW = p_blockNW;
			blockNE = p_blockNE;
			blockSW = p_blockSW;
			blockSE = p_blockSE;
			warp = false;
		}

		bool operator==(const MapTile tile) {
			if (Graphics.x == tile.Graphics.x && Graphics.y == tile.Graphics.y) {
				return true;
			} else {
				return false;
			}
		}

		bool operator!=(const MapTile tile) {
			if (Graphics.x == tile.Graphics.x && Graphics.y == tile.Graphics.y) {
				return false;
			} else {
				return true;
			}
		}

		/** Graphisme du tile sur son tileset */
		Coords Graphics;

		/**
		 * Points de blocage du tile (comme des points cardinaux)
		 * (NW)(NE)
		 * (SW)(SE)
		 */
		bool blockNW;
		bool blockNE;
		bool blockSW;
		bool blockSE;

		bool warp;
	};

	struct MapSprite {
		MapSprite() {
			sprite = NULL;
		}

		MapSprite(Sprite * p_sprite, const Coords p_pos) {
			sprite = p_sprite;
			pos = p_pos;
		}

		Sprite * sprite;
		Coords pos;
	};

	class Map {
		public:
			virtual ~Map();

			/**
			 * Affiche la fraction visible de la map à l'écran,
			 * en fonction des coordonnées d'origine (du centre)
			 */
			void setVisible();
			/**
			 * Chargement des graphismes. Les graphismes doivent
			 * d'abord avoir été définis
			 */
			void loadGraphics();

			/**
			 * Renvoie les coordonnées de départ du perso dans la map
			 */
			Coords getStartingPos() const;

			/**
			 * Renvoie la taille de la map
			 */
			Coords getSize() const;

			/**
			 * Renvoie la largeur de la map
			 */
			int getWidth() const;

			/**
			 * Renvoie la hauteur de la map
			 */
			int getHeight() const;

			/**
			 * Renvoie le background alloué par bgInit()
			 * @return int id du background
			 */
			int getBgId() const;

			void setVisible(bool visible);

			Coords getOffset() const;
			void scrollX(int x);
			void scrollY(int y);
			void scroll(int x, int y);

			bool canMove(Coords coords) const;

			bool isOnWarp(Coords coords) const;

			void addWarp(const MapWarp warp);

			MapWarp findWarp(const Coords coords) const;

			void update();

		protected:
			/**
			 * Constructeur de map
			 */
			Map();

			/** Tableau de tiles */
			const unsigned int * m_FloorTiles;

			/** Taille du tableau de tiles */
			int m_FloorTilesLen;

			/** Palette */
			const unsigned short * m_FloorPal;

			/** Taille de la palette */
			int m_FloorPalLen;

			/** Tableau de tiles */
			const unsigned int * m_AboveTiles;

			/** Taille du tableau de tiles */
			int m_AboveTilesLen;

			/** Palette */
			const unsigned short * m_AbovePal;

			/** Taille de la palette */
			int m_AbovePalLen;


#ifdef AFRODS_DEBUG_SHOW_COLLISION_MAP
			/** Tiles de la map de collision */
			const unsigned int * m_ColTiles;

			/** Taille des tiles de la map de collision */
			int m_ColTilesLen;

			/** Palette de la map de collision */
			const unsigned short * m_ColPal;

			/** Taille de la palette de la map de collision */
			int m_ColPalLen;
#endif



			/** Taille de la map */
			Coords m_Size;

			/** Taille du Background */
			BgSize m_bgSize;

			/**
			 * Position de départ du perso dans la map
			 */
			Coords m_StartingPos;

			unsigned short int * m_FloorMap;
			int m_FloorMapLen;
			unsigned short int * m_AboveMap;
			int m_AboveMapLen;
			unsigned short * m_CollisionMap;
			int m_CollisionMapLen;

			/** Le tableau qui représente les tiles de la map */
			MapTile m_tabTilesFloor[AFRODS_MAP_GENERATED_X][AFRODS_MAP_GENERATED_Y];

			/** Les tiles de l'autre layer */
			MapTile m_tabTilesAbove[AFRODS_MAP_GENERATED_X][AFRODS_MAP_GENERATED_Y];

			/** Les NPC */
			std::vector<Character *> m_npc;

			/** Les sprites utilisés sur la map (NPC ou autres) */
			std::vector<MapSprite> m_sprites;

			/** Les warp zones */
			std::vector<MapWarp> m_warps;
		private:

			/**
			 * Définit une tile dans la map
			 * @param s16 x position X de la tile sur la map
			 * @param s16 y position Y de la tile sur la map
			 * @param s16 tilex position X de la tile dans le tileset
			 * @param s16 tiley position Y de la tile dans le tileset
			 */
			void setTile(s16 x, s16 y, s16 tilex, s16 tiley);

			/**
			 * Permet de charger la map dans son tableau
			 */
			void loadMap();

			/** Indique si la map est visible ou pas */
			bool m_visible;

			/** Le background du layer du sol */
			int m_bgFloor;

			/** Le background du layer above */
			int m_bgAbove;

			/** Offset de la map */
			Coords m_Offset;

			/** Position du scrolling */
			Coords m_ScrollingOffset;
	};

}
#endif

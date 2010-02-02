#ifndef __MAPGENERATED_H__
#define __MAPGENERATED_H__

#include "map.h"

// nombre de tiles par ligne dans le tileset
#define AFRODS_MAP_NBTILES_PER_LINE 16

// description des tiles du tileset...
#define AFRODS_TILE_EMPTY MapTile()
#define AFRODS_TILE_WATER MapTile(Coords(2, 4), false, false, false, false)
#define AFRODS_TILE_WALL MapTile(Coords(5, 1), true, true, true, true)
#define AFRODS_TILE_DIRT MapTile(Coords(2, 1), false, false, false, false)
#define AFRODS_TILE_GRASS MapTile(Coords(14, 1), false, false, false, false)
#define AFRODS_TILE_DOOR MapTile(Coords(7, 5), false, false, false, false)
#define AFRODS_TILE_STAIRS_UP MapTile(Coords(8, 5), false, false, false, false)
#define AFRODS_TILE_STAIRS_DOWN MapTile(Coords(9, 5), false, false, false, false)

namespace AfroDS {
	enum MapLayer {LAYER_FLOOR, LAYER_ABOVE, LAYER_COLLISION};

	struct Room {
		Coords pos;
		Coords size;
	};

	class MapGenerated : public Map {
		public:
			MapGenerated(const MapWarp warp);

			~MapGenerated();
		private:
			void loadMap();
			void generateMap();
			void generateRoom();
			void connectRooms();
			void generateWarps(const MapWarp initWarp);
			Coords findFreePos();

			/**
			 * Définit une tile dans la map
			 * @param MapLayer layer true pour floor, false pour above
			 * @param Coords pos position de la tile sur la map
			 * @param MapTile tile tile dans le tileset, avec ses caractéristiques de blocage
			 */
			void setTile(MapLayer layer, Coords pos, MapTile tile);

			/**
			 * Définit une tile dans la map
			 * @param MapLayer layer true pour floor, false pour above
			 * @param s16 x position X de la tile sur la map
			 * @param s16 y position Y de la tile sur la map
			 * @param MapTile tile tile dans le tileset, avec ses caractéristiques de blocage
			 */
			void setTile(MapLayer layer, s16 x, s16 y, MapTile tile);

			std::vector<Room> m_rooms;

			MapWarp m_initWarp;

			static int s_depth;
	};
}

#endif

#ifndef __MAPSHOPARMORY_H_
#define __MAPSHOPARMORY_H_

#include "map.h"

#define MAPSHOPARMORY_SIZE Coords(16, 12)
#define MAPSHOPARMORY_DOOR Coords(5, 11)

// des PNJ sur la map
#define AFRODS_MAP_NPC_ARMORY MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_NPC_ARMORY), Coords(7, 5))

namespace AfroDS {
	class MapShopArmory : public Map {
		public:
			MapShopArmory(const MapWarp warp);
	};
}

#endif

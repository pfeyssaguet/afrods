#ifndef __MAPSHOPBANK_H_
#define __MAPSHOPBANK_H_

#include "map.h"

#define MAPSHOPBANK_SIZE Coords(16, 12)
#define MAPSHOPBANK_DOOR Coords(4, 11)

// des PNJ sur la map
#define AFRODS_MAP_NPC_BANK MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_NPC_BANK), Coords(7, 5))

namespace AfroDS {
	class MapShopBank : public Map {
		public:
			MapShopBank(const MapWarp warp);
	};
}

#endif

#ifndef __MAPSHOP_H_
#define __MAPSHOP_H_

#include "map.h"

#define MAPSHOP_SIZE Coords(16, 12)
#define MAPSHOP_DOOR Coords(10, 11)

// des PNJ sur la map
#define AFRODS_MAP_NPC_BAZAR MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_NPC_BAZAR), Coords(9, 4))

namespace AfroDS {
	class MapShop : public Map {
		public:
			MapShop(const MapWarp warp);
	};
}

#endif

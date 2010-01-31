#ifndef __MAPSHOPMAGIC_H_
#define __MAPSHOPMAGIC_H_

#include "map.h"

#define MAPSHOPMAGIC_SIZE Coords(16, 12)
#define MAPSHOPMAGIC_DOOR Coords(10, 11)

// des PNJ sur la map
#define AFRODS_MAP_NPC_MAGIC MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_NPC_MAGIC), Coords(7, 4))


namespace AfroDS {
	class MapShopMagic : public Map {
		public:
			MapShopMagic(const MapWarp warp);
	};
}

#endif

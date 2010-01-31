#ifndef __MAPFIXED_H__
#define __MAPFIXED_H__

#include "map.h"

// nombre de tiles dans la map
#define AFRODS_MAP_FIXED_X 32
#define AFRODS_MAP_FIXED_Y 32

// position de d�part du perso, pour l'instant une macro bidon...
#define AFRODS_MAP_FIXED_STARTING_POS Coords(5, 3)
//#define AFRODS_MAP_FIXED_STARTING_POS Coords(10, 21)

// maison 1
#define AFRODS_MAP_WARP_HOUSE_1 Coords(11, 16)

#define AFRODS_MAP_WARP_HOUSE_2 Coords(19, 4)

#define AFRODS_MAP_WARP_HOUSE_3 Coords(22, 10)

// un point de warp sur la map (sur la 1�re maison en bas)
#define AFRODS_MAP_WARP_HOUSE_4 Coords(10, 20)
// grotte
#define AFRODS_MAP_WARP_CAVE Coords(28, 2)

// des PNJ sur la map
#define AFRODS_MAP_NPC_OLDMAN MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_NPC), Coords(20, 5))
#define AFRODS_MAP_NPC_OLDWOMAN MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_WOMAN), Coords(23, 11))
#define AFRODS_MAP_NPC_FROG MapSprite(new SpriteChar(SCREEN_MAIN, SPRITE_FROG), Coords(9, 21))


namespace AfroDS {

	class MapFixed : public Map {
		public:
			MapFixed(const MapWarp warp);
	};
}

#endif

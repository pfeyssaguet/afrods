#ifndef __MAPFACTORY_H_
#define __MAPFACTORY_H_

#include "map.h"

namespace AfroDS {

	//enum MapType {MAP_FIXED, MAP_GENERATED};

	class MapFactory {
		public:
			static Map * loadMap(const MapWarp warp);

		private:
			MapFactory() {};
	};

}

#endif

#include "mapfactory.h"
#include "mapfixed.h"
#include "mapgenerated.h"
#include "mapshop.h"
#include "mapshoparmory.h"
#include "mapshopmagic.h"
#include "mapshopbank.h"


using namespace AfroDS;

Map * MapFactory::loadMap(const MapWarp warp) {
	switch (warp.map2) {
		case MAP_FIXED:
			return new MapFixed(warp);
			break;
		case MAP_GENERATED:
			return new MapGenerated(warp);
			break;
		case MAP_SHOP:
			return new MapShop(warp);
			break;
		case MAP_SHOP_ARMORY:
			return new MapShopArmory(warp);
			break;
		case MAP_SHOP_MAGIC:
			return new MapShopMagic(warp);
			break;
		case MAP_SHOP_BANK:
			return new MapShopBank(warp);
			break;
	}
	return NULL;
}

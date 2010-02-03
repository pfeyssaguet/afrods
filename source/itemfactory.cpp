#include "itemfactory.h"
#include "itemarmor.h"
#include "itemweapon.h"

using namespace AfroDS;


Item * ItemFactory::generateLoot(ItemLoot loot) {
	switch (loot) {
		case LOOT_POTION_HEAL:
			return new Item("Large Heal Potion", TYPE_POTION_HEAL, 50);
			break;
		case LOOT_POTION_MANA:
			return new Item("Large Mana Potion", TYPE_POTION_MANA, 50);
			break;
		case LOOT_SWORD:
			return new ItemWeapon("Sword", TYPE_WEAPON_SWORD, Coords(1, 6));
			break;
		case LOOT_ARTIFACT_SWORD_OF_BOULBI:
			Item * item = new ItemWeapon("Sword of Boulbi", TYPE_WEAPON_SWORD, Stats(12, 0, 12, 0, 0, 0), Coords(1, 10), LARGEICON_SWORD_1);
			item->setPrice(3234);
			return item;
			break;
	}
	return NULL;
}

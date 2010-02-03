#ifndef __ITEMFACTORY_H_
#define __ITEMFACTORY_H_

#include "item.h"

namespace AfroDS {


	enum ItemLoot {
		LOOT_POTION_HEAL,
		LOOT_POTION_MANA,
		LOOT_SWORD,
		LOOT_ARTIFACT_SWORD_OF_BOULBI
	};

	class ItemFactory {
		public:
			static Item * generateLoot(ItemLoot loot);

	};
}

#endif

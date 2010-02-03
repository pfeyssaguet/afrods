#ifndef __ITEMWEAPON_H_
#define __ITEMWEAPON_H_

#include "item.h"

namespace AfroDS {

	class ItemWeapon : public Item {
		public:
			ItemWeapon(const std::string sName, const ItemType type, const Coords dice);

			ItemWeapon(const std::string sName, const ItemType type, const Coords dice, const ItemLargeIcon largeIcon);

			// TODO inverser les paramètres stats et dice dans ce constructeur
			ItemWeapon(const std::string sName, const ItemType type, const Stats stats, const Coords dice);

			// TODO inverser les paramètres stats et dice dans ce constructeur
			ItemWeapon(const std::string sName, const ItemType type, const Stats stats, const Coords dice, const ItemLargeIcon largeIcon);

			int rollDamage() const;
			std::string getLongName() const;
			virtual std::string getDescription() const;
			bool isRangedWeapon() const;

		private:
			// on stocke le dé de dégâts dans une structure Coords
			// X = nombre de dés
			// Y = valeur des dés
			Coords m_dice;
	};

}

#endif

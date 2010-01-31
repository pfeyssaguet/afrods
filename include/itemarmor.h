#ifndef __ITEMARMOR_H_
#define __ITEMARMOR_H_

#include "item.h"

namespace AfroDS {
	class ItemArmor : public Item {
		public:
			ItemArmor(const std::string sName);
			ItemArmor(const std::string sName, const ItemType type);
			ItemArmor(const std::string sName, const ItemType type, const ItemLargeIcon largeIcon);
			ItemArmor(const std::string sName, const ItemType type, const int armorFactor);
			ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const ItemLargeIcon largeIcon);
			ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const Stats stats);
			ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const Stats stats, const ItemLargeIcon largeIcon);

			int getArmorFactor() const;
			virtual std::string getDescription() const;
			std::string getLongName() const;

		private:
			int m_armorFactor;
	};
}

#endif

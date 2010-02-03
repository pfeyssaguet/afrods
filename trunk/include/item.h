#ifndef __ITEM_H__
#define __ITEM_H__

#include "types.h"

#include <string>

namespace AfroDS {
	/**
	 * Les différents types d'items
	 */
	enum ItemType {
		TYPE_WEAPON_SWORD,
		TYPE_WEAPON_HAMMER,
		TYPE_WEAPON_DAGGER,
		TYPE_WEAPON_AXE,
		TYPE_LARGEWEAPON,
		TYPE_RANGEDWEAPON,
		TYPE_SHIELD,
		TYPE_ARMOR,
		TYPE_HELMET,
		TYPE_CLOAK,
		TYPE_BOOTS,
		TYPE_GLOVES,
		TYPE_RING,
		TYPE_NECKLACE,
		TYPE_BELT,
		// types non équipables
		TYPE_POTION_HEAL,
		TYPE_POTION_MANA,
		TYPE_OTHER
	};

	enum ItemSmallIcon {
		SMALLICON_SHIELD, SMALLICON_ARMOR, SMALLICON_HELMET, SMALLICON_BOOTS, SMALLICON_GLOVES, SMALLICON_CLOAK,
		SMALLICON_DAGGER, SMALLICON_SWORD, SMALLICON_AXE, SMALLICON_HAMMER, SMALLICON_BOW1, SMALLICON_BOW2,
		SMALLICON_POTION_MANA, SMALLICON_POTION_HEAL,
		SMALLICON_RING, SMALLICON_NECKLACE, SMALLICON_BELT,
		SMALLICON_UNKNOWN
	};

	enum ItemLargeIcon {
		LARGEICON_DEFAULT_DAGGER = 0,
		LARGEICON_DEFAULT_SWORD = 1, LARGEICON_SWORD_1 = 3,
		LARGEICON_DEFAULT_LARGEWEAPON = 2,
		LARGEICON_DEFAULT_SHIELD = 24,
		LARGEICON_DEFAULT_ARMOR = 36,
		LARGEICON_DEFAULT_HELMET = 20,
		LARGEICON_DEFAULT_BOOTS = 35,
		LARGEICON_DEFAULT_GLOVES = 29,
		LARGEICON_DEFAULT_CLOAK = 48,
		LARGEICON_DEFAULT_AXE = 4,
		LARGEICON_DEFAULT_HAMMER = 5,
		LARGEICON_DEFAULT_BOW = 8,
		LARGEICON_DEFAULT_POTION_MANA = 56,
		LARGEICON_DEFAULT_POTION_HEAL = 58,
		LARGEICON_DEFAULT_RING = 42, LARGEICON_RING_GOLD = 40,
		LARGEICON_DEFAULT_NECKLACE = 44,
		LARGEICON_DEFAULT_BELT = 52,
		LARGEICON_UNKNOWN = 63
	};

	class Item {
		public:
			/**
			 * Constructeur par défaut
			 */
			Item();

			Item(const std::string sName);

			/**
			 * Constructeur initialisant le nom et le type d'item
			 * @param std::string sName nom de l'item
			 * @param ItemType type type de l'item
			 */
			Item(const std::string sName, const ItemType type);

			Item(const std::string sName, const ItemType type, const ItemLargeIcon largeIcon);

			/**
			 * Constructeur initialisant le nom, le type d'item et ses stats
			 * @param std::string sName nom de l'item
			 * @param ItemType type type de l'item
			 * @param Stats stats bonus de l'item
			 */
			Item(const std::string sName, const ItemType type, const Stats stats);

			Item(const std::string sName, const ItemType type, const int value);

			Item(const std::string sName, const ItemType type, const int value, const int price);

			Item(const std::string sName, const ItemType type, const Stats stats, const ItemLargeIcon largeIcon);

			std::string getBonusString() const;

			/**
			 * Définit le nom de l'item
			 * @param std::string sName nom de l'item
			 */
			void setName(const std::string sName);

			/**
			 * Renvoie le type de l'item
			 * @return ItemType type de l'item
			 */
			ItemType getType() const;

			int getValue() const;

			/**
			 * Renvoie les bonus de l'item
			 * @return Stats bonus de l'item
			 */
			Stats getStats() const;

			int getHigherBonus() const;

			std::string getName() const;

			bool isWeapon() const;

			bool isArmor() const;

			ItemSmallIcon getSmallIcon() const;

			ItemLargeIcon getLargeIcon() const;

			long getPrice() const;
			void setPrice(const long price);

			/**
			 * Renvoie le nom de l'item
			 * @return std::string nom de l'item
			 */
			virtual std::string getLongName() const;

			virtual std::string getDescription() const;

		protected:
			/** Nom de l'item */
			std::string m_sName;

			/** Type de l'item */
			ItemType m_Type;

			/** Grande icône de l'item */
			ItemLargeIcon m_LargeIcon;

			/** Bonus de l'item */
			Stats m_statBonus;

			/** Valeur numérique de l'item, dans le cas d'une potion.. */
			int m_value;

			/** Prix */
			long m_price;

		private:
			ItemLargeIcon defaultLargeIcon();
	};
}

#endif

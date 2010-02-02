#include "item.h"

#include <sstream>


using namespace AfroDS;

/**
 * Constructeur par défaut
 */
Item::Item() {
}

Item::Item(const std::string sName) : m_sName(sName), m_Type(TYPE_OTHER) {
	m_LargeIcon = defaultLargeIcon();
}

/**
 * Constructeur initialisant le nom et le type d'item
 * @param std::string sName nom de l'item
 * @param ItemType type type de l'item
 */
Item::Item(const std::string sName, const ItemType type) : m_sName(sName), m_Type(type) {
	m_LargeIcon = defaultLargeIcon();
}

Item::Item(const std::string sName, const ItemType type, const ItemLargeIcon largeIcon) : m_sName(sName), m_Type(type), m_LargeIcon(largeIcon) {
}

Item::Item(const std::string sName, const ItemType type, int value) : m_sName(sName), m_Type(type), m_value(value) {
	m_LargeIcon = defaultLargeIcon();
}

/**
 * Constructeur initialisant le nom, le type d'item et ses stats
 * @param std::string sName nom de l'item
 * @param ItemType type type de l'item
 * @param Stats stats bonus de l'item
 */
Item::Item(const std::string sName, const ItemType type, const Stats stats) : m_sName(sName), m_Type(type), m_statBonus(stats) {
	m_LargeIcon = defaultLargeIcon();
}

Item::Item(const std::string sName, const ItemType type, const Stats stats, const ItemLargeIcon largeIcon) : m_sName(sName), m_Type(type), m_LargeIcon(largeIcon), m_statBonus(stats) {
}

ItemLargeIcon Item::defaultLargeIcon() {
	switch (m_Type) {
		case TYPE_SHIELD:
			return LARGEICON_DEFAULT_SHIELD;
			break;
		case TYPE_ARMOR:
			return LARGEICON_DEFAULT_ARMOR;
			break;
		case TYPE_HELMET:
			return LARGEICON_DEFAULT_HELMET;
			break;
		case TYPE_BOOTS:
			return LARGEICON_DEFAULT_BOOTS;
			break;
		case TYPE_GLOVES:
			return LARGEICON_DEFAULT_GLOVES;
			break;
		case TYPE_CLOAK:
			return LARGEICON_DEFAULT_CLOAK;
			break;
		case TYPE_WEAPON_DAGGER:
			return LARGEICON_DEFAULT_DAGGER;
			break;
		case TYPE_WEAPON_SWORD:
			return LARGEICON_DEFAULT_SWORD;
			break;
		case TYPE_WEAPON_AXE:
			return LARGEICON_DEFAULT_AXE;
			break;
		case TYPE_WEAPON_HAMMER:
			return LARGEICON_DEFAULT_HAMMER;
			break;
		case TYPE_LARGEWEAPON:
			return LARGEICON_DEFAULT_LARGEWEAPON;
			break;
		case TYPE_RANGEDWEAPON:
			return LARGEICON_DEFAULT_BOW;
			break;
		case TYPE_POTION_MANA:
			return LARGEICON_DEFAULT_POTION_MANA;
			break;
		case TYPE_POTION_HEAL:
			return LARGEICON_DEFAULT_POTION_HEAL;
			break;
		case TYPE_RING:
			return LARGEICON_DEFAULT_RING;
			break;
		case TYPE_NECKLACE:
			return LARGEICON_DEFAULT_NECKLACE;
			break;
		case TYPE_BELT:
			return LARGEICON_DEFAULT_BELT;
			break;
		default:
			break;
	}

	return LARGEICON_UNKNOWN;
}

std::string Item::getName() const {
	return m_sName;
}

/**
 * Renvoie le nom de l'item
 * @return std::string nom de l'item
 */
std::string Item::getLongName() const {
	return m_sName;
}

std::string Item::getDescription() const {
	std::ostringstream os;
	os << getLongName();

	std::string sBonus = getBonusString();
	if (sBonus.length() > 0) {
		os << '\n';
		os << "Bonus : ";
		os << sBonus;
	}

	if (m_Type == TYPE_POTION_HEAL) {
		os << '\n';
		os << "Heals ";
		os << m_value;
		os << " HP";
	} else if (m_Type == TYPE_POTION_MANA) {
		os << '\n';
		os << "Heals ";
		os << m_value;
		os << " MP";
	}

	return os.str();
}

bool Item::isWeapon() const {
	switch(m_Type) {
		case TYPE_WEAPON_SWORD:
		case TYPE_WEAPON_AXE:
		case TYPE_WEAPON_DAGGER:
		case TYPE_WEAPON_HAMMER:
		case TYPE_LARGEWEAPON:
		case TYPE_RANGEDWEAPON:
			return true;
			break;
		default:
			break;
	}
	return false;
}

bool Item::isArmor() const {
	switch (m_Type) {
		case TYPE_ARMOR:
		case TYPE_SHIELD:
		case TYPE_BOOTS:
		case TYPE_CLOAK:
		case TYPE_GLOVES:
		case TYPE_HELMET:
			return true;
			break;
		default:
			break;
	}
	return false;
}

ItemLargeIcon Item::getLargeIcon() const {
	return m_LargeIcon;
}

ItemSmallIcon Item::getSmallIcon() const {
	// l'icône "Small" est toujours la même en fonction du type d'item
	// contrairement à l'icône "Large"
	switch (m_Type) {
		case TYPE_ARMOR:
			return SMALLICON_ARMOR;
			break;
		case TYPE_HELMET:
			return SMALLICON_HELMET;
			break;
		case TYPE_SHIELD:
			return SMALLICON_SHIELD;
			break;
		case TYPE_BOOTS:
			return SMALLICON_BOOTS;
			break;
		case TYPE_CLOAK:
			return SMALLICON_CLOAK;
			break;
		case TYPE_GLOVES:
			return SMALLICON_GLOVES;
			break;
		case TYPE_LARGEWEAPON:
		case TYPE_WEAPON_SWORD:
			return SMALLICON_SWORD;
			break;
		case TYPE_WEAPON_AXE:
			return SMALLICON_AXE;
			break;
		case TYPE_WEAPON_DAGGER:
			return SMALLICON_DAGGER;
			break;
		case TYPE_WEAPON_HAMMER:
			return SMALLICON_HAMMER;
			break;
		case TYPE_RANGEDWEAPON:
			return SMALLICON_BOW2;
			break;
		case TYPE_POTION_MANA:
			return SMALLICON_POTION_MANA;
			break;
		case TYPE_POTION_HEAL:
			return SMALLICON_POTION_HEAL;
			break;
		case TYPE_RING:
			return SMALLICON_RING;
			break;
		case TYPE_NECKLACE:
			return SMALLICON_NECKLACE;
			break;
		case TYPE_BELT:
			return SMALLICON_BELT;
			break;
		default:
			break;
	}
	return SMALLICON_UNKNOWN;
}

/**
 * Définit le nom de l'item
 * @param std::string sName nom de l'item
 */
void Item::setName(const std::string sName) {
	m_sName = sName;
}

/**
 * Renvoie le type de l'item
 * @return ItemType type de l'item
 */
ItemType Item::getType() const {
	return m_Type;
}

int Item::getValue() const {
	return m_value;
}

/**
 * Renvoie les bonus de l'item
 * @return Stats bonus de l'item
 */
Stats Item::getStats() const {
	return m_statBonus;
}

int Item::getHigherBonus() const {
	int bonus = 0;
	bonus = MAX(bonus, m_statBonus.force);
	bonus = MAX(bonus, m_statBonus.dexterity);
	bonus = MAX(bonus, m_statBonus.constitution);
	bonus = MAX(bonus, m_statBonus.intelligence);
	bonus = MAX(bonus, m_statBonus.wisdom);
	bonus = MAX(bonus, m_statBonus.charisma);
	return bonus;
}

std::string Item::getBonusString() const {
	std::ostringstream os;
	os.str("");
	bool empty = true;
	if (m_statBonus.force > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "FOR:";
		os << m_statBonus.force;
	}
	if (m_statBonus.dexterity > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "DEX:";
		os << m_statBonus.dexterity;
	}
	if (m_statBonus.constitution > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "CON:";
		os << m_statBonus.constitution;
	}
	if (m_statBonus.intelligence > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "INT:";
		os << m_statBonus.intelligence;
	}
	if (m_statBonus.wisdom > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "WIS:";
		os << m_statBonus.wisdom;
	}
	if (m_statBonus.charisma > 0) {
		if (!empty)
			os << " ";
		else
			empty = false;
		os << "CHA:";
		os << m_statBonus.charisma;
	}
	return os.str();
}

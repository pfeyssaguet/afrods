#include "itemweapon.h"

#include <sstream>
#include <stdlib.h>

using namespace AfroDS;

ItemWeapon::ItemWeapon(const std::string sName, const ItemType type, const Coords dice) : Item(sName, type), m_dice(dice) {
}

ItemWeapon::ItemWeapon(const std::string sName, const ItemType type, const Coords dice, const ItemLargeIcon largeIcon) : Item(sName, type, largeIcon), m_dice(dice) {
}

ItemWeapon::ItemWeapon(const std::string sName, const ItemType type, const Stats stats, const Coords dice) : Item(sName, type, stats), m_dice(dice) {
}

ItemWeapon::ItemWeapon(const std::string sName, const ItemType type, const Stats stats, const Coords dice, const ItemLargeIcon largeIcon) : Item(sName, type, stats, largeIcon), m_dice(dice) {
}

bool ItemWeapon::isRangedWeapon() const {
	if (m_Type == TYPE_RANGEDWEAPON) {
		return true;
	}
	return false;
}

std::string ItemWeapon::getLongName() const {
	std::ostringstream os;
	os << m_sName;

	// on rajoute les dés de dégâts
	os << "(";
	os << m_dice.x;
	os << "D";
	os << m_dice.y;
	os << ")";

	// si on a un bonus on affiche le meilleur bonus entre parenthèses
	int bonus = getHigherBonus();
	if (bonus > 0) {
		os << "(+";
		os << bonus;
		os << ")";
	}

	return os.str();
}

std::string ItemWeapon::getDescription() const {
	std::ostringstream os;
	os << getName();

	// on rajoute les dés de dégâts
	os << '\n';
	os << "Damage : ";
	os << m_dice.x;
	os << "D";
	os << m_dice.y;

	std::string sBonus = getBonusString();
	if (sBonus.length() > 0) {
		os << '\n';
		os << "Bonus : ";
		os << sBonus;
	}

	return os.str();
}

int ItemWeapon::rollDamage() const {
	// on doit lancer des dés : xDy
	int value = 0;

	// on lance X fois 1 dé Y
	for (int i = 0 ; i < m_dice.x ; i++) {
		value += RollDice(m_dice.y);
	}
	return value;
}

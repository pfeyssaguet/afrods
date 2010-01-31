#include "itemarmor.h"

#include <sstream>


using namespace AfroDS;

ItemArmor::ItemArmor(const std::string sName) : Item(sName, TYPE_ARMOR), m_armorFactor(0) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type) : Item(sName, type), m_armorFactor(0) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type, const ItemLargeIcon largeIcon) : Item(sName, type, largeIcon), m_armorFactor(0) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type, const int armorFactor) : Item(sName, type), m_armorFactor(armorFactor) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const ItemLargeIcon largeIcon) : Item(sName, type, largeIcon), m_armorFactor(armorFactor) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const Stats stats) : Item(sName, type, stats), m_armorFactor(armorFactor) {
}

ItemArmor::ItemArmor(const std::string sName, const ItemType type, const int armorFactor, const Stats stats, const ItemLargeIcon largeIcon) : Item(sName, type, stats, largeIcon), m_armorFactor(armorFactor) {
}

std::string ItemArmor::getLongName() const {
	std::ostringstream os;
	os << m_sName;

	// si on a un facteur d'armure supérieur à 0, on le rajoute entre parenthèses
	if (m_armorFactor > 0) {
		os << "(";
		os << m_armorFactor;
		os << ")";
	}

	// si on a un bonus on affiche le meilleur bonus entre parenthèses
	int bonus = getHigherBonus();
	if (bonus > 0) {
		os << "(+";
		os << bonus;
		os << ")";
	}

	return os.str();
}

std::string ItemArmor::getDescription() const {
	std::ostringstream os;
	os << getName();

	// si on a un facteur d'armure supérieur à 0, on le rajoute
	if (m_armorFactor > 0) {
		os << '\n';
		os << "Factor : ";
		os << m_armorFactor;
	}

	std::string sBonus = getBonusString();
	if (sBonus.length() > 0) {
		os << '\n';
		os << "Bonus : ";
		os << sBonus;
	}

	return os.str();
}

int ItemArmor::getArmorFactor() const {
	return m_armorFactor;
}

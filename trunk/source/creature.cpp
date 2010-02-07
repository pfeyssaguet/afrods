#include "creature.h"

using namespace AfroDS;

/**
 * Constructeur initialisant le nom
 * @param std::string sName nom du personnage
 */
Creature::Creature(const std::string sName) : m_money(0) {
	// initialisation du nom
	m_sName = sName;

	// initialisation de l'équipement vide
	for (int i = 0 ; i < SLOT_SIZE ; i++) {
		m_equipment[(EquipmentSlot)i] = NULL;
	}
}

Creature::~Creature() {
	// on doit vider l'inventaire et l'équipement

	// on vide l'équipement
	for (int slot = 0 ; slot < SLOT_SIZE ; slot++) {
		Item * item = getEquipmentItem((EquipmentSlot)slot);
		if (item != NULL) {
			delete item;
		}
	}

	// on vide l'inventaire
	while (!m_inventory.empty()) {
		delete m_inventory.at(0);
		m_inventory.erase(m_inventory.begin());
	}
}

void Creature::addMoney(const long money) {
	m_money += money;
}

void Creature::subMoney(const long money) {
	if (money > m_money) {
		m_money = 0;
	} else {
		m_money = money;
	}
}

long Creature::getMoney() const {
	return m_money;
}

int Creature::XpToLevel(const long xp) {
	/*
	 * 01 	0 			4 	2 	1er 	-
	 * 02 	1.000 		5 	2 	- 	-
	 * 03 	3.000 		6 	3 	2e 	-
	 * 04 	6.000 		7 	3 	- 	1ere
	 * 05 	10.000 		8 	4 	- 	-
	 * 06 	15.000 		9 	4 	3e 	-
	 * 07 	21.000 		10 	5 	- 	-
	 * 08 	28.000 		11 	5 	- 	2e
	 * 09 	36.000 		12 	6 	4e 	-
	 * 10 	45.000 		13 	6 	- 	-
	 * 11 	55.000 		14 	7 	- 	-
	 * 12 	66.000 		15 	7 	5e 	3e
	 * 13 	78.000 		16 	8 	- 	-
	 * 14 	91.000 		17 	8 	- 	-
	 * 15 	105.000 	18 	9 	6e 	-
	 * 16 	120.000 	19 	9 	- 	4e
	 * 17 	136.000 	20 	10 	- 	-
	 * 18 	153.000 	21 	10 	7e 	-
	 * 19 	171.000 	22 	11 	- 	-
	 * 20 	190.000 	23 	11 	- 	5e
	 */
	if (xp < 1000) {
		return 1;
	} else if (xp < 3000) {
		return 2;
	} else if (xp < 6000) {
		return 3;
	} else if (xp < 10000) {
		return 4;
	} else if (xp < 15000) {
		return 5;
	} else {
		return 6;
	}
}

long Creature::XpForNextLevel(const long xp) {
	if (xp < 1000) {
		return 1000 - xp;
	} else if (xp < 3000) {
		return 3000 - xp;
	} else if (xp < 6000) {
		return 6000 - xp;
	} else if (xp < 10000) {
		return 10000 - xp;
	} else if (xp < 15000) {
		return 15000 - xp;
	} else {
		return 0;
	}
}

/**
 * Méthode statique utilitaire permettant de traduire un slot
 * en string pour l'afficher dans le menu (comme un toString() pour
 * l'enum EquipmentSlot)
 * @param EquipmentSlot slot à traduire
 * @return std::string chaîne de caractères
 */
std::string Creature::translateSlot(const EquipmentSlot slot) {
	return translateSlot(slot, false);
}

/**
 * Méthode statique utilitaire permettant de traduire un slot
 * en string pour l'afficher dans le menu (comme un toString() pour
 * l'enum EquipmentSlot)
 * @param EquipmentSlot slot à traduire
 * @param const bool shortName pour avoir le nom court
 * @return std::string chaîne de caractères
 */
std::string Creature::translateSlot(const EquipmentSlot slot, const bool shortName) {
	switch (slot) {
		case SLOT_ARMOR:
			return shortName ? "A" : "Armor";
			break;
		case SLOT_BELT:
			return shortName ? "B" : "Belt";
			break;
		case SLOT_BOOTS:
			return shortName ? "F" : "Boots";
			break;
		case SLOT_CLOAK:
			return shortName ? "C" : "Cloak";
			break;
		case SLOT_GLOVES:
			return shortName ? "G" : "Gloves";
			break;
		case SLOT_HELMET:
			return shortName ? "H" : "Helmet";
			break;
		case SLOT_LEFT_RING:
			return shortName ? "R" : "Left Ring";
			break;
		case SLOT_LEFT_WEAPON:
			return shortName ? "W" : "Left Hand";
			break;
		case SLOT_NECKLACE:
			return shortName ? "N" : "Necklace";
			break;
		case SLOT_RIGHT_RING:
			return shortName ? "R" : "Right Ring";
			break;
		case SLOT_RIGHT_WEAPON:
			return shortName ? "W" : "Right Hand";
			break;
		default:
			return shortName ? "U" : "Unknown";
			break;
	}
}

/**
 * Renvoie les stats de base du personnage, sans bonus
 * @return Stats stats de base du perso
 */
Stats Creature::getBaseStats() const {
	return m_baseStats;
}

long Creature::getCurrentHp() const {
	return m_currentHp;
}

void Creature::setCurrentHp(const int hp) {
	m_currentHp = hp;
}

long Creature::getCurrentMp() const {
	return m_currentMp;
}

void Creature::setCurrentMp(const int mp) {
	m_currentMp = mp;
}

long Creature::getMaxHp() const {
	return m_maxHp;
}

long Creature::getMaxMp() const {
	return m_maxMp;
}

/**
 * Renvoie le nom du personnage
 * @return std::string nom du personnage
 */
std::string Creature::getName() const {
	return m_sName;
}

/**
 * Définit le nom du personnage
 * @param std::string sName nom du personnage
 */
void Creature::setName(const std::string sName) {
	m_sName = sName;
}

/**
 * Ajoute un item dans l'équipement
 * @param EquipmentSlot slot slot dans lequel équiper l'item
 * @param Item * item item à équiper (pointeur)
 */
void Creature::addItemToEquipment(const EquipmentSlot slot, Item * item) {
	if (m_equipment[slot] == NULL) {
		m_equipment[slot] = item;
	}
}

/**
 * Renvoie l'item d'équipement correspondant au slot demandé
 * @param EquipmentSlot slot slot demandé
 * @return Item * item d'équipement (pointeur)
 */
Item * Creature::getEquipmentItem(const EquipmentSlot slot) const {
	return m_equipment.find(slot)->second;
}

int Creature::getBonusAttack() const {
	/*
	 * Avec une arme de corps à corps, le bonus d'attaque est égal à :
	 * Bonus de base à l'attaque + modificateur de Force
	 *
	 * Avec une arme à distance, il devient :
	 * Bonus de base à l'attaque + modificateur de Dextérité
	 */
	// bonus d'attaque = modificateur de force
	int bonus;

	// on regarde l'arme utilisée dans la main droite
	if (m_equipment.find(SLOT_RIGHT_WEAPON)->second != NULL) {
		Item * item = m_equipment.find(SLOT_RIGHT_WEAPON)->second;
		ItemWeapon * weapon = (ItemWeapon *)item;
		if (weapon->isRangedWeapon()) {
			// arme à distance, on prend la dex
			bonus = StatModifier(getStats().dexterity);
		} else {
			// arme de corps à corps, on prend la force
			bonus = StatModifier(getStats().force);
		}
	} else {
		// pas d'arme, on prend la force
		bonus = StatModifier(getStats().force);
	}

	return bonus;
}

int Creature::getArmorClass() const {
	// 10 + bonus d'armure + bonus de bouclier + modificateur de Dextérité
	int armorClass = 10;

	// on regarde dans les slots d'équipement d'armure
	if (m_equipment.find(SLOT_ARMOR)->second) {
		Item * item = m_equipment.find(SLOT_ARMOR)->second;
		ItemArmor * armor = (ItemArmor *)item;
		armorClass += armor->getArmorFactor();
	}

	if (m_equipment.find(SLOT_LEFT_WEAPON)->second != NULL) {
		Item * item = m_equipment.find(SLOT_LEFT_WEAPON)->second;
		if (item->isArmor()) {
			ItemArmor * armor = (ItemArmor *)item;
			armorClass += armor->getArmorFactor();
		}
	}
	// modificateur de dex
	armorClass += StatModifier(getStats().dexterity);

	return armorClass;
}

int Creature::attack(Creature * target) {
/*
 * Pour effectuer un jet d'attaque, on jette 1d20 auquel on ajoute le bonus d'attaque du personnage.
 * Si le résultat final égale ou dépasse la CA de l'adversaire, le coup touche et inflige des dégâts.
 * Coup automatiquement réussi ou raté :
 * - On rate automatiquement son coup sur un 1 naturel (c'est-à-dire au dé, avant modificateur) au jet d'attaque.
 * - De la même manière, l'attaque passe toujours sur un 20 naturel (à noter que celui-ci est également un coup critique possible).
 */

	int damage = 0;

	int dice = RollDice20;
	if (dice == 1) {
		// échec critique
		damage = 0;
	} else if (dice == 20) {
		// réussite critique
		damage = rollAttack();
	} else if (dice + getBonusAttack() >= target->getArmorClass()) {
		// attaque réussie
		damage = rollAttack();
	}

	target->setCurrentHp(target->getCurrentHp() - damage);
	return damage;
}

/**
 * Ajoute un item dans l'inventaire
 * @param Item item l'item à ajouter
 */
void Creature::addItemToInventory(Item * item) {
	m_inventory.push_back(item);
}

/**
 * Renvoie le nombre d'items dans l'inventaire
 * @return int nombre d'items
 */
unsigned int Creature::getInventorySize() const {
	return m_inventory.size();
}

/**
 * Renvoie l'item n° N de l'inventaire
 * @param int iNumItem numéro de l'item à récupérer
 * @return Item item récupéré
 */
Item * Creature::getInventoryItem(const int iNumItem) {
	return getInventoryItem(iNumItem, false);
}

Item * Creature::getInventoryItem(const int iNumItem, bool extract) {
	Item * item = m_inventory.at(iNumItem);
	if (extract) {
		m_inventory.erase(m_inventory.begin() + iNumItem);
	}
	return item;
}


void Creature::deleteInventoryItem(const int iNumItem) {
	delete m_inventory.at(iNumItem);
	m_inventory.erase(m_inventory.begin() + iNumItem);
}

/**
 * Equipe un item de l'inventaire si possible, et renvoie true en cas de succès
 * @param unsigned int iNumItem numéro de l'item d'inventaire
 * @return bool false en cas d'échec
 */
bool Creature::equipItem(const unsigned int iNumItem) {
	// on vérifie que l'item existe
	if (m_inventory.size() <= iNumItem) {
		return false;
	}

	// on récupére l'item
	Item * item = m_inventory.at(iNumItem);

	EquipmentSlot slot;

	switch (item->getType()) {
		case TYPE_ARMOR:
			slot = SLOT_ARMOR;
			break;
		case TYPE_BELT:
			slot = SLOT_BELT;
			break;
		case TYPE_WEAPON_AXE:
		case TYPE_WEAPON_DAGGER:
		case TYPE_WEAPON_HAMMER:
		case TYPE_WEAPON_SWORD:
			slot = SLOT_RIGHT_WEAPON;
			if (m_equipment[slot] != NULL) {
				slot = SLOT_LEFT_WEAPON;
			}
			break;
		case TYPE_SHIELD:
		case TYPE_LARGEWEAPON:
		case TYPE_RANGEDWEAPON:
			slot = SLOT_RIGHT_WEAPON;
			break;
		case TYPE_BOOTS:
			slot = SLOT_BOOTS;
			break;
		case TYPE_CLOAK:
			slot = SLOT_CLOAK;
			break;
		case TYPE_GLOVES:
			slot = SLOT_GLOVES;
			break;
		case TYPE_HELMET:
			slot = SLOT_HELMET;
			break;
		case TYPE_NECKLACE:
			slot = SLOT_NECKLACE;
			break;
		case TYPE_RING:
			slot = SLOT_RIGHT_RING;
			if (m_equipment[slot] != NULL) {
				slot = SLOT_LEFT_RING;
			}
			break;
		default:
			slot = SLOT_SIZE;
			// ce slot ne s'équipe pas, on sort
			return false;
			break;
	}

	// on regarde si le slot est vide
	if (m_equipment[slot] != NULL) {
		unequipItem(slot);
	}

	// si c'est une grande arme on vide aussi le slot de main gauche
	if (item->getType() == TYPE_LARGEWEAPON || item->getType() == TYPE_RANGEDWEAPON) {
		if (m_equipment[SLOT_LEFT_WEAPON] != NULL) {
			unequipItem(SLOT_LEFT_WEAPON);
		}
	}

	// on met le nouvel item à la place
	m_equipment[slot] = item;

	// on le retire de l'inventaire
	m_inventory.erase(m_inventory.begin() + iNumItem);

	// on a réussi à équiper l'item donc on renvoie true
	return true;
}

/**
 * Retire un item d'équipement et le remet dans l'inventaire
 * @param EquipmentSlot slot slot d'équipement à vider
 * @return bool false en cas d'échec
 */
bool Creature::unequipItem(EquipmentSlot slot) {
	// on doit retirer l'item et le mettre dans l'inventaire
	// s'il n'y avait aucun item, on renvoie false
	if (m_equipment[slot] == NULL) {
		return false;
	}

	// s'il y avait un item on le met dans l'inventaire
	m_inventory.push_back(m_equipment[slot]);

	// on supprime l'item
	m_equipment[slot] = NULL;

	// on a réussi à retirer l'item donc on renvoie true
	return true;
}

void Creature::activateInventoryItem(const unsigned int iNumItem) {
	// on récup_re l'item
	Item * item = m_inventory.at(iNumItem);

	// on active l'item
	if (activateItem(item)) {
		// si l'item est détruit, on le retire de l'inventaire
		delete item;
		m_inventory.erase(m_inventory.begin() + iNumItem);
	}
}

bool Creature::activateItem(Item * item) {
	if (item->getType() == TYPE_POTION_HEAL) {
		m_currentHp += item->getValue();
		if (m_currentHp > m_maxHp) {
			m_currentHp = m_maxHp;
		}
		return true;
	} else if (item->getType() == TYPE_POTION_MANA) {
		m_currentMp += item->getValue();
		if (m_currentMp > m_maxMp) {
			m_currentMp = m_maxMp;
		}
		return true;
	}
	return false;
}

int Creature::rollAttack() const {
	int damage = 0;

	// on prend l'arme du slot de droite
	if (m_equipment.find(SLOT_RIGHT_WEAPON)->second != NULL) {
		// on récupère l'item et ses stats
		Item * item = m_equipment.find(SLOT_RIGHT_WEAPON)->second;
		ItemWeapon * weapon = (ItemWeapon *) item;

		damage = weapon->rollDamage();
	}

	// on prend l'arme du slot de gauche
	if (m_equipment.find(SLOT_LEFT_WEAPON)->second != NULL) {
		// on récupère l'item et ses stats
		Item * item = m_equipment.find(SLOT_LEFT_WEAPON)->second;
		if (item->isWeapon()) {
			ItemWeapon * weapon = (ItemWeapon *) item;
			damage += weapon->rollDamage();
		}
	}

	// TODO gestion des dégâts à main nue : pour l'instant 1D3
	if (m_equipment.find(SLOT_RIGHT_WEAPON)->second == NULL && m_equipment.find(SLOT_LEFT_WEAPON)->second == NULL) {
		damage = RollDice(3);
	}

	return damage;
}

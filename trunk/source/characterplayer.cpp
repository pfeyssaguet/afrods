#include "characterplayer.h"

using namespace AfroDS;

CharacterPlayer::CharacterPlayer(const std::string sName) : Character(sName), m_charClass(CLASS_WARRIOR) {
	// on initialise le reste du perso
	initCharacter();
}


CharacterPlayer::CharacterPlayer(const std::string sName, const CharacterClass charClass) : Character(sName), m_charClass(charClass) {
	initCharacter();
}
/*
CharacterPlayer::~CharacterPlayer() {
}
*/
void CharacterPlayer::initCharacter() {
	m_move_speed = AFRODS_CHAR_SPEED;
	m_xp = 0;

	// Stats(int p_force, int p_constitution, int p_dexterity, int p_wisdom, int p_charisma, int p_intelligence)
	// initialisation des stats du perso
	switch (m_charClass) {
		case CLASS_WARRIOR:
			m_baseStats = Stats(18, 16, 14, 8, 10, 6);
			m_maxHp = 30;
			m_maxMp = 0;
			break;
		case CLASS_WIZARD:
			m_baseStats = Stats(6, 10, 10, 14, 6, 18);
			m_maxHp = 10;
			m_maxMp = 20;
			break;
		case CLASS_RANGER:
			m_baseStats = Stats(14, 14, 18, 6, 8, 10);
			m_maxHp = 25;
			m_maxMp = 5;
			break;
		case CLASS_PRIEST:
			m_baseStats = Stats(6, 10, 10, 18, 6, 16);
			m_maxHp = 15;
			m_maxMp = 15;
			break;
		case CLASS_MONK:
			m_baseStats = Stats(17, 17, 17, 8, 8, 8);
			m_maxHp = 20;
			m_maxMp = 10;
			break;
		default:
			m_baseStats = Stats(AFRODS_BASESTAT_FORCE, AFRODS_BASESTAT_CONSTITUTION, AFRODS_BASESTAT_DEXTERITY, AFRODS_BASESTAT_WISDOM, AFRODS_BASESTAT_CHARISMA, AFRODS_BASESTAT_INTELLIGENCE);
			m_maxHp = 30;
			m_maxMp = 0;
			break;
	}
	m_currentHp = m_maxHp;
	m_currentMp = m_maxMp;

}


/**
 * Renvoie les stats du personnage, avec les bonus et modificateurs appliqués
 * @return Stats stats du personnage
 */
Stats CharacterPlayer::getStats() const {
	// on prend les stats de base
	Stats stats = m_baseStats;

	// on parcourt l'équipement pour ajouter les bonus aux stats de base
	for (int i = SLOT_ARMOR ; i <= SLOT_BELT ; i++) {
		EquipmentSlot slot = (EquipmentSlot)i;
		// si on a un item dans le slot
		if (m_equipment.find(slot)->second != NULL) {
			// on récupère l'item et ses stats
			//Item * item = m_equipment.at(slot);
			Item * item = m_equipment.find(slot)->second;

			Stats itemStats = item->getStats();

			// on ajoute les stats
			stats = stats + itemStats;
			/*
			stats.force += itemStats.force;
			stats.dexterity += itemStats.dexterity;
			stats.constitution += itemStats.constitution;
			stats.intelligence += itemStats.intelligence;
			stats.wisdom += itemStats.wisdom;
			stats.charisma += itemStats.charisma;
			*/
		}
	}
	// on renvoie les stats calculées
	return stats;
}

int CharacterPlayer::getLevel() const {
	return XpToLevel(m_xp);
}

std::string CharacterPlayer::translateClass(CharacterClass charClass) {
	switch (charClass) {
		case CLASS_WARRIOR:
			return "Warrior";
			break;
		case CLASS_WIZARD:
			return "Wizard";
			break;
		case CLASS_RANGER:
			return "Ranger";
			break;
		case CLASS_PRIEST:
			return "Priest";
			break;
		case CLASS_MONK:
			return "Monk";
			break;
	}
	return "Unknown";
}

void CharacterPlayer::setClass(CharacterClass charClass) {
	m_charClass = charClass;
}

CharacterClass CharacterPlayer::getClass() const {
	return m_charClass;
}

bool CharacterPlayer::hasMagic() const {
	if (m_maxMp > 0) {
		return true;
	}
	return false;
}

/**
 * Renvoie l'expérience du personnage
 * @return long expérience
 */
long CharacterPlayer::getExperience() const {
	return m_xp;
}

/**
 * Renvoie la position X
 * @return int position X
 */
int CharacterPlayer::getPosX() const {
	return m_position.x;
}

/**
 * Définit la position X
 * @param int x position X
 */
void CharacterPlayer::setPosX(const int x) {
	m_position.x = x;
}

/**
 * Renvoie la position Y
 * @return int position Y
 */
int CharacterPlayer::getPosY() const {
	return m_position.y;
}

/**
 * Définit la position Y
 * @param int y position Y
 */
void CharacterPlayer::setPosY(const int y) {
	m_position.y = y;
}

/**
 * Renvoie la position avec un type personnalisé
 * @return AF_Coords position
 */
Coords CharacterPlayer::getPos() const {
	return m_position;
}

/**
 * Définit la position avec un type personnalisé
 * @param AF_Coords pos position
 */
void CharacterPlayer::setPos(const Coords pos) {
	m_position = pos;
}

/**
 * Définit les positions de X et Y
 * @param int x position X
 * @param int y position Y
 */
void CharacterPlayer::setPos(const int x, const int y) {
	m_position.x = x;
	m_position.y = y;
}

/**
 * Renvoie la vitesse de déplacement du personnage
 */
int CharacterPlayer::getMoveSpeed() const {
	return m_move_speed;
}

void CharacterPlayer::addXp(const int xp) {
	m_xp += xp;
}

int CharacterPlayer::rollAttack() const {
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

	return damage;
}

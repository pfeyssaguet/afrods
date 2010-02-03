#include "charactermonster.h"

using namespace AfroDS;

std::map<MonsterType, MonsterDescription> CharacterMonster::m_monsterDescriptions;

CharacterMonster::CharacterMonster(MonsterType type) : Character(translateMonsterType(type)), m_type(type) {
	if (m_monsterDescriptions.empty())
		initMonsterDescriptions();

	if (m_monsterDescriptions.find(m_type) == m_monsterDescriptions.end()) {
		// le type de mob est introuvable, on charge les valeurs par défaut !
		m_maxHp = 3;
		m_maxMp = 0;
	} else {
		// on charge le contenu de la structure dans le mob courant
		MonsterDescription desc = m_monsterDescriptions[m_type];

		// les points de vie, de mana, et les stats
		m_maxHp = desc.maxHp;
		m_maxMp = desc.maxMp;
		m_baseStats = desc.stats;

		// l'argent
		m_money = desc.money;

		// les loots
		for (unsigned int i = 0 ; i < desc.loots.size() ; i++) {
			MonsterLoot loot = desc.loots.at(i);
			// on lance 1D100 pour voir si le monstre possède cet item
			int roll = RollDice(100);
			// si le résultat est supérieur ou égal à la chance de looter l'item
			if (roll >= 100 - loot.chance) {
				// on le met dans l'inventaire du monstre
				addItemToInventory(ItemFactory::generateLoot(loot.loot));
			}
		}
	}

	m_currentHp = m_maxHp;
	m_currentMp = m_maxMp;
}

void CharacterMonster::initMonsterDescriptions() {
	std::vector<MonsterLoot> loots;

	// MonsterDescription(std::string p_sName, int p_Hp, int p_Mp, Stats p_stats)
	// Stats(int p_force, int p_constitution, int p_dexterity, int p_wisdom, int p_charisma, int p_intelligence, int p_xp, long p_money)

	// -------------- RAT
	loots.push_back(MonsterLoot(LOOT_POTION_HEAL, 50));
	m_monsterDescriptions[MONSTER_RAT] 				= MonsterDescription("Rat", 				 3, 0, Stats( 8, 0,  8, 0, 0, 0),   1,   3, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- IMP
	loots.push_back(MonsterLoot(LOOT_POTION_HEAL, 50));
	m_monsterDescriptions[MONSTER_IMP] 				= MonsterDescription("Imp", 				 8, 0, Stats( 8, 0, 14, 0, 0, 0),   3,   7, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- FROG
	loots.push_back(MonsterLoot(LOOT_SWORD, 50));
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_FROG] 			= MonsterDescription("Frog", 				11, 0, Stats(12, 0, 14, 0, 0, 0),   3,   8, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- BAT
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_BAT] 				= MonsterDescription("Bat", 				12, 0, Stats(15, 0, 18, 0, 0, 0),   5,  12, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- OGRE
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_OGRE] 			= MonsterDescription("Ogre", 				13, 0, Stats(16, 0, 12, 0, 0, 0),  10,  25, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- KNIGHT
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_KNIGHT] 			= MonsterDescription("Knight", 				15, 0, Stats(17, 0, 16, 0, 0, 0),  12,  30, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- EARTH ELEMENTAL
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_EARTH_ELEMENTAL] 	= MonsterDescription("Earth Elemental", 	17, 0, Stats(13, 0,  6, 0, 0, 0),  12,  40, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- GORILLA
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_GORILLA] 			= MonsterDescription("Gorilla", 			22, 0, Stats(17, 0, 18, 0, 0, 0),  30,  75, loots);
	loots.erase(loots.begin(), loots.end());

	// -------------- DRAGON
	loots.push_back(MonsterLoot(LOOT_POTION_HEAL, 80));
	loots.push_back(MonsterLoot(LOOT_POTION_MANA, 80));
	loots.push_back(MonsterLoot(LOOT_ARTIFACT_SWORD_OF_BOULBI, 100));
	m_monsterDescriptions[MONSTER_DRAGON] 			= MonsterDescription("Dragon", 				50, 0, Stats(20, 0, 18, 0, 0, 0), 100, 300, loots);
}

int CharacterMonster::getXp() const {
	MonsterDescription desc = m_monsterDescriptions.find(m_type)->second;
	return desc.xp;
}

std::string CharacterMonster::translateMonsterType(MonsterType type) {
	if (m_monsterDescriptions.empty())
		initMonsterDescriptions();

	if (m_monsterDescriptions.find(type) == m_monsterDescriptions.end()) {
		return "Unknown";
	} else {
		MonsterDescription desc = m_monsterDescriptions[type];
		return desc.sName;
	}
}

Stats CharacterMonster::getStats() const {
	return getBaseStats();
}

#ifndef __CHARACTERMONSTER_H__
#define __CHARACTERMONSTER_H__

#include "character.h"
#include "itemfactory.h"
#include <map>
#include <string>

namespace AfroDS {

	enum MonsterType {
		MONSTER_BAT, MONSTER_RAT, MONSTER_FROG,
		MONSTER_IMP, MONSTER_KNIGHT, MONSTER_EARTH_ELEMENTAL,
		MONSTER_GORILLA, MONSTER_OGRE, MONSTER_DRAGON
	};

	struct MonsterLoot {
		MonsterLoot() {
		}

		MonsterLoot(const ItemLoot p_loot, const int p_chance) {
			loot = p_loot;
			chance = p_chance;
		}

		ItemLoot loot;
		int chance;
	};

	struct MonsterDescription {
		MonsterDescription() {
			sName = "";
			maxHp = 0;
			maxMp = 0;
			xp = 0;
			money = 0;
		}

		MonsterDescription(const std::string p_sName) {
			sName = p_sName;
			maxHp = 3;
			maxMp = 0;
			xp = 0;
			money = 0;
		}

		MonsterDescription(const std::string p_sName, const int p_Hp) {
			sName = p_sName;
			maxHp = p_Hp;
			maxMp = 0;
			xp = 0;
			money = 0;
		}

		MonsterDescription(const std::string p_sName, const int p_Hp, const int p_Mp) {
			sName = p_sName;
			maxHp = p_Hp;
			maxMp = p_Mp;
			xp = 0;
			money = 0;
		}

		MonsterDescription(const std::string p_sName, const int p_Hp, const int p_Mp, const Stats p_stats, const int p_xp) {
			sName = p_sName;
			maxHp = p_Hp;
			maxMp = p_Mp;
			stats = p_stats;
			xp = p_xp;
			money = 0;
		}

		MonsterDescription(const std::string p_sName, const int p_Hp, const int p_Mp, const Stats p_stats, const int p_xp, const long p_money) {
			sName = p_sName;
			maxHp = p_Hp;
			maxMp = p_Mp;
			stats = p_stats;
			xp = p_xp;
			money = p_money;
		}

		MonsterDescription(const std::string p_sName, const int p_Hp, const int p_Mp, const Stats p_stats, const int p_xp, const long p_money, std::vector<MonsterLoot> p_loots) {
			sName = p_sName;
			maxHp = p_Hp;
			maxMp = p_Mp;
			stats = p_stats;
			xp = p_xp;
			money = p_money;
			loots = p_loots;
		}

		std::string sName;
		int maxHp;
		int maxMp;
		Stats stats;
		int xp;
		long money;
		std::vector<MonsterLoot> loots;
	};

	class CharacterMonster : public Character {

		public:
			CharacterMonster(const MonsterType type);

			static std::string translateMonsterType(const MonsterType type);

			Stats getStats() const;

			int getXp() const;

		private:
			static void initMonsterDescriptions();

			static std::map<MonsterType, MonsterDescription> m_monsterDescriptions;

			MonsterType m_type;
	};

}

#endif

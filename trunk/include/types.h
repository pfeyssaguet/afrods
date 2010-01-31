#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>

#define RollDice(faces) (1 + rand() % (faces))
#define RollDice20 RollDice(20)
#define MAX(x, y) ((x) > (y) ? (x) : (y))

namespace AfroDS {
	/**
	 * Structure pour d�crire un couple de coordonn�es
	 */
	struct Coords {
		/**
		 * Constructeur par d�faut qui initialise les variables � 0
		 */
		Coords() {
			x = 0;
			y = 0;
		}

		/**
		 * Constructeur avec param�tres
		 * @param int p_x coordonn�e X
		 * @param int p_y coordonn�e Y
		 */
		Coords(const int p_x, const int p_y) {
			x = p_x;
			y = p_y;
		}

		Coords operator+(const Coords coords) {
			Coords retCoord;
			retCoord.x = coords.x + x;
			retCoord.y = coords.y + y;
			return retCoord;
		}

		bool operator==(const Coords coords) {
			if (coords.x == x && coords.y == y) {
				return true;
			} else {
				return false;
			}
		}

		bool operator!=(const Coords coords) {
			if (coords.x == x && coords.y == y) {
				return false;
			} else {
				return true;
			}
		}

		int x;
		int y;
	};

	/** Structure pour d�crire les stats d'un perso */
	struct Stats {
		/**
		 * Constructeur par d�faut qui initialise les variables � 0
		 */
		Stats() {
			force = 0;
			constitution = 0;
			dexterity = 0;
			wisdom = 0;
			charisma = 0;
			intelligence = 0;
		}

		/**
		 * Constructeur avec param�tres
		 * @param int p_force force
		 * @param int p_constitution constitution
		 * @param int p_dexterity dexterit�
		 * @param int p_wisdom sagesse
		 * @param int p_charisma charisme
		 * @param int p_intelligence intelligence
		 */
		Stats(const int p_force, const int p_constitution, const int p_dexterity, const int p_wisdom, const int p_charisma, const int p_intelligence) {
			force = p_force;
			constitution = p_constitution;
			dexterity = p_dexterity;
			wisdom = p_wisdom;
			charisma = p_charisma;
			intelligence = p_intelligence;
		}

		Stats operator+(const Stats stats) {
			Stats retStats;
			retStats.force = force + stats.force;
			retStats.constitution = constitution + stats.constitution;
			retStats.dexterity = dexterity + stats.dexterity;
			retStats.wisdom = wisdom + stats.wisdom;
			retStats.charisma = charisma + stats.charisma;
			retStats.intelligence = intelligence + stats.intelligence;
			return retStats;
		}

		int force;
		int constitution;
		int dexterity;
		int wisdom;
		int charisma;
		int intelligence;
	};
}

#endif

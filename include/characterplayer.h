#ifndef __CHARACTERPLAYER_H_
#define __CHARACTERPLAYER_H_

#include "character.h"
#include "debug.h"

// Stats de base d'un perso
#define AFRODS_BASESTAT_FORCE 16
#define AFRODS_BASESTAT_CONSTITUTION 16
#define AFRODS_BASESTAT_DEXTERITY 16
#define AFRODS_BASESTAT_WISDOM 16
#define AFRODS_BASESTAT_CHARISMA 16
#define AFRODS_BASESTAT_INTELLIGENCE 16

#ifdef AFRODS_DEBUG_CHAR_SPEED
#define AFRODS_CHAR_SPEED AFRODS_DEBUG_CHAR_SPEED
#else
#define AFRODS_CHAR_SPEED 1
#endif

namespace AfroDS {

	enum CharacterClass {
		CLASS_WARRIOR, CLASS_WIZARD, CLASS_RANGER, CLASS_PRIEST, CLASS_MONK
	};

	class CharacterPlayer : public Character {
		public:
			CharacterPlayer(const std::string sName = "");

			CharacterPlayer(const std::string sName, const CharacterClass charClass);

			//~CharacterPlayer();

			void initCharacter();

			void setClass(const CharacterClass charClass);

			CharacterClass getClass() const;

			int getLevel() const;

			bool hasMagic() const;

			/**
			 * Renvoie les stats du personnage, avec les bonus et modificateurs appliqu�s
			 * @return Stats stats du personnage
			 */
			Stats getStats() const;

			/**
			 * Renvoie l'exp�rience du personnage
			 * @return long exp�rience
			 */
			long getExperience() const;

			/**
			 * Renvoie la position X
			 * @return int position X
			 */
			int getPosX() const;

			/**
			 * D�finit la position X
			 * @param int x position X
			 */
			void setPosX(const int x);

			/**
			 * Renvoie la position Y
			 * @return int position Y
			 */
			int getPosY() const;

			/**
			 * D�finit la position Y
			 * @param int y position Y
			 */
			void setPosY(const int y);

			/**
			 * Renvoie la position avec un type personnalis�
			 * @return AF_Coords position
			 */
			Coords getPos() const;

			/**
			 * D�finit la position avec un type personnalis�
			 * @param AF_Coords pos position
			 */
			void setPos(const Coords pos);

			/**
			 * D�finit les positions de X et Y
			 * @param int x position X
			 * @param int y position Y
			 */
			void setPos(const int x, const int y);

			/**
			 * Renvoie la vitesse de d�placement du personnage
			 */
			int getMoveSpeed() const;

			void addXp(const int xp);

			int rollAttack() const;

			static std::string translateClass(const CharacterClass charClass);

		private:
			/** Classe */
			CharacterClass m_charClass;

			/** Exp�rience */
			long m_xp;

			/** Position sur la map */
			Coords m_position;

			/** Vitesse de d�placement */
			int m_move_speed;
	};

}

#endif

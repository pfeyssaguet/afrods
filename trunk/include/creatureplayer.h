#ifndef __CREATUREPLAYER_H_
#define __CREATUREPLAYER_H_

#include "creature.h"
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

	enum Job {
		JOB_WARRIOR, JOB_WIZARD, JOB_RANGER, JOB_PRIEST, JOB_MONK
	};

	class CreaturePlayer : public Creature {
		public:
			CreaturePlayer(const std::string sName = "");

			CreaturePlayer(const std::string sName, const Job job);

			//~CreaturePlayer();

			void initCreature();

			void setJob(const Job job);

			Job getJob() const;

			int getLevel() const;

			bool hasMagic() const;

			/**
			 * Renvoie les stats du personnage, avec les bonus et modificateurs appliqués
			 * @return Stats stats du personnage
			 */
			Stats getStats() const;

			/**
			 * Renvoie l'expérience du personnage
			 * @return long expérience
			 */
			long getExperience() const;

			/**
			 * Renvoie la position X
			 * @return int position X
			 */
			int getPosX() const;

			/**
			 * Définit la position X
			 * @param int x position X
			 */
			void setPosX(const int x);

			/**
			 * Renvoie la position Y
			 * @return int position Y
			 */
			int getPosY() const;

			/**
			 * Définit la position Y
			 * @param int y position Y
			 */
			void setPosY(const int y);

			/**
			 * Renvoie la position avec un type personnalisé
			 * @return AF_Coords position
			 */
			Coords getPos() const;

			/**
			 * Définit la position avec un type personnalisé
			 * @param AF_Coords pos position
			 */
			void setPos(const Coords pos);

			/**
			 * Définit les positions de X et Y
			 * @param int x position X
			 * @param int y position Y
			 */
			void setPos(const int x, const int y);

			/**
			 * Renvoie la vitesse de déplacement du personnage
			 */
			int getMoveSpeed() const;

			void addXp(const int xp);

			int rollAttack() const;

			static std::string translateJob(const Job job);

		private:
			/** Classe */
			Job m_job;

			/** Expérience */
			long m_xp;

			/** Position sur la map */
			Coords m_position;

			/** Vitesse de déplacement */
			int m_move_speed;
	};

}

#endif

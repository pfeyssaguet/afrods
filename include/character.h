#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "types.h"
#include <string>

namespace AfroDS {

	/**
	 * Représente un personnage
	 */
	class Character {
		public:
			/**
			 * Constructeur par défaut
			 */
			Character();

			/**
			 * Constructeur initialisant le nom
			 * @param std::string sName nom du personnage
			 */
			Character(const std::string sName);

			/**
			 * Renvoie le nom du personnage
			 * @return std::string nom du personnage
			 */
			std::string getName() const;

			/**
			 * Définit le nom du personnage
			 * @param std::string sName nom du personnage
			 */
			void setName(const std::string sName);

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
			AfroDS::Coords getPos() const;

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
			void setPosXY(const int x, const int y);

			/**
			 * Renvoie la vitesse de déplacement du personnage
			 */
			int getMoveSpeed() const;

		private:
			/** Nom du personnage */
			std::string m_sName;

			/** Position */
			AfroDS::Coords m_position;

			/** Vitesse de déplacement */
			int m_move_speed;
	};

}

#endif

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "types.h"
#include <string>

namespace AfroDS {

	/**
	 * Repr�sente un personnage
	 */
	class Character {
		public:
			/**
			 * Constructeur par d�faut
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
			 * D�finit le nom du personnage
			 * @param std::string sName nom du personnage
			 */
			void setName(const std::string sName);

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
			AfroDS::Coords getPos() const;

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
			void setPosXY(const int x, const int y);

			/**
			 * Renvoie la vitesse de d�placement du personnage
			 */
			int getMoveSpeed() const;

		private:
			/** Nom du personnage */
			std::string m_sName;

			/** Position */
			AfroDS::Coords m_position;

			/** Vitesse de d�placement */
			int m_move_speed;
	};

}

#endif

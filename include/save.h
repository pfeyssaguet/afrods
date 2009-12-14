#ifndef __SAVE_H__
#define __SAVE_H__

#include "character.h"
#include <vector>

namespace AfroDS {

	/**
	 * Permet d'acc�der aux donn�es sauvegard�es
	 */
	class Save {
		public:
			/**
			 * Constructeur par d�faut
			 */
			Save();

			/**
			 * Charge les personnages depuis la sauvegarde
			 */
			void loadCharacters();

			/**
			 * Sauvegarde les personnages
			 */
			void saveCharacters();

			/**
			 * Renvoie le nombre de personnages de la sauvegarde
			 * @return int nombre de personnages
			 */
			int getNbCharacters();

			/**
			 * Cr�e un nouveau personnage
			 * @param Character newchar personnage � cr�er
			 */
			void addCharacter(Character newchar);

			/**
			 * R�cup�re le personnage n� N
			 * @param int iNumPerso num�ro du personnage
			 * @return Character personnage
			 */
			AfroDS::Character getCharacter(int iNumPerso);

		private:
			/** liste des personnages sauvegard�s */
			std::vector<AfroDS::Character> m_characters;
	};

}

#endif

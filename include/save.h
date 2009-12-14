#ifndef __SAVE_H__
#define __SAVE_H__

#include "character.h"
#include <vector>

namespace AfroDS {

	/**
	 * Permet d'accéder aux données sauvegardées
	 */
	class Save {
		public:
			/**
			 * Constructeur par défaut
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
			 * Crée un nouveau personnage
			 * @param Character newchar personnage à créer
			 */
			void addCharacter(Character newchar);

			/**
			 * Récupère le personnage n° N
			 * @param int iNumPerso numéro du personnage
			 * @return Character personnage
			 */
			AfroDS::Character getCharacter(int iNumPerso);

		private:
			/** liste des personnages sauvegardés */
			std::vector<AfroDS::Character> m_characters;
	};

}

#endif

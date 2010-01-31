#ifndef __SAVE_H__
#define __SAVE_H__

#include "characterplayer.h"
#include <vector>

// nom du fichier de sauvegarde
#define AFRODS_SAVE_FILENAME "/AfroDS.dat"

namespace AfroDS {

	/**
	 * Permet d'accéder aux données sauvegardées
	 */
	class Save {
		public:
			/**
			 * Méthode d'accès au singleton
			 */
			static Save * getInstance();

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
			void addCharacter(CharacterPlayer * newchar);

			/**
			 * Récupère le personnage n° N
			 * @param int iNumPerso numéro du personnage
			 * @return Character personnage
			 */
			CharacterPlayer * getCharacter(int iNumPerso);

			/**
			 * Crée un perso de test pour utiliser directement en jeu
			 */
			CharacterPlayer * getDemoCharacter();

			/**
			 * Crée une liste de persos de test pour utiliser dans le menu
			 */
			void createDemoCharacters();
		private:
			/**
			 * Constructeur par défaut, privé car singleton
			 */
			Save();

			/** liste des personnages sauvegardés */
			std::vector<CharacterPlayer *> m_characters;

			static Save * m_Instance;
	};

}

#endif

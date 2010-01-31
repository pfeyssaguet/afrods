#ifndef __SAVE_H__
#define __SAVE_H__

#include "characterplayer.h"
#include <vector>

// nom du fichier de sauvegarde
#define AFRODS_SAVE_FILENAME "/AfroDS.dat"

namespace AfroDS {

	/**
	 * Permet d'acc�der aux donn�es sauvegard�es
	 */
	class Save {
		public:
			/**
			 * M�thode d'acc�s au singleton
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
			 * Cr�e un nouveau personnage
			 * @param Character newchar personnage � cr�er
			 */
			void addCharacter(CharacterPlayer * newchar);

			/**
			 * R�cup�re le personnage n� N
			 * @param int iNumPerso num�ro du personnage
			 * @return Character personnage
			 */
			CharacterPlayer * getCharacter(int iNumPerso);

			/**
			 * Cr�e un perso de test pour utiliser directement en jeu
			 */
			CharacterPlayer * getDemoCharacter();

			/**
			 * Cr�e une liste de persos de test pour utiliser dans le menu
			 */
			void createDemoCharacters();
		private:
			/**
			 * Constructeur par d�faut, priv� car singleton
			 */
			Save();

			/** liste des personnages sauvegard�s */
			std::vector<CharacterPlayer *> m_characters;

			static Save * m_Instance;
	};

}

#endif

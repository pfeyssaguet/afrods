#ifndef __SAVE_H__
#define __SAVE_H__

#include "creatureplayer.h"
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
			void loadCreatures();

			/**
			 * Sauvegarde les personnages
			 */
			void saveCreatures();

			/**
			 * Renvoie le nombre de personnages de la sauvegarde
			 * @return int nombre de personnages
			 */
			int getNbCreatures();

			/**
			 * Crée un nouveau personnage
			 * @param Creature newchar personnage à créer
			 */
			void addCreature(CreaturePlayer * newchar);

			/**
			 * Récupère le personnage n° N
			 * @param int iNumPerso numéro du personnage
			 * @return Creature personnage
			 */
			CreaturePlayer * getCreature(int iNumPerso);

			/**
			 * Crée un perso de test pour utiliser directement en jeu
			 */
			CreaturePlayer * getDemoCreature();

			/**
			 * Crée une liste de persos de test pour utiliser dans le menu
			 */
			void createDemoCreatures();
		private:
			/**
			 * Constructeur par défaut, privé car singleton
			 */
			Save();

			/** liste des personnages sauvegardés */
			std::vector<CreaturePlayer *> m_characters;

			static Save * m_Instance;
	};

}

#endif

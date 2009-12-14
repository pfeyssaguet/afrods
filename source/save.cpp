#include "save.h"
#include "constants.h"
#include <PA9.h>
#include <fat.h>

using namespace AfroDS;

/**
 * Constructeur par défaut
 */
Save::Save() {
	// Initialisation du filesystem (c'est pas gagné)
	PA_OutputText(ECRAN_HAUT, 1, 5, "Init. FAT...");
	if (!fatInitDefault()) {
		// FAT ne fonctionne pas, on est mal...
		PA_OutputText(ECRAN_HAUT, 27, 5, "[KO]");
		PA_OutputText(ECRAN_HAUT, 4, 21, "FAT system is down");
	} else {
		// FAT fonctionne
		PA_OutputText(ECRAN_HAUT, 27, 5, "[OK]");
	}
	// Chargement des persos depuis la sauvegarde
	PA_OutputText(ECRAN_HAUT, 1, 6, "Init. personnages...");
	loadCharacters();
}

/**
 * Renvoie le nombre de personnages de la sauvegarde
 * @return int nombre de personnages
 */
int Save::getNbCharacters() {
	return m_characters.size();
}

/**
 * Crée un nouveau personnage
 * @param Character newchar personnage à créer
 */
void Save::addCharacter(Character newchar) {
	m_characters.push_back(newchar);
}

/**
 * Récupère le personnage n° N
 * @param int iNumPerso numéro du personnage
 * @return Character personnage
 */
Character Save::getCharacter(int iNumPerso) {
	return m_characters.at(iNumPerso);
}

/**
 * Charge les personnages depuis la sauvegarde
 */
void Save::loadCharacters() {

	FILE* file = fopen(AFRODS_SAVE_FILENAME, "r");

	if (file) {
		//on cherche la taille du fichier, cela sert apres pour le buffer
		u32 size;
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);//on retourne au debut du fichier

		// on alloue suffisamment de mémoire et on stocke l'adresse dans buffer
		char * buffer;
		buffer = (char*) malloc(sizeof(char) * size);
		fread(buffer, 1, size, file);
		PA_OutputText(ECRAN_HAUT, 4, 8, "content: [%s]", buffer);
		PA_OutputText(ECRAN_HAUT, 4, 9, "size: %d bytes", size);
		free(buffer);
		fclose(file);//on ferme le fichier
	} else {
		// on crée un nouveau fichier
		file = fopen(AFRODS_SAVE_FILENAME, "wb");
		fclose(file);//on ferme le fichier
	}
	// pour l'instant j'ajoute quelques persos bidons pour test
	addCharacter(Character("deuspi"));
	addCharacter(Character("yoda"));
	addCharacter(Character("nob"));
	addCharacter(Character("deuspi2"));
}

void Save::saveCharacters() {
	/*
	Character charac;
	for(std::vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it)
		charac = (Character)it;
		std::string sPath = "/" + charac.getName() + ".dat";
		if (m_UseEFS)
			sPath = "efs:" + sPath;
		FILE * file = fopen(sPath, "wb");
		fwrite((void *)charac, 1, sizeof(charac), file);
		fclose(file);
	}
	*/

}


#include "save.h"
#include <fat.h>

using namespace std;

Save::Save() {
	// Initialisation du système de filesystem (c'est pas gagné)
	//AF_SaveInitFAT();
	//AF_SaveTestCardMe();

	// Chargement des persos depuis la sauvegarde
	loadPersos();
}
/*
AF_SavePerso * Save::getPersos() {
	//return m_persos;
	return m_characters;
}
*/

void Save::loadPersos() {
	// pour l'instant j'ajoute quelques persos bidons pour test
	// TODO Save : il faut charger les persos depuis une sauvegarde !
	//AF_SavePersoAdd("deuspi");
	//AF_SavePersoAdd("yoda");
//	AF_SavePersoAdd("nob");
	m_characters.push_back(Character("deuspi"));
	m_characters.push_back(Character("yoda"));
	m_characters.push_back(Character("nob"));

/*
	FILE* imgFile = fopen(AFRODS_SAVE_FILENAME, "rb");

	if (imgFile) {
		//on cherche la taille du fichier, cela sert apres pour le buffer
		u32 imgSize;
		fseek(imgFile, 0, SEEK_END);
		imgSize = ftell(imgFile);
		rewind(imgFile);//on retourne au debut du fichier

		// on alloue suffisamment de mémoire et on stocke l'adresse dans buffer
		char * buffer;
		buffer = (char*) malloc(sizeof(char) * imgSize);
		fread(buffer, 1, imgSize, imgFile);

		fclose(imgFile);//on ferme le fichier
	} else {
		// on crée un nouveau fichier
		imgFile = fopen(AFRODS_SAVE_FILENAME, "wb");

	}
*/
}

int Save::getNbCharacters() {
	return m_characters.size();
}

vector<Character> Save::getCharacters() {
	return m_characters;
}

/*
int Save::AF_SavePersoCount() {
	AF_SavePerso * iter = m_persos;
	int i = 0;

	while (iter != NULL)
	{
		iter = iter->next;
		i++;
	}

	return i;
}

void Save::AF_SavePersoAdd(char * sNom) {
	// on crée un nouvel élément
	AF_SavePerso* nouveau = malloc(sizeof(AF_SavePerso));
	nouveau->sName = malloc((strlen(sNom) + 1) * sizeof(char));
	strcpy(nouveau->sName, sNom);

	// c'est parti vive les listes chaînées :p
	nouveau->prev = NULL;
	nouveau->next = NULL;

	// si la liste était vide c'est facile...
	if (m_persos == NULL) {
		m_persos = nouveau;
		return;
	}

	// recherche du dernier élément
	AF_SavePerso * last = m_persos;
	while (last->next != NULL)
		last = last->next;

	// on rajoute directement le nouvel élément à last
	last->next = nouveau;
	nouveau->prev = last;
}

void Save::AF_SavePersoClear()
{
	AF_SavePerso * tmp;
	AF_SavePerso * tmp2;

	while (m_persos != NULL)
	{
		tmp = m_persos->next;
		tmp2 = m_persos;

		// on nettoie la chaîne du nom du perso
		free(tmp2->sName);
		tmp2->sName = NULL;

		// on nettoie l'élément en lui-même
		free(tmp2);
		tmp2 = NULL;

		m_persos = tmp;
	}
}
*/
/*
void AF_SaveInitFAT() {
	 PA_InitText(ECRAN_HAUT, 2);
	 // on initialise la libfat
	 PA_OutputText(ECRAN_HAUT, 1, 3, "Init. FAT...");

	 if (!fatInitDefault())
	 {
		 PA_OutputText(ECRAN_HAUT, 27, 3, "[KO]");
		 PA_OutputText(ECRAN_HAUT, 4, 19, "FAT system is down");
		 //return false;
	 }
	 else
	 {
		 PA_OutputText(ECRAN_HAUT, 27, 3, "[OK]");
	 }
}
*/

/*
void AF_SaveTestCardMe() {
	 char text[10] = "Salut";
	 u8 data[20];

	 PA_InitText(0, 0);

	 PA_Print(0, "Getting card type\n");
	 int type = cardmeGetType();
	 PA_Print(0, "Type found : %d   \n", type);

	 while(1){

		 if(Pad.Newpress.A) {
			 cardmeWriteEeprom(0, (u8*)text, 10, type);
			 PA_Print(0, "SAVED !!      \n");
		 }
		 if(Pad.Newpress.B) {
			 cardmeReadEeprom(0, data, 10, type);
			 PA_Print(0, "LOADED => %s     \n", (char*)data);
		 }

		 PA_WaitForVBL();
	 }

}
 */

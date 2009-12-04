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

void Save::loadPersos() {
	// pour l'instant j'ajoute quelques persos bidons pour test
	// TODO Save : il faut charger les persos depuis une sauvegarde !
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

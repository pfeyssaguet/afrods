#include "save.h"
#include <fat.h>

void AF_SaveInit() {
	// Initialisation de la liste des persos � NULL
	G_Env.Save.persos = NULL;

	// Initialisation du syst�me de filesystem (c'est pas gagn�)
	//AF_SaveInitFAT();
	//AF_SaveTestCardMe();

	// Chargement des persos depuis la sauvegarde
	AF_SaveLoadPersos();
}

void AF_SaveLoadPersos() {
	// pour l'instant j'ajoute quelques persos bidons pour test
	// TODO Save : il faut charger les persos depuis une sauvegarde !
	AF_SavePersoAdd("deuspi");
	AF_SavePersoAdd("yoda");
//	AF_SavePersoAdd("nob");
/*
	FILE* imgFile = fopen(AFRODS_SAVE_FILENAME, "rb");

	if (imgFile) {
		//on cherche la taille du fichier, cela sert apres pour le buffer
		u32 imgSize;
		fseek(imgFile, 0, SEEK_END);
		imgSize = ftell(imgFile);
		rewind(imgFile);//on retourne au debut du fichier

		// on alloue suffisamment de m�moire et on stocke l'adresse dans buffer
		char * buffer;
		buffer = (char*) malloc(sizeof(char) * imgSize);
		fread(buffer, 1, imgSize, imgFile);

		fclose(imgFile);//on ferme le fichier
	} else {
		// on cr�e un nouveau fichier
		imgFile = fopen(AFRODS_SAVE_FILENAME, "wb");

	}
*/
}

int AF_SavePersoCount() {
	AF_SavePerso * iter = G_Env.Save.persos;
	int i = 0;

	while (iter != NULL)
	{
		iter = iter->next;
		i++;
	}

	return i;
}

void AF_SavePersoAdd(char * sNom) {
	// on cr�e un nouvel �l�ment
	AF_SavePerso* nouveau = malloc(sizeof(AF_SavePerso));
	nouveau->sName = malloc((strlen(sNom) + 1) * sizeof(char));
	strcpy(nouveau->sName, sNom);

	// c'est parti vive les listes cha�n�es :p
	nouveau->prev = NULL;
	nouveau->next = NULL;

	// si la liste �tait vide c'est facile...
	if (G_Env.Save.persos == NULL) {
		G_Env.Save.persos = nouveau;
		return;
	}

	// recherche du dernier �l�ment
	AF_SavePerso * last = G_Env.Save.persos;
	while (last->next != NULL)
		last = last->next;

	// on rajoute directement le nouvel �l�ment � last
	last->next = nouveau;
	nouveau->prev = last;
}

void AF_SavePersoClear()
{
	AF_SavePerso * tmp;
	AF_SavePerso * tmp2;

	while (G_Env.Save.persos != NULL)
	{
		tmp = G_Env.Save.persos->next;
		tmp2 = G_Env.Save.persos;

		// on nettoie la cha�ne du nom du perso
		free(tmp2->sName);
		tmp2->sName = NULL;

		// on nettoie l'�l�ment en lui-m�me
		free(tmp2);
		tmp2 = NULL;

		G_Env.Save.persos = tmp;
	}
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

#include "main.h"

int main(int argc, char ** argv) {
	// on initialise la PA_Lib
	PA_Init();
	PA_InitVBL();

	AF_MainInit();

	// Boucle principale
	while (1) {
		// on lance les événements
		AF_MainEvents();

		// on attend la prochaine frame
		PA_WaitForVBL();
	}

	return 0;
}

/**
 * Initialisation du module principal
 */
void AF_MainInit()
{
	// Initialisation du background pour le texte
	PA_InitText(ECRAN_HAUT, AFRODS_LAYER_TEXT);
	PA_InitText(ECRAN_BAS, AFRODS_LAYER_TEXT);

	// Initialisation du module splash
	G_Env.currentModule = new Splash();

	// Initialisation de la sauvegarde
	G_Env.save = new Save();
}

void AF_MainEvents()
{
	// d'abord on traite les événements du module en cours
	G_Env.currentModule->moduleEvents();

	if (G_Env.currentModule->isStopped()) {
		// on appelle le destructeur
		delete G_Env.currentModule;

		// on charge le prochain module
		switch (G_Env.NextModule)
		{
			case AFRODS_MODULE_NEWCHAR:
				G_Env.currentModule = new NewChar();
				break;

			case AFRODS_MODULE_MENU:
				G_Env.currentModule = new Menu();
				break;

			case AFRODS_MODULE_GAME:
				G_Env.currentModule = new Game();
				break;

			case AFRODS_MODULE_SPLASH:
				G_Env.currentModule = new Splash();
				break;
		}
	}

}

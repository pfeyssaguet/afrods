#include "main.h"
#include "splash.h"
#include "menu.h"
#include "game.h"
#include "newchar.h"
#include "save.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

int main(int argc, char ** argv) {
	// on initialise la PA_Lib
	PA_Init();
	PA_InitVBL();

	// FIXME Main : virer cette vieille feinte ! on attend un peu pour éviter le bug du stylus déjà pressé
	PA_WaitForVBL();
	PA_WaitForVBL();
	PA_WaitForVBL();
	PA_WaitForVBL();
	PA_WaitForVBL();
	PA_WaitForVBL();

	// Initialisations principales
	AF_MainInit();

	// Boucle principale
	while (true) {
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
void AF_MainInit() {
	// Initialisation du module splash
	G_Env.currentModule = new Splash();
}

void AF_MainEvents() {
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

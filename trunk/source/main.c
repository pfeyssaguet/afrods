#include "main.h"

int main(int argc, char ** argv)
{
	// on initialise la PA_Lib
	PA_Init();
	PA_InitVBL();
	PA_InitText(ECRAN_BAS, 2);

	AF_MainInit();

	// Boucle principale
	while (1)
	{
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
	// on charge la palette du menu
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_MENU, (void*)palMenu_Pal);

	// on charge la palette du personnage
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_PERSO, (void*)palPerso_Pal);

	// Initialisation du module splash
	AF_SplashInit();
	
	// Initialisation du module de sauvegarde
	AF_SaveInit();
}

void AF_MainEvents()
{
	switch (G_Env.Module)
	{
		case AFRODS_MODULE_SPLASH:
			AF_SplashEvents();
			break;

		case AFRODS_MODULE_MENU:
			AF_MenuEvents();
			break;
		
		case AFRODS_MODULE_GAME:
			// on traite les événements du jeu
			AF_GameEvents();
			break;
	}


	// on vérifie le flag ModuleStop :
	// s'il est passé à TRUE, ça veut dire qu'on doit changer de module
	if (G_Env.ModuleStop) {

		switch (G_Env.Module)
		{
			case AFRODS_MODULE_SPLASH:
				AF_SplashClean();
				AF_MenuInit();
				break;

			case AFRODS_MODULE_MENU:
				AF_MenuClean();
				AF_GameInit();
				break;

			case AFRODS_MODULE_GAME:
				// on retourne au splash screen
				AF_GameClean();
				AF_SplashInit();
				break;
		}
	}

}

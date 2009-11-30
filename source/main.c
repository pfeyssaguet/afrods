#include "main.h"

int main(int argc, char ** argv)
{
	// on initialise la PA_Lib
	PA_Init();
	PA_InitVBL();
	
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

void AF_MainInit()
{
	// on charge la palette du menu
	PA_LoadSpritePal(ECRAN_BAS, // Screen
				AFRODS_PAL_MENU, // Palette number
				(void*)palMenu_Pal);	// Palette name

	// on charge la palette du personnage
	PA_LoadSpritePal(ECRAN_BAS, // Screen
				AFRODS_PAL_PERSO, // Palette number
				(void*)palPerso_Pal);	// Palette name
				
	// Initialisation du module splash
	AF_SplashInit();
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
}

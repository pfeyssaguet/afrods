#include "main.h"

int main(int argc, char ** argv)
{
	// on initialise la PA_Lib
	PA_Init();
	PA_InitVBL();
	
	// Initialisation du module game
	AF_MenuInit();
	
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

void AF_MainEvents()
{
	switch (G_Env.Module)
	{
		case AFRODS_MODULE_MENU:
			AF_MenuEvents();
			break;
		
		case AFRODS_MODULE_GAME:
			// on traite les événements du jeu
			AF_GameEvents();
			break;
	}
}

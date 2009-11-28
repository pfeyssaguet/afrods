#include "menu.h"

void AF_MenuInit()
{
	// On indique qu'on se trouve dans le menu
	G_Env.Module = AFRODS_MODULE_MENU;

	// Load Backgrounds with their palettes !

	PA_EasyBgLoad(ECRAN_BAS, // screen
					AFRODS_LAYER_BG, // background number (0-3)
					bg0); // Background name, used by PAGfx...

	PA_EasyBgLoad(ECRAN_HAUT, AFRODS_LAYER_BG, bg0);	
}

void AF_MenuEvents()
{
	// en cas d'appui sur A, on lance le jeu
	if (Pad.Newpress.A)
		AF_GameInit();
}

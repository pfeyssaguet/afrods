#include "splash.h"

void AF_SplashInit()
{
	// On indique qu'on se trouve dans le splash
	G_Env.Module = AFRODS_MODULE_SPLASH;

	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	
	PA_EasyBgLoad(ECRAN_BAS, // screen
					AFRODS_LAYER_BG, // background number (0-3)
					bg_splash_bottom); // Background name, used by PAGfx...

	PA_EasyBgLoad(ECRAN_HAUT, AFRODS_LAYER_BG, bg_splash_top);	
}

void AF_SplashEvents()
{
	// en cas d'appui sur Start ou A, on lance le menu
	if (Pad.Newpress.Start || Pad.Newpress.A)
		AF_MenuInit();
}

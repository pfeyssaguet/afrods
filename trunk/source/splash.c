#include "splash.h"

void AF_SplashInit()
{
	// On indique qu'on se trouve dans le splash
	G_Env.Module = AFRODS_MODULE_SPLASH;
	G_Env.ModuleStop = FALSE;

	// on vide les backgrounds
	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	
	// on charge les 2 backgrounds du module splash
	PA_EasyBgLoad(ECRAN_BAS, AFRODS_LAYER_BG, bg_splash_bottom);
	PA_EasyBgLoad(ECRAN_HAUT, AFRODS_LAYER_BG, bg_splash_top);	
}

void AF_SplashEvents() {
	// en cas d'appui sur Start ou A, on sort du splash screen
	if (Pad.Newpress.Start || Pad.Newpress.A) {
		// on indique qu'on est plus sur le splash
		G_Env.ModuleStop = TRUE;
	}
}

void AF_SplashClean() {
	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
}

#include "splash.h"

Splash::Splash()
{
	// on charge les 2 backgrounds du module splash
	PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_splash_bottom);
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_BG, bg_splash_top);
}

void Splash::moduleEvents() {
	// en cas d'appui sur Start ou A, on sort du splash screen
	if (Pad.Newpress.Start || Pad.Newpress.A) {
		// on indique qu'on veut sortir
		m_bIsStopped = true;
		// pour aller dans le module Menu
		G_Env.NextModule = AFRODS_MODULE_MENU;
	}
}

Splash::~Splash() {
	// on efface les backgrounds
	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
}

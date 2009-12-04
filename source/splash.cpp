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
		// on indique qu'on est plus sur le splash
		m_bIsStopped = true;
	}
}

Splash::~Splash() {
	// on efface les backgrounds
	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
}

#include "splash.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

using namespace AfroDS;

Splash::Splash() {
	// on charge les 2 backgrounds du module splash
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_splash_loading_top);
	PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_splash_bottom);
	PA_InitText(ECRAN_HAUT, AFRODS_LAYER_TOP_TEXT);

	PA_OutputText(ECRAN_HAUT, 1, 1, "AfroDS v%s", AFRODS_VERSION);
	PA_OutputText(ECRAN_HAUT, 1, 3, "Init. sauvegarde...");

	// Initialisation de la sauvegarde
	G_Env.save = new Save();

	// On charge le dernier background
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_splash_top);
}

void Splash::moduleEvents() {
	// si on appuie au stylet...

	if (Stylus.Newpress) {
		PA_WaitFor(Stylus.Released);
		// on indique qu'on veut sortir
		m_bIsStopped = true;
		// pour aller dans le module Menu
		G_Env.NextModule = AFRODS_MODULE_MENU;
		return;
	}


	// en cas d'appui sur Start ou A, on sort du splash screen
	if (Pad.Newpress.Start || Pad.Newpress.A) {
		// on indique qu'on veut sortir
		m_bIsStopped = true;
		// pour aller dans le module Menu
		G_Env.NextModule = AFRODS_MODULE_MENU;
	}
}

Splash::~Splash() {
	PA_ResetBgSys();
	PA_ResetSpriteSys();
}

// custom includes
#include "modulesplash.h"
#include "context.h"

// standard includes
#include <nds.h>


using namespace AfroDS;

/**
 * Initialise le module splash avec ses backgrounds
 */
ModuleSplash::ModuleSplash(Context * context) : Module(context), m_bgTop(NULL), m_bgBottom(NULL) {
	// chargement du background du haut
	m_bgTop = new Background(SCREEN_MAIN, AFRODS_LAYER_SPLASH_TOP_BG, BG_SPLASH_TOP);

	// chargement du background du bas
	m_bgBottom = new Background(SCREEN_SUB, AFRODS_LAYER_SPLASH_TOP_BOTTOM, BG_SPLASH_BOTTOM);
}

/**
 * Supprime les backgrounds
 */
ModuleSplash::~ModuleSplash() {
	// suppression des backgrounds en haut et en bas
	if (m_bgTop != NULL)
		delete m_bgTop;

	if (m_bgBottom != NULL)
		delete m_bgBottom;
}

/**
 * Gestion des �v�nements du module
 */
void ModuleSplash::moduleEvents() {
	// si on touche l'�cran, on se dirige le module Menu
	if (keysDown()) {
		if (keysDown() & KEY_TOUCH || keysDown() & KEY_START || keysDown() & KEY_A) {

			while(keysHeld() & KEY_TOUCH || keysHeld() & KEY_START || keysHeld() & KEY_A) {
				swiWaitForVBlank();
				scanKeys();
			}

			//swiIntrWait(1, IRQ_KEYS);

			// on indique qu'on veut sortir pour aller dans le module Menu
			m_context->switchModule(MODULE_MENU, false);
			return;
		}
	}
}


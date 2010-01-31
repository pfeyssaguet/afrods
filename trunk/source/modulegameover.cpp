#include "modulegameover.h"
#include "constants.h"
#include "context.h"

#include <nds.h>

using namespace AfroDS;

ModuleGameover::ModuleGameover(Context * context) : Module(context) {
	m_bgTop = new Background(SCREEN_MAIN, 3, BG_SPLASH_TOP);
	m_bgBottom = new Background(SCREEN_SUB, 3, BG_GAMEOVER_BOTTOM);
}

ModuleGameover::~ModuleGameover() {
	delete m_bgTop;
	delete m_bgBottom;
}

void ModuleGameover::moduleEvents() {

	// si on fait A, on quitte le GameOver pour revenir au Game qui est en pause
	if (keysDown() & KEY_A) {
		// on veut revenir au jeu
		// on sort juste du module GameOver

		// on remet 1 point de vie au perso
		m_context->getActiveChar()->setCurrentHp(1);

		m_context->resumePausedModule();
	}

	// si on fait B, on doit retourner au splash
	if (keysDown() & KEY_B) {
		// on vide le module pausé
		m_context->setPausedModule(NULL);
		m_context->switchModule(MODULE_SPLASH, false);
	}

}


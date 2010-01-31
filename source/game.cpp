// custom includes
#include "game.h"
#include "constants.h"
#include "save.h"

// standard includes
#include <nds.h>
#include <time.h>

using namespace AfroDS;

Game * Game::m_Instance = NULL;

Game::Game() {
	m_context = new Context();
}

Game * Game::getInstance() {
	if (m_Instance == NULL) {
		m_Instance = new Game();
	}
	return m_Instance;
}

void Game::init() {
	// mise en place de l'ExceptionHandler pour le Guru Meditation
	defaultExceptionHandler();

	vramSetMainBanks(VRAM_A_MAIN_SPRITE_0x06400000,
					 VRAM_B_MAIN_BG_0x06000000,
					 VRAM_C_SUB_BG_0x06200000,
					 VRAM_D_SUB_SPRITE);

	//vramSetBankG(VRAM_G_MAIN_BG_0x06004000);

	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);

	// init modes vid�os
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	// init des consoles
	GraphicsEngine::getInstance()->initConsoles();

	// activation des palettes �tendues pour les sprites
	oamInit(&oamMain, SpriteMapping_1D_128, true);
	oamInit(&oamSub, SpriteMapping_1D_128, true);

	// activation du syst�me de sprite sur les 2 �crans
	oamEnable(&oamMain);
	oamEnable(&oamSub);

	// initialisation du syst�me de random
	srand(time(NULL));

	// Temporaire : on utilise un perso de test pour le cas o� on lance le module Game directement
	m_context->setActiveChar(Save::getInstance()->getDemoCharacter());

	// On lance le module splash
	//m_context->runModule(MODULE_SPLASH);
	m_context->runModule(MODULE_GAME);

}

void Game::run() {
	// on capture les �v�nements d'entr�e...
	scanKeys();

	// on traite les �v�nements du module en cours
	//ModuleFactory::moduleEvents();
	m_context->moduleEvents();

	// on attend la fin de la frame
	swiWaitForVBlank();

	// mise � jour des backgrounds
	bgUpdate();

	// mise � jour des sprites des 2 �crans
	GraphicsEngine::updateOam();
}


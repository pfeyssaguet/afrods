#include "modulefactory.h"

#include "modulesplash.h"
#include "modulemenu.h"
#include "modulegame.h"
#include "modulebattle.h"
#include "modulegameover.h"

using namespace AfroDS;

Module * ModuleFactory::loadModule(Context * context, const ModuleType type) {
	// {MODULE_SPLASH = 1, MODULE_MENU = 2, MODULE_NEWCHAR = 3, MODULE_GAME = 4, MODULE_BATTLE = 5}
	switch (type) {
		case MODULE_SPLASH:
			return new ModuleSplash(context);
			break;
		case MODULE_MENU:
			return new ModuleMenu(context);
			break;
		case MODULE_NEWCHAR:
			// TODO implémenter le module NEWCHAR !
			// temporaire : on redirige le newchar sur le splash (bcp de choses à faire avant de refaire le newchar)
			return new ModuleSplash(context);
			break;
		case MODULE_GAME:
			return new ModuleGame(context);
			break;
		case MODULE_BATTLE:
			return new ModuleBattle(context);
			break;
		case MODULE_GAMEOVER:
			return new ModuleGameover(context);
			break;
		default:
		case MODULE_NONE:
			break;
	}

	return NULL;
}

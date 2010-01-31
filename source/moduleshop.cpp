#include "moduleshop.h"
#include "context.h"

using namespace AfroDS;

ModuleShop::ModuleShop(Context * context) : Module(context) {
	m_bgBottom = new Background(SCREEN_SUB, 3, BG_SHOP_BOTTOM);
}

ModuleShop::~ModuleShop() {
	delete m_bgBottom;
}

void ModuleShop::moduleEvents() {
	// si on appuie sur B on sort
	if (keysDown() && KEY_B) {
		// on va revenir sur le module Game qui est en pause
		m_context->resumePausedModule();
	}
}

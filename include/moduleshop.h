#ifndef __MODULESHOP_H_
#define __MODULESHOP_H_

#include "module.h"
#include "background.h"
#include "sprite.h"

namespace AfroDS {
	class ModuleShop : public Module {
		public:
			ModuleShop(Context * context);
			~ModuleShop();
			void moduleEvents();
		private:
			Background * m_bgBottom;
			Sprite * m_spriteFinger;
	};
}

#endif

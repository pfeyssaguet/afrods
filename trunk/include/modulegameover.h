#ifndef __MODULEGAMEOVER_H_
#define __MODULEGAMEOVER_H_

#include "module.h"
#include "background.h"

namespace AfroDS {
	class ModuleGameover : public Module {
		public:
			ModuleGameover(Context * context);
			virtual ~ModuleGameover();
			void moduleEvents();

		private:
			Background * m_bgTop;
			Background * m_bgBottom;
	};
}

#endif

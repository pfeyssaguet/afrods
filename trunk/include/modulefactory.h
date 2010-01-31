#ifndef __MODULEFACTORY_H_
#define __MODULEFACTORY_H_

#include "module.h"

namespace AfroDS {
	class ModuleFactory {
		public:
			static Module * loadModule(Context * context, const ModuleType type);
	};
}

#endif

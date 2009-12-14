#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "module.h"

namespace AfroDS {

	class Splash : public AfroDS::Module {
		public:
			Splash();
			~Splash();
			void moduleEvents();
	};

}

#endif

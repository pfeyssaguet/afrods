#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "module.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

class Splash : public Module {
	public:
		Splash();
		~Splash();
		void moduleEvents();
};

#endif

#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "module.h"
#include "background.h"

namespace AfroDS {

	/**
	 * Classe Module Splash
	 */
	class ModuleSplash : public Module {
		public:
			/**
			 * Initialise le module splash avec ses backgrounds
			 */
			ModuleSplash(Context * context);

			/**
			 * Supprime les backgrounds
			 */
			virtual ~ModuleSplash();

			/**
			 * Gestion des événements du module
			 */
			void moduleEvents();
		private:
			/** Le background du haut */
			Background * m_bgTop;

			/** Le background du bas */
			Background * m_bgBottom;
	};

}

#endif

#ifndef __MODULE_H__
#define __MODULE_H__

#include "constants.h"

namespace AfroDS {

	// constantes pour identifier les modules
	enum ModuleType {MODULE_NONE, MODULE_SPLASH, MODULE_MENU, MODULE_NEWCHAR, MODULE_GAME, MODULE_BATTLE, MODULE_GAMEOVER};

	class Context;

	class Module {
		public:
			/** Constructeur et Destructeur */
			Module(Context * context);

			virtual ~Module() {};

			/** Méthode de mise à jour du module */
			virtual void moduleEvents();

			/** Méthode pour mettre un module en pause */
			virtual void modulePause();

			/** Méthode pour sortir de pause */
			virtual void moduleResume();

			Context * getContext() const;

		protected:
			Context * m_context;
	};

}
#endif

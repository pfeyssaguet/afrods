#ifndef __CONTEXT_H_
#define __CONTEXT_H_

#include "module.h"
#include "modulefactory.h"
#include "graphicsengine.h"
#include "creatureplayer.h"


namespace AfroDS {
	class Context {
		public:
			Context();
			GraphicsBackground getBattleBackground() const;
			CreaturePlayer * getActiveChar() const;
			void setBattleBackground(const GraphicsBackground background);
			void setActiveChar(CreaturePlayer * player);
			void setPausedModule(Module * module);
			void runModule(const ModuleType type);
			void moduleEvents();
			void switchModule(const ModuleType type, const bool pause);
			void resumePausedModule();
		private:
			/** Le personnage sélectionné */
			CreaturePlayer * m_ActiveChar;

			GraphicsBackground m_BattleBackground;

			Module * m_CurrentModule;
			Module * m_PausedModule;

	};
}

#endif

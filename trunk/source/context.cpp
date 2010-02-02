#include "context.h"

using namespace AfroDS;

Context::Context() : m_ActiveChar(NULL), m_BattleBackground(BG_BATTLE_TOP_FOREST), m_CurrentModule(NULL), m_PausedModule(NULL) {

}

GraphicsBackground Context::getBattleBackground() const {
	return m_BattleBackground;
}

CharacterPlayer * Context::getActiveChar() const {
	return m_ActiveChar;
}

void Context::setBattleBackground(const GraphicsBackground background) {
	m_BattleBackground = background;
}

void Context::setActiveChar(CharacterPlayer * player) {
	if (m_ActiveChar != NULL) {
		delete m_ActiveChar;
	}
	m_ActiveChar = player;
}

void Context::setPausedModule(Module * module) {
	// TODO faire une liste plutôt qu'un seul module en pause, pour les empiler
	if (m_PausedModule != NULL) {
		delete m_PausedModule;
	}
	m_PausedModule = module;
}

void Context::runModule(const ModuleType type) {
	if (m_CurrentModule != NULL) {
		delete m_CurrentModule;
	}
	m_CurrentModule = ModuleFactory::loadModule(this, type);
}

void Context::moduleEvents() {
	m_CurrentModule->moduleEvents();
}

void Context::switchModule(const ModuleType type, const bool pause) {
	// si on veut mettre le module en pause
	if (pause) {
		// on copie le module courant dans le module pausé
		m_PausedModule = m_CurrentModule;

		// on endort le module
		m_PausedModule->modulePause();

		// on vide le pointeur du module courant pour qu'il ne soit pas détruit
		m_CurrentModule = NULL;
	}

	// on charge le prochain module
	runModule(type);
}

void Context::resumePausedModule() {
	if (m_CurrentModule != NULL) {
		delete m_CurrentModule;
		m_CurrentModule = NULL;
	}

	if (m_PausedModule != NULL) {
		m_CurrentModule = m_PausedModule;
		m_PausedModule = NULL;
		m_CurrentModule->moduleResume();
	}
}

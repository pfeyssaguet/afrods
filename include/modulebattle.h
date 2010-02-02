#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "module.h"
#include "background.h"
#include "spritebattle.h"
#include "spritechar.h"
#include "characterplayer.h"
#include "charactermonster.h"

#include <vector>
#include <string>
#include <stdarg.h>

// Les différents sous-menus du menu principal
#define MENU_ATTACK_STR "Attack"
#define MENU_INFO_STR "Info"
#define MENU_MAGIC_STR "Magic"
#define MENU_ITEMS_STR "Items"

namespace AfroDS {
	/** Représente les menus */
	enum MenuType {MENU_DEFAULT, MENU_ATTACK, MENU_INFO, MENU_MAGIC, MENU_ITEMS};

	/**
	 * Permet de gérer les modes du module ModuleBattle :
	 * MODE_BATTLE = combat en cours
	 * MODE_WIN = combat gagné
	 */
	enum BattleMode {MODE_BATTLE, MODE_WIN};

	class ModuleBattle : public Module {
		public:
			ModuleBattle(Context * context);
			virtual ~ModuleBattle();
			void moduleEvents();

		private:
			void initConsoles();
			void doModeBattle();
			void doModeWin();
			void doActionAttack();
			void selectMonster();
			void generateMonsters();
			void createMonster(MonsterType type);
			void showPlayers();
			void showMenu(MenuType menu);
			void addLog(const char * text, ...);
			void winBattle();

			BattleMode m_currentMode;

			std::vector<std::string> m_menuEntries;

			unsigned int m_selectedEntry;

			MenuType m_currentMenu;

			PrintConsole m_consoleLog;
			PrintConsole m_consoleMenu;
			PrintConsole m_consolePlayer;

			std::vector<CharacterMonster *> m_monstersAlive;
			std::vector<CharacterMonster *> m_monstersDead;

			std::vector<Sprite *> m_spriteMonstersAlive;
			std::vector<Sprite *> m_spriteMonstersDead;

			Background * m_bgBottom;
			Background * m_bgTop;

			SpriteBattle * m_spriteChar1;

			Sprite * m_spriteFingerBottom;
			Sprite * m_spriteFingerTop;
	};
}

#endif

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "module.h"
#include "background.h"
#include "spritebattle.h"
#include "spritechar.h"
#include "creatureplayer.h"
#include "creaturemonster.h"

#include <vector>
#include <string>
#include <stdarg.h>

// Les différents sous-menus du menu principal
#define MENU_BATTLE_ATTACK_STR "Attack"
#define MENU_BATTLE_INFO_STR "Info"
#define MENU_BATTLE_MAGIC_STR "Magic"
#define MENU_BATTLE_ITEMS_STR "Items"

namespace AfroDS {
	/** Représente les menus */
	enum MenuBattleType {MENU_BATTLE_DEFAULT, MENU_BATTLE_ATTACK, MENU_BATTLE_INFO, MENU_BATTLE_MAGIC, MENU_BATTLE_ITEMS};

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
			void showMenu(MenuBattleType menu);
			void addLog(const char * text, ...);
			void winBattle();

			BattleMode m_currentMode;

			std::vector<std::string> m_menuEntries;

			unsigned int m_selectedEntry;

			MenuBattleType m_currentMenu;

			PrintConsole m_consoleLog;
			PrintConsole m_consoleMenu;
			PrintConsole m_consolePlayer;

			std::vector<CreatureMonster *> m_monstersAlive;
			std::vector<CreatureMonster *> m_monstersDead;

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

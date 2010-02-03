#include "modulebattle.h"
#include "constants.h"
#include "context.h"

// standard includes
#include <nds.h>
#include <stdio.h>
#include <sstream>
#include "fnt_arialia.h"

using namespace AfroDS;

ModuleBattle::ModuleBattle(Context * context) : Module(context), m_currentMode(MODE_BATTLE), m_selectedEntry(0) {
	// création des 2 backgrounds
	m_bgTop = new Background(SCREEN_MAIN, 3, m_context->getBattleBackground());
	m_bgBottom = new Background(SCREEN_SUB, 3, BG_BATTLE_BOTTOM);

	// initialisation des consoles
	initConsoles();

	// le doigt
	m_spriteFingerBottom = new Sprite(SCREEN_SUB, SPRITE_FINGER);
	m_spriteFingerBottom->setVisible(false);

	m_spriteFingerTop = new Sprite(SCREEN_MAIN, SPRITE_FINGER);
	m_spriteFingerTop->setVisible(false);

	// on affiche les joueurs sur la zone à droite
	showPlayers();

	// création du perso 1
	m_spriteChar1 = new SpriteBattle(SCREEN_MAIN, GraphicsEngine::CharacterClassToGraphicsSprite(m_context->getActiveChar()->getClass(), true));
	m_spriteChar1->setPos(Coords(32, 112));

	generateMonsters();

	showMenu(MENU_BATTLE_DEFAULT);
}

ModuleBattle::~ModuleBattle() {
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");

	delete m_bgBottom;
	delete m_bgTop;

	if (m_spriteChar1 != NULL) {
		delete m_spriteChar1;
	}

	// on vire les monstres
	while (!m_monstersAlive.empty()) {
		delete m_monstersAlive.at(0);
		m_monstersAlive.erase(m_monstersAlive.begin());
	}
	while (!m_monstersDead.empty()) {
		delete m_monstersDead.at(0);
		m_monstersDead.erase(m_monstersDead.begin());
	}

	while (!m_spriteMonstersAlive.empty()) {
		delete m_spriteMonstersAlive.at(0);
		m_spriteMonstersAlive.erase(m_spriteMonstersAlive.begin());
	}
	while (!m_spriteMonstersDead.empty()) {
		delete m_spriteMonstersDead.at(0);
		m_spriteMonstersDead.erase(m_spriteMonstersDead.begin());
	}

	if (m_spriteFingerBottom != NULL) {
		delete m_spriteFingerBottom;
	}

	if (m_spriteFingerTop != NULL) {
		delete m_spriteFingerTop;
	}
}

void ModuleBattle::moduleEvents() {
	switch (m_currentMode) {
		case MODE_BATTLE:
			doModeBattle();
			break;
		case MODE_WIN:
			doModeWin();
			break;
	}
}

void ModuleBattle::initConsoles() {
	// création des 3 consoles
	m_consolePlayer = *(GraphicsEngine::getInstance()->getConsole());
	m_consoleLog = *(GraphicsEngine::getInstance()->getConsole());
	m_consoleMenu = *(GraphicsEngine::getInstance()->getConsole());

	// initialisation des 3 consoles
	consoleSetWindow(&m_consolePlayer, 1, 19, 28, 4);
	consoleSetWindow(&m_consoleLog, 2, 12, 28, 6);
	consoleSetWindow(&m_consoleMenu, 1, 1, 18, 9);
}

void ModuleBattle::doModeBattle() {
	if (keysDown() & KEY_START) {
		winBattle();
		return;
	}

	if (keysDown() & KEY_Y) {
		m_spriteChar1->launchAnim(ANIM_0);
	}

	if (keysDown() & KEY_L) {
		m_spriteChar1->launchAnim(ANIM_ATTACK);
	}

	if (keysDown() & KEY_R) {
		m_spriteChar1->launchAnim(ANIM_STUN);
	}

	if (keysDown() & KEY_X) {
		m_spriteChar1->launchAnim(ANIM_HIT);
	}

	// Gestion des flèches haut et bas pour le menu
	if ((keysDown() & KEY_UP && m_selectedEntry > 0) || (keysDown() & KEY_DOWN && m_selectedEntry + 1 < m_menuEntries.size())) {
		if (keysDown() & KEY_UP && m_selectedEntry > 0) {
			m_selectedEntry--;
		}

		if (keysDown() & KEY_DOWN && m_selectedEntry + 1 < m_menuEntries.size()) {
			m_selectedEntry++;
		}

		// on met le doigt sur la ligne sélectionnée
		m_spriteFingerBottom->setPosY(m_selectedEntry * 8 + 21);

		// si on est en mode Attack on doit en plus gérer le doigt sur l'écran du haut
		if (m_currentMenu == MENU_BATTLE_ATTACK || m_currentMenu == MENU_BATTLE_INFO) {
			selectMonster();
		}
	}

	// Gestion de l'action sélectionnée quand on appuie sur A
	if (keysDown() & KEY_A) {
		if (m_currentMenu == MENU_BATTLE_DEFAULT) {
			// ici on est sur le menu principal
			// selon l'option sélectionée on charge le sous-menu correspondant
			if (m_menuEntries.at(m_selectedEntry) == MENU_BATTLE_ITEMS_STR) {
				showMenu(MENU_BATTLE_ITEMS);
			} else if (m_menuEntries.at(m_selectedEntry) == MENU_BATTLE_ATTACK_STR) {
				showMenu(MENU_BATTLE_ATTACK);
			} else if (m_menuEntries.at(m_selectedEntry) == MENU_BATTLE_INFO_STR) {
				showMenu(MENU_BATTLE_INFO);
			} else if (m_menuEntries.at(m_selectedEntry) == MENU_BATTLE_MAGIC_STR) {
				showMenu(MENU_BATTLE_MAGIC);
			}
		} else if (m_currentMenu == MENU_BATTLE_ATTACK) {
			// action "Attack" sur le mob sélectionné

			// bcp de choses à faire ici, on isole ça dans la méthode doActionAttack()
			doActionAttack();

			// s'il ne reste plus de mob en vie, on a gagné
			if (m_monstersAlive.empty()) {
				winBattle();
				return;
			}

			// gestion de la mort
			if (m_context->getActiveChar()->getCurrentHp() <= 0) {
				// on part sur le module Game Over
				m_context->switchModule(MODULE_GAMEOVER, false);
				return;
			}

			// on réaffiche les stats des players
			showPlayers();
			// on réaffiche le menu
			showMenu(MENU_BATTLE_DEFAULT);

		} else if (m_currentMenu == MENU_BATTLE_INFO) {
			// action "Info" sur le mob sélectionné

			CharacterMonster * monster = m_monstersAlive.at(m_selectedEntry);

			m_spriteFingerTop->setVisible(false);

			addLog("Name:%s", monster->getName().c_str());
			addLog("HP:%d/%d", monster->getCurrentHp(), monster->getMaxHp());
			addLog("MP:%d/%d", monster->getCurrentMp(), monster->getMaxMp());
			addLog("AB:%d - AC:%d", monster->getBonusAttack(), monster->getArmorClass());
			// on réaffiche le menu
			showMenu(MENU_BATTLE_DEFAULT);
		}
	}

	// B pour sortir d'un menu
	if (keysDown() & KEY_B) {
		if (m_currentMenu == MENU_BATTLE_ATTACK) {
			m_spriteFingerTop->setVisible(false);
		}
		if (m_currentMenu == MENU_BATTLE_ATTACK || m_currentMenu == MENU_BATTLE_INFO || m_currentMenu == MENU_BATTLE_ITEMS || m_currentMenu == MENU_BATTLE_MAGIC) {
			showMenu(MENU_BATTLE_DEFAULT);
		}
	}

	m_spriteChar1->update();

	// mise à jour des mobs
	for (unsigned int i = 0 ; i < m_spriteMonstersAlive.size() ; i++) {
		Sprite * sprite = m_spriteMonstersAlive.at(i);
		sprite->update();
	}

	m_spriteFingerBottom->update();
	m_spriteFingerTop->update();
}

void ModuleBattle::doActionAttack() {
	m_spriteFingerTop->setVisible(false);
	CharacterMonster * monster = m_monstersAlive.at(m_selectedEntry);

	addLog("Attack %s (%d HP left)", monster->getName().c_str(), monster->getCurrentHp());

	// on attaque !
	m_spriteChar1->launchAnim(ANIM_ATTACK);
	Sprite * sprite = m_spriteMonstersAlive.at(m_selectedEntry);
	int damage = m_context->getActiveChar()->attack(monster);

	if (damage > 0) {
		sprite->blink();
		addLog("You attack %s for %d damage !", monster->getName().c_str(), damage);
	} else {
		addLog("You miss %s !", monster->getName().c_str());
	}

	if (monster->getCurrentHp() <= 0) {
		addLog("%s is dead !", monster->getName().c_str());
		// on retire le mob du vector pour le mettre dans l'autre vector
		m_monstersDead.push_back(monster);
		m_monstersAlive.erase(m_monstersAlive.begin() + m_selectedEntry);
		// on efface le sprite
		sprite->setVisible(false);
		sprite->update();
		// on le met aussi dans l'autre vector dédié à ça
		m_spriteMonstersDead.push_back(sprite);
		m_spriteMonstersAlive.erase(m_spriteMonstersAlive.begin() + m_selectedEntry);

	} else {
		damage = monster->attack(m_context->getActiveChar());
		// le mob attaque à son tour !
		if (damage > 0) {
			addLog("%s attacks you for %d damage !", monster->getName().c_str(), damage);
			// on s'est fait toucher donc on lance l'animation correspondante
			m_spriteChar1->launchAnim(ANIM_HIT);
		} else {
			addLog("%s misses you !", monster->getName().c_str());
		}

	}
}

void ModuleBattle::selectMonster() {
	// on récupère le sprite du monstre attaqué pour se baser sur sa position
	Sprite * sprite = m_spriteMonstersAlive.at(m_selectedEntry);

	m_spriteFingerTop->setPos(sprite->getPos() + Coords(-8, 24));
}

void ModuleBattle::doModeWin() {
	if (keysDown() & KEY_A) {
		// on arrête le module mais on n'en lance pas d'autre,
		// on va revenir sur le module Game qui est en pause
		m_context->resumePausedModule();
	}
}

void ModuleBattle::addLog(const char * text, ...) {
	consoleSelect(&m_consoleLog);
	std::string sBuffer;
	std::ostringstream os;

	va_list varg;
	va_start(varg, text);

	for (int j = 0; text[j]; j++) {
		if (text[j] == '%') {
			if (text[j+1] == 's') {
				sBuffer += va_arg(varg, const char *);
				j++;
			} else if (text[j+1] == 'd') {
				os.str("");
				os << va_arg(varg, s32);
				sBuffer += os.str();
				j++;
			}
		} else {
			sBuffer += text[j];
		}
	}

	va_end(varg);

	iprintf("%s\n", sBuffer.c_str());
}

void ModuleBattle::generateMonsters() {
	// création des monstres
/*
	createMonster(MONSTER_GORILLA);
	createMonster(MONSTER_DRAGON);
	createMonster(MONSTER_RAT);
	*/

	for (int i = 0 ; i < 4 ; i++) {
		createMonster((MonsterType)RollDice((int)MONSTER_DRAGON));
	}
	/*
	createMonster(MONSTER_RAT);
	createMonster(MONSTER_FROG);
	createMonster(MONSTER_FROG);
	createMonster(MONSTER_FROG);
*/
	// TODO ModuleBattle numéroter les mobs s'il y en a plusieurs identiques

}

void ModuleBattle::createMonster(MonsterType type) {
	CharacterMonster * monster = new CharacterMonster(type);
	m_monstersAlive.push_back(monster);

	Sprite * monsterSprite = new Sprite(SCREEN_MAIN, GraphicsEngine::MonsterTypeToGraphicsSprite(type));
	monsterSprite->setCurrentFrame((int)type);

	switch (m_monstersAlive.size()) {
		case 1:
			monsterSprite->setPos(Coords(128, 32));
			break;
		case 2:
			monsterSprite->setPos(Coords(128, 96));
			break;
		case 3:
			monsterSprite->setPos(Coords(192, 32));
			break;
		case 4:
			monsterSprite->setPos(Coords(192, 96));
			break;
		default:
			monsterSprite->setPos(Coords(128, 60 + m_spriteMonstersAlive.size() * 64));
			break;
	}
	m_spriteMonstersAlive.push_back(monsterSprite);
}

void ModuleBattle::showPlayers() {
	consoleSelect(&m_consolePlayer);
	iprintf("\x1b[2J");

	iprintf("\x1b[0;0H%s", m_context->getActiveChar()->getName().c_str());

	if (m_context->getActiveChar()->getMaxHp() >= 100) {
		iprintf("\x1b[0;10H%ld/%ld", m_context->getActiveChar()->getCurrentHp(), m_context->getActiveChar()->getMaxHp());
	} else {
		iprintf("\x1b[0;11H%ld/%ld", m_context->getActiveChar()->getCurrentHp(), m_context->getActiveChar()->getMaxHp());
	}

	if (m_context->getActiveChar()->getMaxMp() >= 100) {
		iprintf("\x1b[0;18H%ld/%ld", m_context->getActiveChar()->getCurrentMp(), m_context->getActiveChar()->getMaxMp());
	} else if (m_context->getActiveChar()->getMaxMp() >= 10) {
		iprintf("\x1b[0;19H%ld/%ld", m_context->getActiveChar()->getCurrentMp(), m_context->getActiveChar()->getMaxMp());
	} else {
		iprintf("\x1b[0;20H%ld/%ld", m_context->getActiveChar()->getCurrentMp(), m_context->getActiveChar()->getMaxMp());
	}
}

void ModuleBattle::showMenu(MenuBattleType menu) {
	m_currentMenu = menu;

	consoleSelect(&m_consoleMenu);
	iprintf("\x1b[2J");

	m_menuEntries.clear();

	switch (m_currentMenu) {
		case MENU_BATTLE_DEFAULT:
			iprintf("\x1b[0;5HACTIONS");
			m_menuEntries.push_back(MENU_BATTLE_ATTACK_STR);
			m_menuEntries.push_back(MENU_BATTLE_INFO_STR);

			if (m_context->getActiveChar()->hasMagic()) {
				m_menuEntries.push_back(MENU_BATTLE_MAGIC_STR);
			}
			m_menuEntries.push_back(MENU_BATTLE_ITEMS_STR);
			break;
		case MENU_BATTLE_ATTACK:
		case MENU_BATTLE_INFO:
			m_selectedEntry = 0;
			if (m_currentMenu == MENU_BATTLE_INFO) {
				iprintf("\x1b[0;5H  INFO");
			} else {
				iprintf("\x1b[0;5H ATTACK");
			}
			// on affiche la liste des mobs
			for (unsigned int i = 0 ; i < m_monstersAlive.size() ; i++) {
				CharacterMonster * monster = m_monstersAlive.at(i);
				if (monster->getCurrentHp() > 0) {
					m_menuEntries.push_back(m_monstersAlive.at(i)->getName().c_str());
				}
			}
			// on affiche le doigt
			m_spriteFingerTop->setVisible(true);
			selectMonster();

			break;
		case MENU_BATTLE_ITEMS:
			iprintf("\x1b[0;5H ITEMS");
			// on affiche le contenu de l'inventaire
			for (unsigned int i = 0 ; i < m_context->getActiveChar()->getInventorySize() ; i++) {
				m_menuEntries.push_back(m_context->getActiveChar()->getInventoryItem(i)->getLongName().c_str());
			}
			break;
		case MENU_BATTLE_MAGIC:
			iprintf("\x1b[0;5H MAGIC");
			break;
		default:
			break;
	}

	for (unsigned int i = 0 ; i < m_menuEntries.size() ; i++) {
		iprintf("\x1b[%d;1H%s", i+2, m_menuEntries.at(i).c_str());
		if (i == 5)
			break;
	}

	m_selectedEntry = 0;
	m_spriteFingerBottom->setPos(Coords(0, 21));
	m_spriteFingerBottom->setVisible(true);
}

void ModuleBattle::winBattle() {
	m_currentMode = MODE_WIN;

	delete m_bgBottom;

	delete m_spriteFingerTop;
	m_spriteFingerTop = NULL;
	delete m_spriteFingerBottom;
	m_spriteFingerBottom = NULL;

	m_bgBottom = new Background(SCREEN_SUB, 3, BG_GAME_BOTTOM);

	// d'abord on vide tout l'écran
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");

	// on se met une console
	consoleSetWindow(&m_consoleLog, 2, 1, 24, 20);
	consoleSelect(&m_consoleLog);

	iprintf("\x1b[0;7H  VICTORY");
	iprintf("\n\n");

	iprintf("You won the battle !\n");

	int bonusXp = 0;
	long bonusMoney = 0;
	for (unsigned int i = 0 ; i < m_monstersDead.size() ; i++) {
		CharacterMonster * monster = m_monstersDead.at(i);
		bonusXp += monster->getXp();
		bonusMoney += monster->getMoney();

		// on gagne des loots
		for (unsigned int j = 0 ; j < monster->getInventorySize() ; j++) {
			Item * item = monster->getInventoryItem(j, true);
			iprintf("%s wins %s !\n", m_context->getActiveChar()->getName().c_str(), item->getLongName().c_str());
			/*
			if (item->isArmor()) {
				m_context->getActiveChar()->addItemToInventory(new ItemArmor(item));
			} else if (item->isWeapon()) {
				m_context->getActiveChar()->addItemToInventory(new ItemWeapon(item));
			} else {*/
				m_context->getActiveChar()->addItemToInventory(item);
			//s}
		}

	}

	// on gagne de l'xp
	iprintf("%s wins %d XP !\n", m_context->getActiveChar()->getName().c_str(), bonusXp);
	m_context->getActiveChar()->addXp(bonusXp);

	// on gagne de l'argent
	iprintf("%s wins %ld gold !\n", m_context->getActiveChar()->getName().c_str(), bonusMoney);
	m_context->getActiveChar()->addMoney(bonusMoney);


}

// custom includes
#include "modulegame.h"
#include "constants.h"
#include "mapfactory.h"
#include "context.h"

// standard includes
#include <nds.h>
#include <stdio.h>
#include <string>

using namespace AfroDS;

/**
 * Lancement du module Game, cr�ation du niveau
 */
ModuleGame::ModuleGame(Context * context) : Module(context), m_gameMode(MODE_WALK), m_activeMap(NULL), m_spritePlayer(NULL), m_spriteSelectedItem(NULL) {
	// chargement du menu
	initMenu();

	// chargement du monde
	initWorld(MapWarp(MAP_FIXED));

	// affichage des stats du perso
	showStatus();
}

/**
 * Destructeur du module, supprime tous les sprites et backgrounds
 */
ModuleGame::~ModuleGame() {
	// suppression du bg
	delete m_bgBottom;
	// on efface l'�cran
	iprintf("\x1b[2J");

	// suppression des sprites
	delete m_spritePlayer;
	delete m_spriteIconQuit;
	delete m_spriteIconOptions;
	delete m_spriteIconEquipment;
	delete m_spriteIconInventory;
	delete m_spriteIconStatus;
	delete m_spriteFinger;
	delete m_spriteSelectedItem;

	// suppression des autres objets
	delete m_activeMap;
}

/**
 * Gestion des �v�nements du module Game
 */
void ModuleGame::moduleEvents() {
	switch (m_gameMode) {
		default:
		case MODE_WALK:
			if (!doModeWalk()) {
				// si doModeWalk() renvoie false �a veut dire qu'on a quitt� le module, il a donc �t� delete
				return;
			}
			break;
		case MODE_INVENTORY:
			doModeSelection();
			break;
		case MODE_EQUIPMENT:
			doModeSelection();
			break;
	}

	// Mise � jour des sprites
	m_spritePlayer->update();
	m_spriteIconStatus->update();
	m_spriteIconInventory->update();
	m_spriteIconEquipment->update();
	m_spriteIconOptions->update();
	m_spriteIconQuit->update();
	m_spriteFinger->update();
	m_spriteSelectedItem->update();

	// mise � jour de la map et de ses sprites
	m_activeMap->update();
}

void ModuleGame::modulePause() {
	// on vide tout l'�cran
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");
	delete m_bgBottom;

	// Masquage des sprites

	// écran du haut
	m_spritePlayer->setVisible(false);
	m_activeMap->setVisible(false);

	// écran du bas
	m_spriteIconStatus->setVisible(false);
	m_spriteIconInventory->setVisible(false);
	m_spriteIconEquipment->setVisible(false);
	m_spriteIconOptions->setVisible(false);
	m_spriteIconQuit->setVisible(false);
	m_spriteFinger->setVisible(false);


	// Mise � jour des sprites

	// écran du haut
	m_spritePlayer->update();
	m_activeMap->update();

	// écran du bas
	m_spriteIconStatus->update();
	m_spriteIconInventory->update();
	m_spriteIconEquipment->update();
	m_spriteIconOptions->update();
	m_spriteIconQuit->update();
	m_spriteFinger->update();
}

void ModuleGame::moduleResume() {
	// chargement du background du bas
	m_bgBottom = new Background(SCREEN_SUB, AFRODS_LAYER_GAME_BOTTOM_BG, BG_GAME_BOTTOM);

	// on reprend la main sur la console
	initConsoles();
	//consoleSelect(&m_consoleMain);

	// affichage des stats du perso
	showStatus();

	// on recharge les graphismes du haut
	m_activeMap->loadGraphics();

	// on r�affiche tous les sprites
	m_spritePlayer->setVisible(true);
	m_spriteIconStatus->setVisible(true);
	m_spriteIconInventory->setVisible(true);
	m_spriteIconEquipment->setVisible(true);
	m_spriteIconOptions->setVisible(true);
	m_spriteIconQuit->setVisible(true);

	// on r�affiche la map
	m_activeMap->setVisible(true);

	// Mise � jour des sprites
	m_spritePlayer->update();
	m_spriteIconStatus->update();
	m_spriteIconInventory->update();
	m_spriteIconEquipment->update();
	m_spriteIconOptions->update();
	m_spriteIconQuit->update();
	m_spriteFinger->update();

	// mise � jour de la map
	m_activeMap->update();
}

/**
 * Gestion des modes MODE_INVENTORY et MODE_EQUIPMENT : interactions :
 * - revenir en mode MODE_WALK en appuyant sur Start
 * - basculer entre MODE_INVENTORY et MODE_EQUIPMENT en appuyant sur R ou L
 * - naviguer dans l'inventaire ou l'�quipement avec haut/bas
 * - �quiper un item de l'inventaire avec A
 * - retirer un item de l'�quipement avec A
 */
void ModuleGame::doModeSelection() {
	// si on fait Start on retourne au mode Walk
	if (keysDown() & KEY_START) {
		consoleSelect(&m_consoleDesc);
		iprintf("\x1b[2J");
		m_spriteFinger->setVisible(false);
		m_spriteSelectedItem->setVisible(false);
		m_gameMode = MODE_WALK;
	}

	// si on fait L ou R on switch entre mode Equipment et Inventory
	if (keysDown() & KEY_L || keysDown() & KEY_R) {
		m_selectedEntry = 0;
		m_offsetInventory = 0;
		m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
		m_spriteSelectedItem->setVisible(false);
		if (m_gameMode == MODE_INVENTORY) {
			showEquipment();
			m_gameMode = MODE_EQUIPMENT;
		} else {
			showInventory();
			m_gameMode = MODE_INVENTORY;
		}
	}

	// on calcule le nombre d'�l�ments qu'on a dans le menu
	unsigned int iNumEntries = 0;
	if (m_gameMode == MODE_EQUIPMENT) {
		iNumEntries = SLOT_SIZE - 1;
	} else {
		iNumEntries = m_context->getActiveChar()->getInventorySize() - 1;
	}

	// gestion des fl�ches pour choisir un item dans le menu
	if ((keysDown() & KEY_DOWN && m_selectedEntry < iNumEntries) || (keysDown() & KEY_UP && m_selectedEntry > 0)) {
		// on change la ligne s�lectionn�e et on replace le doigt
		if (keysDown() & KEY_DOWN && m_selectedEntry < iNumEntries) {
			m_selectedEntry++;
			if (m_selectedEntry > AFRODS_GAME_INVENTORY_NBLINES - 2) {
				m_offsetInventory++;
				showInventory();
			}
			m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
		} else if (keysDown() & KEY_UP && m_selectedEntry > 0) {
			if (m_selectedEntry > AFRODS_GAME_INVENTORY_NBLINES - 2) {
				m_offsetInventory--;
				showInventory();
			}
			m_selectedEntry--;
			m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
		}

		consoleSelect(&m_consoleDesc);
		iprintf("\x1b[2J");

		// affichage des infos
		if (m_gameMode == MODE_INVENTORY) {
			Item * item = m_context->getActiveChar()->getInventoryItem(m_selectedEntry);
			if (item != NULL) {
				m_spriteSelectedItem->setCurrentFrame(item->getLargeIcon());
				m_spriteSelectedItem->setVisible(true);
				iprintf("%s", item->getDescription().c_str());
			}
		} else if (m_gameMode == MODE_EQUIPMENT) {
			iprintf("Slot : %s\n", Character::translateSlot((EquipmentSlot)m_selectedEntry).c_str());
			Item * item = m_context->getActiveChar()->getEquipmentItem((EquipmentSlot)m_selectedEntry);
			if (item != NULL) {
				m_spriteSelectedItem->setCurrentFrame(item->getLargeIcon());
				m_spriteSelectedItem->setVisible(true);
				iprintf("%s", item->getDescription().c_str());
			} else {
				m_spriteSelectedItem->setVisible(false);
			}
		}
	}

	// gestion de la touche A pour �quiper ou retirer un item
	if (keysDown() & KEY_A) {
		if (m_gameMode == MODE_INVENTORY) {
			// on r�cup�re l'item
			Item * item = m_context->getActiveChar()->getInventoryItem(m_selectedEntry);

			// si c'est une arme ou armure, on �quipe l'item
			if (item->isArmor() || item->isWeapon()) {
				if (m_context->getActiveChar()->equipItem(m_selectedEntry)) {
					// si on �tait sur le dernier �l�ment, on remonte d'un cran
					if (m_selectedEntry > 0 && m_selectedEntry == m_context->getActiveChar()->getInventorySize()) {
						if (m_selectedEntry > AFRODS_GAME_INVENTORY_NBLINES - 2) {
							m_offsetInventory--;
						}
						m_selectedEntry--;
						m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
					}
					// on doit redessiner
					showInventory();
				}
			} else {
				// sinon on active l'item
				m_context->getActiveChar()->activateInventoryItem(m_selectedEntry);
				// si on �tait sur le dernier �l�ment, on remonte d'un cran
				if (m_selectedEntry > 0 && m_selectedEntry == m_context->getActiveChar()->getInventorySize()) {
					if (m_selectedEntry > AFRODS_GAME_INVENTORY_NBLINES - 2) {
						m_offsetInventory--;
					}
					m_selectedEntry--;
					m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
				}
				// on doit redessiner
				showInventory();
			}
		} else {
			// on retire l'item
			if (m_context->getActiveChar()->unequipItem((EquipmentSlot)m_selectedEntry)) {
				// on doit redessiner
				showEquipment();
			}
		}
	}
}

/**
 * Gestion du mode MODE_WALK : interactions :
 * - d�placer le personnage avec les fl�ches
 * - activer le mode MODE_INVENTORY en appuyant sur Start
 * - afficher les stats du personnage en cliquant sur le sprite Status
 * - afficher l'inventaire en cliquant sur le sprite Inventory
 * - afficher l'�quipement en cliquant sur le sprite Equipment
 * - quitter le jeu en cliquant sur le sprite Quit
 * @return bool
 */
bool ModuleGame::doModeWalk() {
	// Gestion des ic�nes du menu
	if (keysDown() & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		// Si on touche le sprite pour quitter, on quitte
		if (m_spriteIconQuit->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			// TODO Game quitter de fa�on moins abrupte !
			quit();
			return false;
		}
		// Si on touche le sprite pour voir les stats
		if (m_spriteIconStatus->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			showStatus();
		}
		// Si on touche le sprite pour montrer l'inventaire
		if (m_spriteIconInventory->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			showInventory();
		}
		// Si on touche le sprite pour montrer l'�quipement
		if (m_spriteIconEquipment->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			showEquipment();
		}
	}

	// si on fait Start on se met en mode s�lection d'item
	if (keysDown() & KEY_START) {
		m_gameMode = MODE_INVENTORY;
		// on affiche le sprite du doigt
		m_selectedEntry = 0;
		m_offsetInventory = 0;
		m_spriteFinger->setPos(0, 24 + (m_selectedEntry - m_offsetInventory) * 8 - AFRODS_GAME_OFFSET_FINGER_Y);
		m_spriteFinger->setVisible(true);
		// on affiche l'inventaire
		showInventory();
	}

	// pour l'instant on lance le combat en appuyant sur X
	if (keysDown() & KEY_X) {
		battle();
	}

	// D�placement du personnage
	moveChar();

	return true;
}

/**
 * Initialisation du menu en bas :
 * - affichage du background
 * - affichage des 5 sprites de menu
 */
void ModuleGame::initMenu() {
	initConsoles();
	// chargement du background du bas
	m_bgBottom = new Background(SCREEN_SUB, AFRODS_LAYER_GAME_BOTTOM_BG, BG_GAME_BOTTOM);

	// on charge les sprites de l'�cran du bas
	Coords coords = Coords(AFRODS_GAME_OFFSET_ICONS_X, AFRODS_GAME_OFFSET_ICONS_Y);
	m_spriteIconStatus = new SpriteGameIcon(ICON_STATUS);
	m_spriteIconStatus->setPos(coords);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	m_spriteIconInventory = new SpriteGameIcon(ICON_INVENTORY);
	m_spriteIconInventory->setPos(coords);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	m_spriteIconEquipment = new SpriteGameIcon(ICON_EQUIPMENT);
	m_spriteIconEquipment->setPos(coords);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	m_spriteIconOptions = new SpriteGameIcon(ICON_OPTIONS);
	m_spriteIconOptions->setPos(coords);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	m_spriteIconQuit = new SpriteGameIcon(ICON_QUIT);
	m_spriteIconQuit->setPos(coords);

	// le doigt
	m_spriteFinger = new Sprite(SCREEN_SUB, SPRITE_FINGER);
	m_spriteFinger->setVisible(false);

	// l'item s�lectionn�
	m_spriteSelectedItem = new Sprite(SCREEN_SUB, SPRITE_GAME_ITEMS);
	m_spriteSelectedItem->setVisible(false);
	m_spriteSelectedItem->setPos(176, 140);
}

void ModuleGame::initConsoles() {
	// cr�ation des consoles
	m_consoleMain = *(GraphicsEngine::getInstance()->getConsole());
	m_consoleDesc = *(GraphicsEngine::getInstance()->getConsole());

	consoleSetWindow(&m_consoleMain, 2, 1, 24, 16);
	consoleSetWindow(&m_consoleDesc, 2, 17, 20, 5);

	// on se met sur la console principale
	consoleSelect(&m_consoleMain);
}

/**
 * Initialisation du monde affich� en haut, g�r�
 * au travers de la classe Map
 */
void ModuleGame::initWorld(MapWarp warp) {
	// cr�ation de la map
	m_activeMap = MapFactory::loadMap(warp);
	if (warp.map2 == MAP_FIXED) {
		m_context->setBattleBackground(BG_BATTLE_TOP_FOREST);
	} else {
		m_context->setBattleBackground(BG_BATTLE_TOP_DUNGEON);
	}

	// on cr�e le sprite du perso � l'�cran
	if (m_spritePlayer == NULL) {
		m_spritePlayer = new SpriteChar(SCREEN_MAIN, GraphicsEngine::CharacterClassToGraphicsSprite(m_context->getActiveChar()->getClass(), false));
	}

	// on place le perso sur la position de d�part de la map
	Coords coords;
	if (warp.pos2 == Coords(0, 0)) {
		// si la position du perso n'était pas initialisée, on prend la position de départ "absolue" de la map
		coords = m_activeMap->getStartingPos();
	} else {
		// sinon on prend la position du warp
		coords = warp.pos2;
	}

	// le tile du perso fait 32x32
	// on re�oit des coordonn�es sur une grille de tiles en 16x16
	// on veut centrer le perso comme �a :
	// ....      les . repr�sentent le sprite du perso en 32x32
	// ....      les x repr�sentent l'emplacement de la tile initiale
	// .xx.      donc par rapport � la coordonn�e d'origine
	// .xx.      on retire 8 � X et 16 � Y
	coords.x = coords.x * 16 - AFRODS_GAME_OFFSET_CENTER_CHAR_X;
	coords.y = coords.y * 16 - AFRODS_GAME_OFFSET_CENTER_CHAR_Y;

	m_context->getActiveChar()->setPos(coords);

	// on positionne le sprite et la map
	updatePositions();

	// On affiche la map
	m_activeMap->setVisible(true);

	// On met � jour le perso
	m_spritePlayer->setDefaultAnim();
}

void ModuleGame::updatePositions() {

	if (m_activeMap->getWidth() * 16 <= AFRODS_SCREEN_WIDTH) {
		// si la map est plus petite que l'�cran
		m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x);
		m_activeMap->scrollX(0);
	} else {
		// si la map est plus grande que l'�cran
		// on calcule les coordonn�es o� afficher le perso
		if (m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_WIDTH / 2 < AFRODS_SCREEN_WIDTH / 2) {
			// s'il est proche de la gauche, on r�cup�re directement sa position
			m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x);
			m_activeMap->scrollX(0);
		} else if (m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_WIDTH / 2 > ((m_activeMap->getWidth()-1) * 16) - AFRODS_SCREEN_WIDTH / 2) {
			// s'il est proche de la droite, on calcule sa position par rapport � la droite de l'�cran
			m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x - ((m_activeMap->getWidth()-1) * 16 - AFRODS_SCREEN_WIDTH));
			m_activeMap->scrollX((m_activeMap->getWidth()-1) * 16 - AFRODS_SCREEN_WIDTH);
		} else {
			// s'il n'est pas pr�s du bord, c'est au centre
			m_spritePlayer->setPosX(AFRODS_SCREEN_WIDTH / 2 - AFRODS_CHAR_WIDTH / 2);
			m_activeMap->scrollX(m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X - AFRODS_SCREEN_WIDTH / 2 + AFRODS_CHAR_WIDTH / 2);
		}
	}

	// TODO voir pourquoi �a marche avec AFRODS_GAME_OFFSET_CENTER_CHAR_X au lieu de AFRODS_GAME_OFFSET_CENTER_CHAR_Y, �a devrait pas !
	if (m_activeMap->getHeight() * 16 <= AFRODS_SCREEN_HEIGHT) {
		// si la map est plus petite que l'�cran
		m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y);
		m_activeMap->scrollY(0);
	} else {
		// si la map est plus grande que l'�cran
		// on calcule les coordonn�es o� afficher le perso
		if (m_context->getActiveChar()->getPosY() - AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_HEIGHT / 2 < AFRODS_SCREEN_HEIGHT / 2) {
			// s'il est proche du haut, on r�cup�re directement sa position
			m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y);
			m_activeMap->scrollY(0);
		} else if (m_context->getActiveChar()->getPosY() - AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_HEIGHT / 2 > ((m_activeMap->getHeight()-1) * 16) - AFRODS_SCREEN_HEIGHT / 2) {
			// s'il est proche du bas, on calcule sa position par rapport au bas de l'�cran
			m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y - ((m_activeMap->getHeight()-1) * 16 - AFRODS_SCREEN_HEIGHT));
			m_activeMap->scrollY((m_activeMap->getHeight()-1) * 16 - AFRODS_SCREEN_HEIGHT);
		} else {
			// s'il n'est pas pr�s du bord, c'est au centre
			m_spritePlayer->setPosY(AFRODS_SCREEN_HEIGHT / 2 - AFRODS_CHAR_HEIGHT / 2);
			m_activeMap->scrollY(m_context->getActiveChar()->getPosY()-AFRODS_GAME_OFFSET_CENTER_CHAR_X - AFRODS_SCREEN_HEIGHT / 2 + AFRODS_CHAR_HEIGHT / 2);
		}
	}
}

/**
 * Gestion du d�placement du perso, avec scrolling en cons�quence
 */
void ModuleGame::moveChar() {
	// si on commence � appuyer, on lance l'animation
	Coords move;
	bool hasMoved = false;
	SpriteDirection sprtDir = DIR_NOTHING;
	if (keysHeld()) {
		if (keysHeld() & KEY_UP) {
			move.y = -1 * m_context->getActiveChar()->getMoveSpeed();
			sprtDir = DIR_UP;
		}
		if (keysHeld() & KEY_DOWN) {
			move.y = m_context->getActiveChar()->getMoveSpeed();
			sprtDir = DIR_DOWN;
		}
		if (keysHeld() & KEY_LEFT) {
			move.x = -1 * m_context->getActiveChar()->getMoveSpeed();
			sprtDir = DIR_LEFT;
		}
		if (keysHeld() & KEY_RIGHT) {
			move.x = m_context->getActiveChar()->getMoveSpeed();
			sprtDir = DIR_RIGHT;
		}

		if (sprtDir != DIR_NOTHING) {
			m_spritePlayer->setCurrentDir(sprtDir);
			m_spritePlayer->animate();

			if (m_activeMap->canMove(m_context->getActiveChar()->getPos() + Coords(move.x, 0)))
			{
				hasMoved = true;
				m_context->getActiveChar()->setPosX(m_context->getActiveChar()->getPosX() + move.x);
			}
			if (m_activeMap->canMove(m_context->getActiveChar()->getPos() + Coords(0, move.y)))
			{
				hasMoved = true;
				m_context->getActiveChar()->setPosY(m_context->getActiveChar()->getPosY() + move.y);
			}
		}
	}

	if (/*hasMoved*/ keysUp() & KEY_A) {
		if (m_activeMap->isOnWarp(m_context->getActiveChar()->getPos())) {
			// calcul de la tile du perso
			Coords coordsPerso = m_context->getActiveChar()->getPos();
			coordsPerso.x = (coordsPerso.x + AFRODS_MAP_OFFSET_CHAR_LEFT)/16;
			coordsPerso.y = (coordsPerso.y + AFRODS_MAP_OFFSET_CHAR_TOP)/16;

			// on cherche le MapWarp qui se trouve sur cette tile
			MapWarp warp = m_activeMap->findWarp(coordsPerso);
			if (warp != MapWarp()) {
				// on delete la map et on la recr�e
				delete m_activeMap;
				initWorld(warp);

				m_spritePlayer->setCurrentDir(DIR_DOWN);
				m_spritePlayer->setDefaultAnim();
				return;
			}
		}
	}
	// si on rel�che la direction, on se remet dans la bonne frame
	if (keysUp() & KEY_UP || keysUp() & KEY_DOWN || keysUp() & KEY_LEFT || keysUp() & KEY_RIGHT) {
		m_spritePlayer->setDefaultAnim();
	}

	// gestion du scrolling et du positionnement des sprites
	updatePositions();

}

/**
 * M�thode appel�e lorsqu'on veut quitter le jeu
 */
void ModuleGame::quit() {
	// on indique qu'on veut sortir pour aller dans le module Splash
	m_context->switchModule(MODULE_SPLASH, false);
}

/**
 * Affiche les stats du personnage. Correspond � l'ic�ne "Status" du menu
 */
void ModuleGame::showStatus() {
	consoleSelect(&m_consoleMain);

	// on efface l'�cran
	iprintf("\x1b[2J");

	iprintf("\x1b[0;7H  STATUS");
	iprintf("\n\n");

	// nom du perso
	iprintf("Name : %s\n", m_context->getActiveChar()->getName().c_str());

	// Classe
	//iprintf("Class : %s\n", CharacterPlayer::translateClass(m_context->getActiveChar()->getClass()).c_str());

	// Classe et Level
	iprintf("%s Level %d\n", CharacterPlayer::translateClass(m_context->getActiveChar()->getClass()).c_str(), m_context->getActiveChar()->getLevel());

	// XP
	iprintf("EXP : %ld\n", m_context->getActiveChar()->getExperience());

	// Thune
	iprintf("Gold : %ld\n", m_context->getActiveChar()->getMoney());

	iprintf("\n");

	// Stats
	Stats stats = m_context->getActiveChar()->getStats();
/*
	if (stats.force > m_context->getActiveChar()->getBaseStats().force) {
		iprintf("\x1b[32m"); // vert
	} else if (stats.force < m_context->getActiveChar()->getBaseStats().force) {
		iprintf("\x1b[31m"); // rouge
	} else {
		iprintf("\x1b[30m"); // noir
	}
*/
	iprintf("FOR : %d\n", stats.force);
	iprintf("DEX : %d\n", stats.dexterity);
	iprintf("CON : %d\n", stats.constitution);
	iprintf("INT : %d\n", stats.intelligence);
	iprintf("WIS : %d\n", stats.wisdom);
	iprintf("CHA : %d\n", stats.charisma);

	// HP et MP
	iprintf("\x1b[7;11HHP : %ld/%ld", m_context->getActiveChar()->getCurrentHp(), m_context->getActiveChar()->getMaxHp());
	iprintf("\x1b[8;11HMP : %ld/%ld", m_context->getActiveChar()->getCurrentMp(), m_context->getActiveChar()->getMaxMp());

	// Attack Bonus (AB) et Armor Class (AC)
	iprintf("\x1b[9;11HAB : %d", m_context->getActiveChar()->getBonusAttack());
	iprintf("\x1b[10;11HAC : %d", m_context->getActiveChar()->getArmorClass());

	// XP NEXT
	iprintf("\x1b[4;11HNEXT : %ld", Character::XpForNextLevel(m_context->getActiveChar()->getExperience()));
}

/**
 * Affiche l'inventaire du personnage. Correspond � l'ic�ne "Inventory" du menu
 */
void ModuleGame::showInventory() {
	// on se met sur la console principale
	consoleSelect(&m_consoleMain);

	// on efface l'�cran
	iprintf("\x1b[2J");
	iprintf("\x1b[0;7H INVENTORY");

	iprintf("\n\n");

	// on parcourt l'inventaire
	for (unsigned int i = 0 ; i + m_offsetInventory < m_context->getActiveChar()->getInventorySize() ; i++) {
		Item * item = m_context->getActiveChar()->getInventoryItem(i + m_offsetInventory);
		std::string sText;
		sText = char(144 + item->getSmallIcon());
		sText += item->getLongName();
		if (sText.size() > 23) {
			sText = sText.substr(0, 23);
		}

		iprintf("%s\n", sText.c_str());
		if (i >= AFRODS_GAME_INVENTORY_NBLINES - 1) {
			break;
		}
	}

	if (m_gameMode != MODE_WALK) {
		consoleSelect(&m_consoleDesc);
		iprintf("\x1b[2J");
		Item * item = m_context->getActiveChar()->getInventoryItem(m_selectedEntry);
		if (item != NULL) {
			m_spriteSelectedItem->setCurrentFrame(item->getLargeIcon());
			m_spriteSelectedItem->setVisible(true);
			iprintf("%s", item->getDescription().c_str());
		}
	}
}

/**
 * Affiche l'�quipement du personnage. Correspond � l'ic�ne "Equipment" du menu
 */
void ModuleGame::showEquipment() {
	// on se met sur la console principale
	consoleSelect(&m_consoleMain);

	// on efface l'�cran
	iprintf("\x1b[2J");
	iprintf("\x1b[0;7H EQUIPMENT");

	iprintf("\n\n");

	// on parcourt l'inventaire
	for (int i = 0 ; i < SLOT_SIZE ; i++) {
		EquipmentSlot slot = (EquipmentSlot)i;
		Item * item = m_context->getActiveChar()->getEquipmentItem(slot);

		std::string sText = Character::translateSlot(slot, true) + ":";

		if (item != NULL) {
			sText += char(144 + item->getSmallIcon());
			sText += item->getLongName();
		}

		if (sText.size() > 23) {
			sText = sText.substr(0, 23);
		}

		iprintf("%s\n", sText.c_str());
	}

	if (m_gameMode != MODE_WALK) {
		consoleSelect(&m_consoleDesc);
		iprintf("\x1b[2J");
		iprintf("Slot : %s\n", Character::translateSlot((EquipmentSlot)m_selectedEntry).c_str());
		Item * item = m_context->getActiveChar()->getEquipmentItem((EquipmentSlot)m_selectedEntry);
		if (item != NULL) {
			m_spriteSelectedItem->setCurrentFrame(item->getLargeIcon());
			m_spriteSelectedItem->setVisible(true);
			iprintf("%s", item->getDescription().c_str());
		}
	}
}

void ModuleGame::battle() {
	// on indique qu'on veut se mettre en pause pour aller dans le module Battle
	m_context->switchModule(MODULE_BATTLE, true);
}

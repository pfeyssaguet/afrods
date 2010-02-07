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
 * Lancement du module Game, création du niveau
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
	// on vide tout l'écran
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");
	// suppression du bg
	delete m_bgBottom;

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
 * Gestion des événements du module Game
 */
void ModuleGame::moduleEvents() {
	switch (m_gameMode) {
		default:
		case MODE_WALK:
			if (!doModeWalk()) {
				// si doModeWalk() renvoie false ça veut dire qu'on a quitté le module, il a donc été delete
				return;
			}
			break;
		case MODE_SHOP:
			doModeShop();
			break;
		case MODE_INVENTORY:
			doModeSelection();
			break;
		case MODE_EQUIPMENT:
			doModeSelection();
			break;
	}

	// Mise à jour des sprites
	m_spritePlayer->update();
	m_spriteIconStatus->update();
	m_spriteIconInventory->update();
	m_spriteIconEquipment->update();
	m_spriteIconOptions->update();
	m_spriteIconQuit->update();
	m_spriteFinger->update();
	m_spriteSelectedItem->update();

	// mise à jour de la map et de ses sprites
	m_activeMap->update();
}

void ModuleGame::modulePause() {
	// on vide tout l'écran
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


	// Mise à jour des sprites

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
	// FIXME si on revient du module Battle, le sprite du perso part en vrille (sauf sur la map world0)

	// chargement du background du bas
	m_bgBottom = new Background(SCREEN_SUB, AFRODS_LAYER_GAME_BOTTOM_BG, BG_GAME_BOTTOM);

	// on reprend la main sur la console
	initConsoles();
	//consoleSelect(&m_consoleMain);

	// affichage des stats du perso
	showStatus();

	// on recharge les graphismes du haut
	m_activeMap->loadGraphics();

	// on réaffiche tous les sprites
	m_spritePlayer->setVisible(true);
	m_spriteIconStatus->setVisible(true);
	m_spriteIconInventory->setVisible(true);
	m_spriteIconEquipment->setVisible(true);
	m_spriteIconOptions->setVisible(true);
	m_spriteIconQuit->setVisible(true);

	// on réaffiche la map
	m_activeMap->setVisible(true);

	// Mise à jour des sprites
	m_spritePlayer->update();
	m_spriteIconStatus->update();
	m_spriteIconInventory->update();
	m_spriteIconEquipment->update();
	m_spriteIconOptions->update();
	m_spriteIconQuit->update();
	m_spriteFinger->update();

	// mise à jour de la map
	m_activeMap->update();
}

/**
 * Gestion des modes MODE_INVENTORY et MODE_EQUIPMENT : interactions :
 * - revenir en mode MODE_WALK en appuyant sur Start
 * - basculer entre MODE_INVENTORY et MODE_EQUIPMENT en appuyant sur R ou L
 * - naviguer dans l'inventaire ou l'équipement avec haut/bas
 * - équiper un item de l'inventaire avec A
 * - retirer un item de l'équipement avec A
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

	// on calcule le nombre d'éléments qu'on a dans le menu
	unsigned int iNumEntries = 0;
	if (m_gameMode == MODE_EQUIPMENT) {
		iNumEntries = SLOT_SIZE - 1;
	} else {
		iNumEntries = m_context->getActiveChar()->getInventorySize() - 1;
	}

	// gestion des flèches pour choisir un item dans le menu
	if ((keysDown() & KEY_DOWN && m_selectedEntry < iNumEntries) || (keysDown() & KEY_UP && m_selectedEntry > 0)) {
		// on change la ligne sélectionnée et on replace le doigt
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
			iprintf("Slot : %s\n", Creature::translateSlot((EquipmentSlot)m_selectedEntry).c_str());
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

	// gestion de la touche A pour équiper ou retirer un item
	if (keysDown() & KEY_A) {
		if (m_gameMode == MODE_INVENTORY) {
			// on récupère l'item
			Item * item = m_context->getActiveChar()->getInventoryItem(m_selectedEntry);

			// si c'est un item qui s'équipe
			if (item->isEquipable()) {
				if (m_context->getActiveChar()->equipItem(m_selectedEntry)) {
					// si on était sur le dernier élément, on remonte d'un cran
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
				// si on était sur le dernier élément, on remonte d'un cran
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
 * - déplacer le personnage avec les flèches
 * - activer le mode MODE_INVENTORY en appuyant sur Start
 * - afficher les stats du personnage en cliquant sur le sprite Status
 * - afficher l'inventaire en cliquant sur le sprite Inventory
 * - afficher l'équipement en cliquant sur le sprite Equipment
 * - quitter le jeu en cliquant sur le sprite Quit
 * @return bool
 */
bool ModuleGame::doModeWalk() {
	// Gestion des icônes du menu
	if (keysDown() & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);
		// Si on touche le sprite pour quitter, on quitte
		if (m_spriteIconQuit->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			// TODO Game quitter de façon moins abrupte !
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
		// Si on touche le sprite pour montrer l'équipement
		if (m_spriteIconEquipment->isInZone(touch.px, touch.py)) {
			while(keysHeld() & KEY_TOUCH) {
				swiWaitForVBlank();
				scanKeys();
			}
			showEquipment();
		}
	}

	// si on fait Start on se met en mode sélection d'item
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

	// pour l'instant on lance un shop en appuyant sur Y
	if (keysDown() & KEY_Y) {
		initShop();
	}

	// Déplacement du personnage
	moveChar();

	return true;
}

void ModuleGame::initShop() {
	// on change de background
	delete m_bgBottom;
	m_bgBottom = new Background(SCREEN_SUB, 3, BG_SHOP_BOTTOM);
	m_spriteIconEquipment->setVisible(false);
	m_spriteIconInventory->setVisible(false);
	m_spriteIconOptions->setVisible(false);
	m_spriteIconQuit->setVisible(false);
	m_spriteIconStatus->setVisible(false);

	m_gameMode = MODE_SHOP;

	// on vide tout l'écran
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");

	consoleSetWindow(&m_consoleMain, 1, 1, 30, AFRODS_GAME_SHOP_NBLINES);
	consoleSetWindow(&m_consoleDesc, 1, 17, 24, 5);
	consoleSetWindow(&m_consolePrices, 28, 17, 4, 5);

	showShop(MENU_GAME_DEFAULT);
}

void ModuleGame::showShop(const MenuGameType menu) {
	m_shopCurrentMenu = menu;

	consoleSelect(&m_consoleMain);
	iprintf("\x1b[2J");

	m_shopMenuEntries.clear();
	m_shopSelectedEntry = 0;

	// TODO refaire le système de menus pour le factoriser avec celui du module battle, celui de l'inventaire, etc
	switch(m_shopCurrentMenu) {
		default:
		case MENU_GAME_DEFAULT:
			// TODO remplacer par le nom du marchand
			iprintf("\x1b[0;11HSHOP");
			m_shopMenuEntries.push_back(MENU_GAME_BUY_STR);
			m_shopMenuEntries.push_back(MENU_GAME_SELL_STR);
			m_shopMenuEntries.push_back(MENU_GAME_QUIT_STR);

			for (unsigned int i = 0 ; i < m_shopMenuEntries.size() ; i++) {
				iprintf("\x1b[%d;1H%s", i+2, m_shopMenuEntries.at(i).c_str());
				if (i == AFRODS_GAME_SHOP_NBLINES)
					break;
			}

			break;
		case MENU_GAME_SELL:
			iprintf("\x1b[0;11HSELL");
			// on parcourt l'inventaire
			for (unsigned int i = 0 ; i + m_offsetInventory < m_context->getActiveChar()->getInventorySize() ; i++) {
				Item * item = m_context->getActiveChar()->getInventoryItem(i + m_offsetInventory);
				std::string sText;
				sText = char(144 + item->getSmallIcon());
				sText += item->getLongName();
				if (sText.size() > 23) {
					sText = sText.substr(0, 23);
				}

				iprintf("\x1b[%d;1H%s", i+2, sText.c_str());
				iprintf("\x1b[%d;26H%ld", i+2, item->getPrice());

				m_shopMenuEntries.push_back(sText);
				if (i == AFRODS_GAME_SHOP_NBLINES - 1) {
					break;
				}
			}

			break;
		case MENU_GAME_BUY:
			iprintf("\x1b[0;12HBUY");
			break;
	}


	m_spriteFinger->setPos(Coords(0, 21));
	m_spriteFinger->setVisible(true);

	// la thune
	consoleSelect(&m_consolePrices);
	iprintf("\x1b[0;0H%ld", m_context->getActiveChar()->getMoney() / 1000);
	iprintf("\x1b[3;0H%ld", m_context->getActiveChar()->getMoney() % 1000);

}

void ModuleGame::quitShop() {
	delete m_bgBottom;
	m_bgBottom = new Background(SCREEN_SUB, AFRODS_LAYER_GAME_BOTTOM_BG, BG_GAME_BOTTOM);
	m_spriteIconEquipment->setVisible(true);
	m_spriteIconInventory->setVisible(true);
	m_spriteIconOptions->setVisible(true);
	m_spriteIconQuit->setVisible(true);
	m_spriteIconStatus->setVisible(true);
	m_spriteFinger->setVisible(false);

	m_gameMode = MODE_WALK;

	// on vide tout l'écran
	consoleSetWindow(false, 0, 0, 31, 23);
	iprintf("\x1b[2J");

	// on remet les consoles
	consoleSetWindow(&m_consoleMain, 2, 1, 24, 16);
	consoleSetWindow(&m_consoleDesc, 2, 17, 20, 5);

	showStatus();
}

void ModuleGame::doModeShop() {
	// Gestion des flèches haut et bas pour le menu
	if ((keysDown() & KEY_UP && m_shopSelectedEntry > 0) || (keysDown() & KEY_DOWN && m_shopSelectedEntry + 1 < m_shopMenuEntries.size())) {
		if (keysDown() & KEY_UP && m_shopSelectedEntry > 0) {
			m_shopSelectedEntry--;
		}

		if (keysDown() & KEY_DOWN && m_shopSelectedEntry + 1 < m_shopMenuEntries.size()) {
			m_shopSelectedEntry++;
		}

		// on met le doigt sur la ligne sélectionnée
		m_spriteFinger->setPosY(m_shopSelectedEntry * 8 + 21);
	}

	// Gestion de l'action sélectionnée quand on appuie sur A
	if (keysDown() & KEY_A) {
		if (m_shopCurrentMenu == MENU_GAME_DEFAULT) {
			// ici on est sur le menu principal
			// selon l'option sélectionée on charge le sous-menu correspondant
			if (m_shopMenuEntries.at(m_shopSelectedEntry) == MENU_GAME_SELL_STR) {
				showShop(MENU_GAME_SELL);
			} else if (m_shopMenuEntries.at(m_shopSelectedEntry) == MENU_GAME_BUY_STR) {
				showShop(MENU_GAME_BUY);
			} else if (m_shopMenuEntries.at(m_shopSelectedEntry) == MENU_GAME_QUIT_STR) {
				quitShop();
			}
		}
	}

	// B pour sortir d'un menu
	if (keysDown() & KEY_B) {
		if (m_shopCurrentMenu == MENU_GAME_BUY || m_shopCurrentMenu == MENU_GAME_SELL) {
			showShop(MENU_GAME_DEFAULT);
		} else if (m_shopCurrentMenu == MENU_GAME_DEFAULT) {
			// si on est sur le default on sort
			quitShop();
		}
	}
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

	// on charge les sprites de l'écran du bas
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

	// l'item sélectionné
	m_spriteSelectedItem = new Sprite(SCREEN_SUB, SPRITE_GAME_ITEMS);
	m_spriteSelectedItem->setVisible(false);
	m_spriteSelectedItem->setPos(176, 140);
}

void ModuleGame::initConsoles() {
	// création des consoles
	m_consoleMain = *(GraphicsEngine::getInstance()->getConsole());
	m_consoleDesc = *(GraphicsEngine::getInstance()->getConsole());
	m_consolePrices = *(GraphicsEngine::getInstance()->getConsole());

	consoleSetWindow(&m_consoleMain, 2, 1, 24, 16);
	consoleSetWindow(&m_consoleDesc, 2, 17, 20, 5);

	// on se met sur la console principale
	consoleSelect(&m_consoleMain);
}

/**
 * Initialisation du monde affiché en haut, géré
 * au travers de la classe Map
 */
void ModuleGame::initWorld(MapWarp warp) {
	// création de la map
	m_activeMap = MapFactory::loadMap(warp);
	if (warp.map2 == MAP_FIXED) {
		m_context->setBattleBackground(BG_BATTLE_TOP_FOREST);
	} else {
		m_context->setBattleBackground(BG_BATTLE_TOP_DUNGEON);
	}

	// on crée le sprite du perso à l'écran
	if (m_spritePlayer == NULL) {
		m_spritePlayer = new SpriteChar(SCREEN_MAIN, GraphicsEngine::CreatureClassToGraphicsSprite(m_context->getActiveChar()->getJob(), false));
	}

	// on place le perso sur la position de départ de la map
	Coords coords;
	if (warp.pos2 == Coords(0, 0)) {
		// si la position du perso n'était pas initialisée, on prend la position de départ "absolue" de la map
		coords = m_activeMap->getStartingPos();
	} else {
		// sinon on prend la position du warp
		coords = warp.pos2;
	}

	// le tile du perso fait 32x32
	// on reçoit des coordonnées sur une grille de tiles en 16x16
	// on veut centrer le perso comme ça :
	// ....      les . représentent le sprite du perso en 32x32
	// ....      les x représentent l'emplacement de la tile initiale
	// .xx.      donc par rapport à la coordonnée d'origine
	// .xx.      on retire 8 à X et 16 à Y
	coords.x = coords.x * 16 - AFRODS_GAME_OFFSET_CENTER_CHAR_X;
	coords.y = coords.y * 16 - AFRODS_GAME_OFFSET_CENTER_CHAR_Y;

	m_context->getActiveChar()->setPos(coords);

	// on positionne le sprite et la map
	updatePositions();

	// On affiche la map
	m_activeMap->setVisible(true);

	// On met à jour le perso
	m_spritePlayer->setDefaultAnim();
}

void ModuleGame::updatePositions() {

	if (m_activeMap->getWidth() * 16 <= AFRODS_SCREEN_WIDTH) {
		// si la map est plus petite que l'écran
		m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x);
		m_activeMap->scrollX(0);
	} else {
		// si la map est plus grande que l'écran
		// on calcule les coordonnées où afficher le perso
		if (m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_WIDTH / 2 < AFRODS_SCREEN_WIDTH / 2) {
			// s'il est proche de la gauche, on récupère directement sa position
			m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x);
			m_activeMap->scrollX(0);
		} else if (m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_WIDTH / 2 > ((m_activeMap->getWidth()-1) * 16) - AFRODS_SCREEN_WIDTH / 2) {
			// s'il est proche de la droite, on calcule sa position par rapport à la droite de l'écran
			m_spritePlayer->setPosX(m_context->getActiveChar()->getPosX() - m_activeMap->getOffset().x - ((m_activeMap->getWidth()-1) * 16 - AFRODS_SCREEN_WIDTH));
			m_activeMap->scrollX((m_activeMap->getWidth()-1) * 16 - AFRODS_SCREEN_WIDTH);
		} else {
			// s'il n'est pas près du bord, c'est au centre
			m_spritePlayer->setPosX(AFRODS_SCREEN_WIDTH / 2 - AFRODS_CHAR_WIDTH / 2);
			m_activeMap->scrollX(m_context->getActiveChar()->getPosX()-AFRODS_GAME_OFFSET_CENTER_CHAR_X - AFRODS_SCREEN_WIDTH / 2 + AFRODS_CHAR_WIDTH / 2);
		}
	}

	// TODO voir pourquoi ça marche avec AFRODS_GAME_OFFSET_CENTER_CHAR_X au lieu de AFRODS_GAME_OFFSET_CENTER_CHAR_Y, ça devrait pas !
	if (m_activeMap->getHeight() * 16 <= AFRODS_SCREEN_HEIGHT) {
		// si la map est plus petite que l'écran
		m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y);
		m_activeMap->scrollY(0);
	} else {
		// si la map est plus grande que l'écran
		// on calcule les coordonnées où afficher le perso
		if (m_context->getActiveChar()->getPosY() - AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_HEIGHT / 2 < AFRODS_SCREEN_HEIGHT / 2) {
			// s'il est proche du haut, on récupère directement sa position
			m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y);
			m_activeMap->scrollY(0);
		} else if (m_context->getActiveChar()->getPosY() - AFRODS_GAME_OFFSET_CENTER_CHAR_X + AFRODS_CHAR_HEIGHT / 2 > ((m_activeMap->getHeight()-1) * 16) - AFRODS_SCREEN_HEIGHT / 2) {
			// s'il est proche du bas, on calcule sa position par rapport au bas de l'écran
			m_spritePlayer->setPosY(m_context->getActiveChar()->getPosY() - m_activeMap->getOffset().y - ((m_activeMap->getHeight()-1) * 16 - AFRODS_SCREEN_HEIGHT));
			m_activeMap->scrollY((m_activeMap->getHeight()-1) * 16 - AFRODS_SCREEN_HEIGHT);
		} else {
			// s'il n'est pas près du bord, c'est au centre
			m_spritePlayer->setPosY(AFRODS_SCREEN_HEIGHT / 2 - AFRODS_CHAR_HEIGHT / 2);
			m_activeMap->scrollY(m_context->getActiveChar()->getPosY()-AFRODS_GAME_OFFSET_CENTER_CHAR_X - AFRODS_SCREEN_HEIGHT / 2 + AFRODS_CHAR_HEIGHT / 2);
		}
	}
}

/**
 * Gestion du déplacement du perso, avec scrolling en conséquence
 */
void ModuleGame::moveChar() {
	// si on commence à appuyer, on lance l'animation
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

		// FIXME gérer le déplacement en case par case et non en pixel par pixel
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

	// gestion des warps
	if (keysUp() & KEY_A) {
		if (m_activeMap->isOnWarp(m_context->getActiveChar()->getPos())) {
			// calcul de la tile du perso
			Coords coordsPerso = m_context->getActiveChar()->getPos();
			coordsPerso.x = (coordsPerso.x + AFRODS_MAP_OFFSET_CHAR_LEFT)/16;
			coordsPerso.y = (coordsPerso.y + AFRODS_MAP_OFFSET_CHAR_TOP)/16;

			// on cherche le MapWarp qui se trouve sur cette tile
			MapWarp warp = m_activeMap->findWarp(coordsPerso);
			if (warp != MapWarp()) {
				// on delete la map et on la recrée
				delete m_activeMap;
				initWorld(warp);

				m_spritePlayer->setCurrentDir(DIR_DOWN);
				m_spritePlayer->setDefaultAnim();
				return;
			}
		}
	}
	// si on relâche la direction, on se remet dans la bonne frame
	if (keysUp() & KEY_UP || keysUp() & KEY_DOWN || keysUp() & KEY_LEFT || keysUp() & KEY_RIGHT) {
		m_spritePlayer->setDefaultAnim();
	}

	// gestion du scrolling et du positionnement des sprites
	updatePositions();

}

/**
 * Méthode appelée lorsqu'on veut quitter le jeu
 */
void ModuleGame::quit() {
	// on indique qu'on veut sortir pour aller dans le module Splash
	m_context->switchModule(MODULE_SPLASH, false);
}

/**
 * Affiche les stats du personnage. Correspond à l'icône "Status" du menu
 */
void ModuleGame::showStatus() {
	consoleSelect(&m_consoleMain);

	// on efface l'écran
	iprintf("\x1b[2J");

	iprintf("\x1b[0;7H  STATUS");
	iprintf("\n\n");

	// nom du perso
	iprintf("Name : %s\n", m_context->getActiveChar()->getName().c_str());

	// Classe et Level
	iprintf("%s Level %d\n", CreaturePlayer::translateJob(m_context->getActiveChar()->getJob()).c_str(), m_context->getActiveChar()->getLevel());

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
	iprintf("\x1b[4;11HNEXT : %ld", Creature::XpForNextLevel(m_context->getActiveChar()->getExperience()));
}

/**
 * Affiche l'inventaire du personnage. Correspond à l'icône "Inventory" du menu
 */
void ModuleGame::showInventory() {
	// on se met sur la console principale
	consoleSelect(&m_consoleMain);

	// on efface l'écran
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
 * Affiche l'équipement du personnage. Correspond à l'icône "Equipment" du menu
 */
void ModuleGame::showEquipment() {
	// on se met sur la console principale
	consoleSelect(&m_consoleMain);

	// on efface l'écran
	iprintf("\x1b[2J");
	iprintf("\x1b[0;7H EQUIPMENT");

	iprintf("\n\n");

	// on parcourt l'inventaire
	for (int i = 0 ; i < SLOT_SIZE ; i++) {
		EquipmentSlot slot = (EquipmentSlot)i;
		Item * item = m_context->getActiveChar()->getEquipmentItem(slot);

		std::string sText = Creature::translateSlot(slot, true) + ":";

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
		iprintf("Slot : %s\n", Creature::translateSlot((EquipmentSlot)m_selectedEntry).c_str());
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

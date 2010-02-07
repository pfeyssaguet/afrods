// custom includes
#include "modulemenu.h"
#include "save.h"
#include "constants.h"
#include "context.h"

// standard includes
#include <nds.h>
#include <stdio.h>

using namespace AfroDS;

/**
 * Constructeur du module Menu
 */
ModuleMenu::ModuleMenu(Context * context) : Module(context), m_iOffset(0) {
	m_spriteMenuButton = NULL;
	for (int i = 0 ; i < 4 ; i++) {
		m_spriteMenuIcons[i] = NULL;
	}
	m_spriteMenuArrowDown = NULL;
	m_spriteMenuArrowUp = NULL;

	// chargement du background du haut
	m_bg_top = new Background(SCREEN_MAIN, AFRODS_LAYER_MENU_TOP_BG, BG_MENU_TOP);

	// chargement du background du bas
	// background du bas différent selon le nombre de persos
	switch (Save::getInstance()->getNbCreatures()) {
		case 0:
			// on charge un fond avec 1 entrée de menu pour "Nouveau perso"
			m_iNbMenus = 1;
			m_bg_bottom = new Background(SCREEN_SUB, AFRODS_LAYER_MENU_BOTTOM_BG, BG_MENU_BOTTOM01);
			break;
		case 1:
			// on charge un fond avec 2 entrée de menu, une pour "Nouveau perso"
			// et la seconde pour le 1er perso, et ainsi de suite...
			m_iNbMenus = 2;
			m_bg_bottom = new Background(SCREEN_SUB, AFRODS_LAYER_MENU_BOTTOM_BG, BG_MENU_BOTTOM02);
			break;
		case 2:
			// on charge un fond avec 3 entrées de menu
			m_iNbMenus = 3;
			m_bg_bottom = new Background(SCREEN_SUB, AFRODS_LAYER_MENU_BOTTOM_BG, BG_MENU_BOTTOM03);
			break;
		default:
			// au-delà de 3 persos, on voit 4 entrées de menu, ce qui est le maximum
			m_iNbMenus = 4;
			m_bg_bottom = new Background(SCREEN_SUB, AFRODS_LAYER_MENU_BOTTOM_BG, BG_MENU_BOTTOM04);
			break;
	}

	// on crée la liste

	// on se place sur l'entrée de menu "Nouveau perso"
	selectEntry(AFRODS_MENU_SELECTED_1);

	// on crée les flèches pour défiler
	if (Save::getInstance()->getNbCreatures() > 3) {
		m_spriteMenuArrowUp = new Sprite(SCREEN_SUB, SPRITE_MENU_ICONS);
		m_spriteMenuArrowUp->setPos(AFRODS_MENU_ARROWS_X, AFRODS_MENU_ARROW_UP_Y);
		m_spriteMenuArrowUp->setCurrentFrame(FRAME_ICON_ARROW_UP_OFF);

		m_spriteMenuArrowDown = new Sprite(SCREEN_SUB, SPRITE_MENU_ICONS);
		m_spriteMenuArrowDown->setPos(AFRODS_MENU_ARROWS_X, AFRODS_MENU_ARROW_DOWN_Y);
		m_spriteMenuArrowDown->setCurrentFrame(FRAME_ICON_ARROW_DOWN_OFF);
	}
	listChars();
}

/**
 * Nettoyage du module
 */
ModuleMenu::~ModuleMenu() {
	iprintf("\x1b[2J");

	if (m_spriteMenuButton != NULL)
		delete m_spriteMenuButton;
	for (int i = 0 ; i < 4 ; i++) {
		if (m_spriteMenuIcons[i] != NULL)
			delete m_spriteMenuIcons[i];
	}
	if (m_spriteMenuArrowDown != NULL)
		delete m_spriteMenuArrowDown;
	if (m_spriteMenuArrowUp != NULL)
		delete m_spriteMenuArrowUp;

	delete m_bg_top;
	delete m_bg_bottom;
}

/**
 * Affiche une ligne de texte dans le menu
 */
void ModuleMenu::printEntry(int iEntry, GraphicsSprite graphics, std::string sText) {
	// on calcule une box pour afficher le texte
	Coords pos, taille;
	pos.x = AFRODS_MENU_BOX_OFFSET_X + AFRODS_CHAR_WIDTH + 8;
	pos.y = AFRODS_MENU_BOX_OFFSET_Y + 8 + ((iEntry - 1) * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE));
	taille.x = pos.x + AFRODS_MENU_BOX_WIDTH;
	taille.y = pos.y + AFRODS_MENU_BOX_HEIGHT;

	// on écrit le texte
	iprintf("\x1b[%d;7H%s", 1 + pos.y / 8, sText.c_str());

	// on (re)crée le sprite
	if (m_spriteMenuIcons[iEntry - 1] != NULL) {
		delete m_spriteMenuIcons[iEntry - 1];
	}
	m_spriteMenuIcons[iEntry - 1] = new Sprite(SCREEN_SUB, graphics);
	m_spriteMenuIcons[iEntry - 1]->setPriority(0);
	Coords position;
	position.x = AFRODS_MENU_BOX_OFFSET_X;
	position.y = AFRODS_MENU_BOX_OFFSET_Y + ((iEntry - 1) * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE));
	if (iEntry > 1)
		position.y -= AFRODS_MENU_OFFSET_CHAR;

	m_spriteMenuIcons[iEntry - 1]->setPos(position);

	if (iEntry > 1) {
		m_spriteMenuIcons[iEntry - 1]->setCurrentFrame(7);
	}
}

/**
 * Affiche la liste des persos sur l'écran
 */
void ModuleMenu::listChars() {
	iprintf("\x1b[2J");
	for (int i = 0 ; i < 4 ; i++) {
		if (m_spriteMenuIcons[i] != NULL) {
			delete m_spriteMenuIcons[i];
			m_spriteMenuIcons[i] = NULL;
		}
	}

	// on crée l'entrée "Nouveau perso"
	printEntry(1, SPRITE_MENU_ICONS, "NEW CHARACTER");

	// on crée les 3 entrées suivantes
	if (Save::getInstance()->getNbCreatures() > 0) {
		for (int i = 1; i <= 3; i++) {
			// Récupération du perso
			CreaturePlayer * charac = Save::getInstance()->getCreature(i-1 + m_iOffset);

			// on affiche le nom du perso
			printEntry(i + 1, GraphicsEngine::CreatureClassToGraphicsSprite(charac->getJob(), false), charac->getName());
			// si on a plus de persos, on sort
			if (Save::getInstance()->getNbCreatures() - i - m_iOffset == 0)
				break;
		}
	}
}

/**
 * Sélectionne une entrée dans le menu en créant les 3 sprites qui composent un menu sélectionné
 * @param int numéro de l'entrée à sélectionner (1-4)
 */
void ModuleMenu::selectEntry(int iMenu) {
	// on positionne le menu courant
	m_iActiveMenu = iMenu;

	// on calcule la position du 1er sprite
	Coords position;
	position.x = AFRODS_MENU_BOX_OFFSET_X;
	position.y = AFRODS_MENU_BOX_OFFSET_Y + ((AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE) * (m_iActiveMenu - 1));

	// si le bouton n'existe pas, on le crée
	if (m_spriteMenuButton == NULL) {
		// on recrée un bouton à la nouvelle position
		m_spriteMenuButton = new SpriteMenuButton(position);
	} else {
		// sinon on le repositionne
		m_spriteMenuButton->setPos(position);
	}
}

/**
 * Gestion des événements du module Menu
 * Surcharge de Module::moduleEvents()
 */
void ModuleMenu::moduleEvents() {
	for (int i = 0 ; i < 4 ; i++) {
		if (m_spriteMenuIcons[i] != NULL)
			m_spriteMenuIcons[i]->update();
	}
	if (m_spriteMenuButton != NULL)
		m_spriteMenuButton->update();
	if (m_spriteMenuArrowUp != NULL)
		m_spriteMenuArrowUp->update();
	if (m_spriteMenuArrowDown != NULL)
		m_spriteMenuArrowDown->update();

	bool pressLaunch = false;
	bool pressDown = false;
	bool pressUp = false;

	// gestion du stylet
	if (keysDown() & KEY_TOUCH) {
		touchPosition touch;
		touchRead(&touch);

		// si on appuie sur l'un des sprites du menu sélectionné, on lance le module
		if (m_spriteMenuButton->isInZone(touch.px, touch.py)) {
			pressLaunch = true;
			// on attend que le stylet soit relâché
			do {
				// on vérifie que le stylet est toujours dans la zone
				if (m_spriteMenuButton->isInZone(touch.px, touch.py)) {
					// on lance le module
					pressLaunch = true;
				} else {
					// on n'est plus dans la zone, on ne lance plus le module
					pressLaunch = false;
				}
				swiWaitForVBlank();
				scanKeys();
				touchRead(&touch);
			} while (keysHeld() & KEY_TOUCH);

			// on lance le module
			if (pressLaunch) {
				launchModule();
				return;
			}
		}

		// si on appuie sur la flèche du haut
		if (m_spriteMenuArrowUp != NULL && m_spriteMenuArrowUp->isInZone(touch.px, touch.py)) {
			pressUp = true;
			// on change l'animation de la flèche
			m_spriteMenuArrowUp->setCurrentFrame(FRAME_ICON_ARROW_UP_ON);
			// on attend que le stylet soit relâché
			do {
				// on vérifie que le stylet est toujours dans la zone
				// on choisit la bonne frame
				if (m_spriteMenuArrowUp->getCurrentFrame() == FRAME_ICON_ARROW_UP_OFF
					&& m_spriteMenuArrowUp->isInZone(touch.px, touch.py)) {
					// on était plus dans la zone et on vient d'y revenir
					m_spriteMenuArrowUp->setCurrentFrame(FRAME_ICON_ARROW_UP_ON);
					pressUp = true;
				} else if (m_spriteMenuArrowUp->getCurrentFrame() == FRAME_ICON_ARROW_UP_ON
					&& !m_spriteMenuArrowUp->isInZone(touch.px, touch.py)) {
					// on était dans la zone et on vient d'en sortir
					m_spriteMenuArrowUp->setCurrentFrame(FRAME_ICON_ARROW_UP_OFF);
					pressUp = false;
				}
				swiWaitForVBlank();
				scanKeys();
				touchRead(&touch);
			} while (keysHeld() & KEY_TOUCH);
			m_spriteMenuArrowUp->setCurrentFrame(FRAME_ICON_ARROW_UP_OFF);
		}

		// si on appuie sur la flèche du bas
		if (m_spriteMenuArrowDown != NULL && m_spriteMenuArrowDown->isInZone(touch.px, touch.py)) {
			pressDown = true;
			m_spriteMenuArrowDown->setCurrentFrame(FRAME_ICON_ARROW_DOWN_ON);
			do {
				// on vérifie que le stylet est toujours dans la zone
				// on choisit la bonne frame
				if (m_spriteMenuArrowDown->getCurrentFrame() == FRAME_ICON_ARROW_DOWN_OFF
					&& m_spriteMenuArrowDown->isInZone(touch.px, touch.py)) {
					// on était plus dans la zone et on vient d'y revenir
					m_spriteMenuArrowDown->setCurrentFrame(FRAME_ICON_ARROW_DOWN_ON);
					pressDown = true;
				} else if (m_spriteMenuArrowDown->getCurrentFrame() == FRAME_ICON_ARROW_DOWN_ON
					&& !m_spriteMenuArrowDown->isInZone(touch.px, touch.py)) {
					// on était dans la zone et on vient d'en sortir
					m_spriteMenuArrowDown->setCurrentFrame(FRAME_ICON_ARROW_DOWN_OFF);
					pressDown = false;
				}
				swiWaitForVBlank();
				scanKeys();
				touchRead(&touch);
			} while (keysHeld() & KEY_TOUCH);
			m_spriteMenuArrowDown->setCurrentFrame(FRAME_ICON_ARROW_DOWN_OFF);
		}

		// si on appuie dans la zone d'un autre menu que le menu courant, on sélectionne l'entrée correspondante
		for (int i = 0; i < 4; i++) {
			if (m_iNbMenus >= i + 1) {
				Coords coords;
				coords.x = AFRODS_MENU_BOX_OFFSET_X;
				coords.y = AFRODS_MENU_BOX_OFFSET_Y + (i * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE));

				if (touch.px >= coords.x && touch.px <= coords.x + AFRODS_MENU_BOX_WIDTH && touch.py >= coords.y
					&& touch.py <= coords.y + AFRODS_MENU_BOX_HEIGHT) {
					// on sélectionne l'entrée correspondant à i
					selectEntry(i + 1);
				}
			}
		}
	}

	if (keysDown() & KEY_DOWN) {
		pressDown = true;
	}
	if (keysDown() & KEY_UP) {
		pressUp = true;
	}

	// si on est sur la dernière ligne et qu'on descend
	if (pressDown && m_iActiveMenu == 4 && Save::getInstance()->getNbCreatures() > m_iActiveMenu - 1 + m_iOffset) {
		m_iOffset++;
		listChars();
	} else
	// si on est sur la 2e ligne, qu'on a un offset et qu'on remonte
	if (pressUp && m_iActiveMenu == 2 && m_iOffset > 0) {
		m_iOffset--;
		listChars();
	} else
	// si on monte on change la ligne sélectionnée
	if (pressUp && m_iActiveMenu > 1) {
		selectEntry(m_iActiveMenu - 1);
	}
	// si on descend on change la ligne sélectionnée
	if (pressDown && m_iActiveMenu < m_iNbMenus) {
		selectEntry(m_iActiveMenu + 1);
	}

	// en cas d'appui sur A, on lance l'entrée sélectionnée
	if (keysDown() & KEY_A) {
		launchModule();
	}
}

/**
 * Lance le module qui va bien
 */
void ModuleMenu::launchModule() {
	// si on est sur l'entrée nouveau perso
	if (m_iActiveMenu == AFRODS_MENU_SELECTED_1) {
		// on va dans le module de création de perso
		m_context->switchModule(MODULE_NEWCHAR, false);
	} else {
		// on sélectionne le perso
		if (m_context->getActiveChar() != NULL) {
			delete m_context->getActiveChar();
		}

		// m_iActiveMenu -2 : car le perso 0 est sur le menu 2, le perso 1 est sur le menu 3, etc
		m_context->setActiveChar(Save::getInstance()->getCreature(m_iOffset + m_iActiveMenu - 2));

		// on va dans le module Game
		m_context->switchModule(MODULE_GAME, false);
	}
}


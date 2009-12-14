#include "menu.h"
#include "save.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

using namespace AfroDS;

/**
 * Constructeur du module Menu
 */
Menu::Menu() : m_iActiveMenu(AFRODS_MENU_SELECTED_1), m_iNbMenus(1), m_iOffset(0) {
	// initialisation pour la police en smart
	PA_Init8bitBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_8BIT); // init du bg 8bit
	PA_SetBgPrio(ECRAN_BAS, AFRODS_LAYER_BOTTOM_8BIT, 0); // on le passe au 1er plan

	// on charge la palette de la police
	PA_Load8bitBgPal(ECRAN_BAS, (void*)bg_font_menu_Pal); // chargement de la palette des polices du menu
	PA_8bitCustomFont(AFRODS_FONT_MENU, bg_font_menu);

	// on charge la palette du menu
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_BOTTOM_MENU, (void*)palMenu_Pal);

	// on charge la palette du personnage
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_BOTTOM_PERSO, (void*)palPerso_Pal);

	// on charge les 2 backgrounds
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_menu_top);

	// background du bas différent selon le nombre de persos
	switch (G_Env.save->getNbCharacters()) {
		case 0:
			// on charge un fond avec 1 entrée de menu pour "Nouveau perso"
			m_iNbMenus = 1;
			PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_menu_bottom_01);
			break;
		case 1:
			// on charge un fond avec 2 entrée de menu, une pour "Nouveau perso"
			// et la seconde pour le 1er perso, et ainsi de suite...
			m_iNbMenus = 2;
			PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_menu_bottom_02);
			break;
		case 2:
			// on charge un fond avec 3 entrées de menu
			m_iNbMenus = 3;
			PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_menu_bottom_03);
			break;
		default:
			// au-delà de 3 persos, on voit 4 entrées de menu, ce qui est le maximum
			m_iNbMenus = 4;
			PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_menu_bottom_04);
			break;
	}

	// on crée la liste
	listChars();

	// on se place sur l'entrée de menu "Nouveau perso"
	selectEntry(m_iActiveMenu);
}

/**
 * Nettoyage du module
 */
Menu::~Menu() {
	PA_ResetBgSys();
	PA_ResetSpriteSys();
}

/**
 * Affiche une ligne de texte dans le menu
 */
void Menu::printEntry(int iEntry, std::string sText) {
	// on calcule une box pour afficher le texte
	Coords position, taille;
	position.x = AFRODS_MENU_BOX_OFFSET_X + AFRODS_GAME_PERSO_WIDTH + 8;
	position.y = AFRODS_MENU_BOX_OFFSET_Y + 8 + ((iEntry-1) * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE));
	taille.x = position.x + AFRODS_MENU_BOX_WIDTH;
	taille.y = position.y + AFRODS_MENU_BOX_HEIGHT;

	// on a besoin d'un char * et string::c_str() nous renvoie un const char *
	// donc on doit copier cette chaîne dans un char * pour le passer à PA_SmartText()
	size_t size = sText.size() + 1;
	char * buffer = new char[size];

	// copier la chaîne
	strncpy(buffer, sText.c_str(), size);

	// on écrit le nom du perso
	PA_SmartText(ECRAN_BAS,
		position.x, position.y,
		taille.x, taille.y,
		buffer,
		1, AFRODS_FONT_MENU, 1, 100
	);

	// libérer la mémoire
	delete [] buffer;
}

/**
 * Affiche la liste des persos sur l'écran
 */
void Menu::listChars() {

	// on crée le sprite pour "nouveau perso"
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1, (void*) spr_menu_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_BOTTOM_MENU,
			AFRODS_MENU_BOX_OFFSET_X,
			AFRODS_MENU_BOX_OFFSET_Y);

	// on crée l'entrée "Nouveau perso"
	printEntry(1, "NEW CHARACTER");

	// on crée les 3 entrées suivantes
	if (G_Env.save->getNbCharacters() > 0) {
		for (int i = 1 ; i <= 3 ; i++) {
			// on calcule la position du sprite
			Coords position;
			position.x = AFRODS_MENU_BOX_OFFSET_X;
			position.y = AFRODS_MENU_BOX_OFFSET_Y + (i * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE)) - AFRODS_MENU_OFFSET_CHAR;
			// on affiche le sprite du perso
			PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1 + i, (void*)spr_perso_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_BOTTOM_PERSO, position.x, position.y);
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1 + i, 7); // la frame 7 correspond au perso de face

			// on affiche le nom du perso
			printEntry(i+1, G_Env.save->getCharacter(i-1).getName());
			// si on a plus de persos, on sort
			if (G_Env.save->getNbCharacters() - i == 0)
				break;
		}
	}

	// on crée les flèches pour défiler
	if (G_Env.save->getNbCharacters() > 3) {
		PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, (void*)spr_menu_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_BOTTOM_MENU, AFRODS_MENU_ARROWS_X, AFRODS_MENU_ARROW_UP_Y);
		PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, AFRODS_MENU_FRAME_ICON_ARROW_UP_OFF);

		PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, (void*)spr_menu_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_BOTTOM_MENU, AFRODS_MENU_ARROWS_X, AFRODS_MENU_ARROW_DOWN_Y);
		PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, AFRODS_MENU_FRAME_ICON_ARROW_DOWN_OFF);
	}
}

/**
 * Sélectionne une entrée dans le menu en créant les 3 sprites qui composent un menu sélectionné
 * @param int numéro de l'entrée à sélectionner (1-4)
 */
void Menu::selectEntry(int iMenu) {
	// on positionne le menu courant
	m_iActiveMenu = iMenu;

	// on calcule la position du 1er sprite
	Coords position;
	position.x = AFRODS_MENU_BOX_OFFSET_X;
	position.y = AFRODS_MENU_BOX_OFFSET_Y + ((AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE) * (m_iActiveMenu - 1));

	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, (void*) spr_menu_button_Sprite, OBJ_SIZE_64X32, 1, AFRODS_PAL_BOTTOM_MENU, position.x, position.y);
	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, AFRODS_LAYER_BOTTOM_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, AFRODS_MENU_FRAME_SELECT_1);

	position.x += 64;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, (void*) spr_menu_button_Sprite, OBJ_SIZE_64X32, 1, AFRODS_PAL_BOTTOM_MENU, position.x, position.y);
	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, AFRODS_LAYER_BOTTOM_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, AFRODS_MENU_FRAME_SELECT_2);

	position.x += 64;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, (void*) spr_menu_button_Sprite, OBJ_SIZE_64X32, 1, AFRODS_PAL_BOTTOM_MENU, position.x, position.y);
	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, AFRODS_LAYER_BOTTOM_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, AFRODS_MENU_FRAME_SELECT_3);
}

/**
 * Déselectionne l'entrée de menu sélectionnée en supprimant
 * les 3 sprites qui composent un menu sélectionné
 */
void Menu::selectNothing() {
	// on supprime les sprites qu'on a utilisés
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3);
}

/**
 * Gestion des événements du module Menu
 * Surcharge de Module::moduleEvents()
 */
void Menu::moduleEvents() {
	// si on appuie sur l'un des sprites du menu sélectionné, on lance le module
	if (PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_1) ||
		PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_2) ||
		PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_3)) {

		PA_WaitFor(Stylus.Released);
		launchModule();
		return;
	}

	// gestion du stylet
	if (Stylus.Held) {
		for (int i = 0 ; i < 4 ; i++) {
			Coords position;
			position.x = AFRODS_MENU_BOX_OFFSET_X;
			position.y = AFRODS_MENU_BOX_OFFSET_Y + (i * (AFRODS_MENU_BOX_HEIGHT + AFRODS_MENU_BOX_SPACE));
			if (PA_StylusInZone(
					position.x, position.y,
					position.x + AFRODS_MENU_BOX_WIDTH, position.y + AFRODS_MENU_BOX_HEIGHT)) {
				if (m_iNbMenus >= i + 1) {
					PA_WaitFor(Stylus.Released);
					selectNothing();
					m_iActiveMenu = i + 1;
					selectEntry(m_iActiveMenu);
				}
			}
		}
	}

	// si on est sur la dernière ligne et qu'on descend
	if ((PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_DOWN) || Pad.Newpress.Down) && m_iActiveMenu == 4 && G_Env.save->getNbCharacters() > m_iActiveMenu - 1 + m_iOffset) {
		if (PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_DOWN)) {
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, AFRODS_MENU_FRAME_ICON_ARROW_DOWN_ON);
			PA_WaitFor(Stylus.Released);
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, AFRODS_MENU_FRAME_ICON_ARROW_DOWN_OFF);
		}
		m_iOffset++;
		PA_Clear8bitBg(ECRAN_BAS);
		// on crée l'entrée "Nouveau perso"
		printEntry(1, "NEW CHARACTER");
		// on crée les 3 entrées suivantes
		for (int i = 1 ; i <= 3 ; i++) {
			printEntry(i + 1, G_Env.save->getCharacter(i - 1 + m_iOffset).getName());
		}
	}
	else
	// si on est sur la 2e ligne et qu'on remonte
	if ((PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_UP) || Pad.Newpress.Up) && m_iActiveMenu == 2 && m_iOffset > 0) {
		if (PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_UP)) {
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, AFRODS_MENU_FRAME_ICON_ARROW_UP_ON);
			PA_WaitFor(Stylus.Released);
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, AFRODS_MENU_FRAME_ICON_ARROW_UP_OFF);
		}
		m_iOffset--;
		PA_Clear8bitBg(ECRAN_BAS);
		// on crée l'entrée "Nouveau perso"
		printEntry(1, "NEW CHARACTER");
		// on crée les 3 entrées suivantes
		for (int i = 1 ; i <= 3 ; i++) {
			printEntry(i + 1, G_Env.save->getCharacter(i - 1 + m_iOffset).getName());
		}
	}
	else
	// si on descend on change la ligne sélectionnée
	if (((PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_UP) || Pad.Newpress.Up) && m_iActiveMenu > 1) ||
			((PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_DOWN) || Pad.Newpress.Down) && m_iActiveMenu < m_iNbMenus)) {

		if (PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_DOWN)) {
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, AFRODS_MENU_FRAME_ICON_ARROW_DOWN_ON);
			PA_WaitFor(Stylus.Released);
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_DOWN, AFRODS_MENU_FRAME_ICON_ARROW_DOWN_OFF);
			selectNothing();
			m_iActiveMenu++;
		} else if (PA_SpriteTouched(AFRODS_SPRITE_MENU_ARROW_UP)) {
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, AFRODS_MENU_FRAME_ICON_ARROW_UP_ON);
			PA_WaitFor(Stylus.Released);
			PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_ARROW_UP, AFRODS_MENU_FRAME_ICON_ARROW_UP_OFF);
			selectNothing();
			m_iActiveMenu--;
		} else {
			selectNothing();
			m_iActiveMenu += Pad.Newpress.Down - Pad.Newpress.Up;
		}

		selectEntry(m_iActiveMenu);
	}

	// en cas d'appui sur A, on lance l'entrée sélectionnée
	if (Pad.Newpress.A) {
		launchModule();
	}
}

/**
 * Lance le module qui va bien
 */
void Menu::launchModule() {
	// on indique qu'on veut sortir
	m_bIsStopped = true;

	// si on est sur l'entrée nouveau perso
	if (m_iActiveMenu == AFRODS_MENU_SELECTED_1) {
		// on va dans le module de création de perso
		G_Env.NextModule = AFRODS_MODULE_NEWCHAR;
	} else {
		// on sélectionne le perso
		// m_iActiveMenu -2 : car le perso 0 est sur le menu 2, le perso 1 est sur le menu 3, etc
		G_Env.ActiveChar = G_Env.save->getCharacter(m_iOffset + m_iActiveMenu - 2);

		// on va dans le module Game
		G_Env.NextModule = AFRODS_MODULE_GAME;
	}
}


#include "menu.h"

using namespace std;

/**
 * Constructeur du module Menu
 */
Menu::Menu() : m_iActiveMenu(AFRODS_MENU_SELECTED_1), m_iNbMenus(1), m_save(NULL) {
	// récupération d'une référence sur save
	m_save = G_Env.save;

	// on charge la palette du menu
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_MENU, (void*)palMenu_Pal);

	// on charge la palette du personnage
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_PERSO, (void*)palPerso_Pal);

	// on charge les 2 backgrounds
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_BG, bg_menu_top);

	// background du bas différent selon le nombre de persos
	int iNbPersos = m_save->getNbCharacters();

	switch (iNbPersos) {
	case 0:
		// on charge un fond avec 1 entrée de menu pour "Nouveau perso"
		m_iNbMenus = 1;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_01);
		break;
	case 1:
		// on charge un fond avec 2 entrée de menu, une pour "Nouveau perso"
		// et la seconde pour le 1er perso, et ainsi de suite...
		m_iNbMenus = 2;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_02);
		break;
	case 2:
		// on charge un fond avec 3 entrées de menu
		m_iNbMenus = 3;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_03);
		break;
	default:
		// au-delà de 3 persos, on voit 4 entrées de menu, ce qui est le maximum
		m_iNbMenus = 4;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_04);
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
	// on déselectionne l'entrée de menu
	selectNothing();

	// on supprime les sprites du menu
	for (int i = 0 ; i < m_iNbMenus ; i++) {
		PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1 + i);
	}

	// on vide le texte
	PA_ClearTextBg(ECRAN_BAS);

	// on vide les backgrounds
	PA_ClearBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	PA_ClearBg(ECRAN_BAS, AFRODS_LAYER_BG);
}

/**
 * Affiche la liste des persos sur l'écran
 * FIXME Menu : liste des persos pas gérée si plus de 3 personnages
 */
void Menu::listChars() {
	// on crée l'entrée "Nouveau perso"
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1,
			(void*) spr_menu_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_MENU, 32, 16);
	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1, AFRODS_LAYER_SPRITES);

	// TODO Menu : refaire le PA_OutputText
	PA_SetTextCol(ECRAN_BAS, 0, 0, 0);
	PA_OutputText(ECRAN_BAS, 8, 3, "New character");

	// on crée les 3 entrées suivantes
	vector<Character> persos = m_save->getCharacters();
	Character charac;

	if (!persos.empty()) {
		for (int i = 1 ; i <= 3 ; i++) {
			int iNumSprite = AFRODS_SPRITE_MENU_ICON_1 + i;
			// on affiche le sprite du perso
			PA_CreateSprite(ECRAN_BAS, iNumSprite, (void*)spr_perso_Sprite,
					OBJ_SIZE_32X32, 1, AFRODS_PAL_PERSO, 32, 12 + (i * 42));
			PA_SetSpritePrio(ECRAN_BAS, iNumSprite, AFRODS_LAYER_SPRITES);

			// la frame 7 correspond au perso de face
			// TODO Menu : système d'affichage du graphisme à revoir
			PA_SetSpriteAnim(ECRAN_BAS, iNumSprite, 7);

			// TODO Menu : refaire le PA_OutputText
			charac = persos[i-1];
			PA_OutputText(ECRAN_BAS, 8, 3 + (i * 6), charac.getName().c_str());

			if (persos.size() - i == 0)
				break;
		}
	}
}

/**
 * Sélectionne une entrée dans le menu
 * @param int numéro de l'entrée à sélectionner (1-4)
 */
void Menu::selectEntry(int iMenu) {
	AF_Coords position;

	m_iActiveMenu = iMenu;
	// TODO Menu : positions des items de menu à régler précisément
	switch (m_iActiveMenu) {
	default:
	case AFRODS_MENU_SELECTED_1:
		position.y = 16;
		break;
	case AFRODS_MENU_SELECTED_2:
		position.y = 60;
		break;
	case AFRODS_MENU_SELECTED_3:
		position.y = 104;
		break;
	case AFRODS_MENU_SELECTED_4:
		position.y = 148;
		break;
	}

	position.x = 32;

	// on crée les sprites à l'écran
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1,
			(void*) spr_menu_Sprite, OBJ_SIZE_64X32, 1, AFRODS_PAL_MENU, position.x, position.y);

	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, AFRODS_LAYER_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, AFRODS_MENU_FRAME_NEWCHAR_1);

	position.x += 64;

	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2,
			(void*)spr_menu_Sprite, OBJ_SIZE_64X32,
			1, AFRODS_PAL_MENU, position.x, position.y);

	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, AFRODS_LAYER_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, AFRODS_MENU_FRAME_NEWCHAR_2);

	position.x += 64;

	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3,
			(void*)spr_menu_Sprite, OBJ_SIZE_64X32,
			1, AFRODS_PAL_MENU, position.x, position.y);

	PA_SetSpritePrio(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, AFRODS_LAYER_SPRITES);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, AFRODS_MENU_FRAME_NEWCHAR_3);
}

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
	// si on appuie sur le stylet
	if (PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_1) ||
		PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_2) ||
		PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_3)) {

		launchModule();
	}

	// si on descend on change la ligne sélectionnée
	if (Pad.Newpress.Down || Pad.Newpress.Up) {
		if ((Pad.Newpress.Up && m_iActiveMenu > 1) || (Pad.Newpress.Down && m_iActiveMenu < m_iNbMenus)) {
			selectNothing();
			m_iActiveMenu += Pad.Newpress.Down - Pad.Newpress.Up;
			selectEntry(m_iActiveMenu);
		}

		// TODO Menu : gestion du défilement à mettre en place au delà de 3 persos
	}
	// en cas d'appui sur A, on lance le module
	if (Pad.Newpress.A)
		launchModule();
}

/**
 * Lance le module qui va bien
 */
void Menu::launchModule() {
	// on indique qu'on veut sortir
	m_bIsStopped = true;

	// pour aller dans le module Game
	//G_Env.NextModule = AFRODS_MODULE_GAME;
	G_Env.NextModule = AFRODS_MODULE_NEWCHAR;
}


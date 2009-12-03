#include "menu.h"

/**
 * Initialisation du module Menu
 */
void AF_MenuInit() {
	// On indique qu'on se trouve dans le menu
	G_Env.Module = AFRODS_MODULE_MENU;
	G_Env.ModuleStop = FALSE;

	G_Env.Menu.iActiveMenu = AFRODS_MENU_SELECTED_NONE;

	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);

	// on charge les 2 backgrounds
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_BG, bg_menu_top);

	// background du bas si on a pas de perso
	int iNbPersos = AF_SavePersoCount();

	switch (iNbPersos) {
	case 0:
		G_Env.Menu.iNbMenus = 1;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_01);
		break;
	case 1:
		G_Env.Menu.iNbMenus = 2;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_02);
		break;
	case 2:
		G_Env.Menu.iNbMenus = 3;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_03);
		break;
	default:
		G_Env.Menu.iNbMenus = 4;
		PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom_04);
		break;
	}

	// on crée la liste
	AF_MenuListChars();

	// on se place sur l'entrée de menu "Nouveau perso"
	//AF_MenuSelect(AFRODS_MENU_SELECTED_3);
}

/**
 * Affiche la liste des persos sur l'écran
 * FIXME Menu : liste des persos pas gérée si plus de 3 personnages
 */
void AF_MenuListChars() {
	// on crée l'entrée "Nouveau perso"
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1,
			(void*) spr_menu_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_MENU, 32, 16);

	// TODO Menu : refaire le PA_OutputText
	PA_SetTextCol(ECRAN_BAS, 0, 0, 0);
	PA_OutputText(ECRAN_BAS, 8, 3, "New character");

	// on crée les 3 entrées suivantes
	AF_SavePerso * perso = G_Env.Save.persos;
	if (perso != NULL) {
		int i;
		for (i = 1 ; i <= 3 ; i++) {
			int iNumSprite = AFRODS_SPRITE_MENU_ICON_1 + i;
			// on affiche le sprite du perso
			PA_CreateSprite(ECRAN_BAS, iNumSprite, (void*)spr_perso_Sprite,
					OBJ_SIZE_32X32, 1, AFRODS_PAL_PERSO, 32, 12 + (i * 42));

			// la frame 7 correspond au perso de face
			// TODO Menu : système d'affichage du graphisme à revoir
			PA_SetSpriteAnim(ECRAN_BAS, iNumSprite, 7);

			// TODO Menu : refaire le PA_OutputText
			PA_OutputText(ECRAN_BAS, 8, 3 + (i * 6), perso->sName);
			perso = perso->next;
			if (perso == NULL)
				break;
		}
	}
}

/**
 * Sélectionne une entrée dans le menu
 * @param int numéro de l'entrée à sélectionner (1-4)
 */
void AF_MenuSelect(int iMenu) {
	int posY;
	int posX;

	G_Env.Menu.iActiveMenu = iMenu;
	// TODO Menu : positions des items de menu à régler précisément
	switch (G_Env.Menu.iActiveMenu) {
	default:
	case AFRODS_MENU_SELECTED_1:
		posY = 16;
		break;
	case AFRODS_MENU_SELECTED_2:
		posY = 58;
		break;
	case AFRODS_MENU_SELECTED_3:
		posY = 102;
		break;
	case AFRODS_MENU_SELECTED_4:
		posY = 154;
		break;
	}

	posX = 32;

	// on crée les sprites à l'écran
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1,
			(void*) spr_menu_Sprite, OBJ_SIZE_64X32, 1, AFRODS_PAL_MENU, posX,posY);

	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1, AFRODS_MENU_FRAME_NEWCHAR_1);

	posX += 64;

	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2,
			(void*)spr_menu_Sprite, OBJ_SIZE_64X32,
			1, AFRODS_PAL_MENU, posX, posY);

	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2, AFRODS_MENU_FRAME_NEWCHAR_2);

	posX += 64;

	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3,
			(void*)spr_menu_Sprite, OBJ_SIZE_64X32,
			1, AFRODS_PAL_MENU, posX, posY);

	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3, AFRODS_MENU_FRAME_NEWCHAR_3);
}

void AF_MenuDeselect() {
	// on supprime les sprites qu'on a utilisés
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_1);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_2);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_SELECT_3);
}

/**
 * Gestion des événements du module Menu
 */
void AF_MenuEvents() {
	// si on appuie sur le stylet
	if (PA_SpriteTouched(AFRODS_SPRITE_MENU_SELECT_1) || PA_SpriteTouched(
			AFRODS_SPRITE_MENU_SELECT_2) || PA_SpriteTouched(
			AFRODS_SPRITE_MENU_SELECT_3)) {

		AF_MenuLaunchModule();
	}

	// en cas d'appui sur A, on lance le module
	if (Pad.Newpress.A)
		AF_MenuLaunchModule();
}

/**
 * Nettoyage du module
 */
void AF_MenuClean() {
	//AF_MenuDeselect();

	// on supprime les sprites du menu
	int i;
	for (i = 0 ; i < G_Env.Menu.iNbMenus ; i++) {
		PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_ICON_1 + i);
	}

	// on vide le texte
	PA_ClearTextBg(ECRAN_BAS);

	// on vide les backgrounds
	PA_ClearBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	PA_ClearBg(ECRAN_BAS, AFRODS_LAYER_BG);
}

/**
 * Lance le module qui va bien
 */
void AF_MenuLaunchModule() {
	// on clean le menu
	AF_MenuClean();
	// on indique qu'on veut sortir
	G_Env.ModuleStop = TRUE;
}


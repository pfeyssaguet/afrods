#include "menu.h"

void AF_MenuInit()
{
	// On indique qu'on se trouve dans le menu
	G_Env.Module = AFRODS_MODULE_MENU;

	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	
	// on charge les 2 backgrounds
	PA_EasyBgLoad(ECRAN_BAS, AFRODS_LAYER_BG, bg_menu_bottom);
	PA_EasyBgLoad(ECRAN_HAUT, AFRODS_LAYER_BG, bg_menu_top);
	
	// on crée les sprites à l'écran
	PA_CreateSprite(ECRAN_BAS, // Screen
				AFRODS_SPRITE_MENU_NEWCHAR_1, // Sprite number
				(void*)spr_menu_Sprite, // Sprite name
				OBJ_SIZE_64X32, // Sprite size
				1, // 256 color mode
				AFRODS_PAL_MENU, // Sprite palette number
				16, 16); // X and Y position on the screen
	
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_1, AFRODS_MENU_FRAME_NEWCHAR_1);
	
	PA_CreateSprite(ECRAN_BAS, // Screen
				AFRODS_SPRITE_MENU_NEWCHAR_2, // Sprite number
				(void*)spr_menu_Sprite, // Sprite name
				OBJ_SIZE_64X32, // Sprite size
				1, // 256 color mode
				AFRODS_PAL_MENU, // Sprite palette number
				80, 16); // X and Y position on the screen
	
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_2, AFRODS_MENU_FRAME_NEWCHAR_2);

	PA_CreateSprite(ECRAN_BAS, // Screen
				AFRODS_SPRITE_MENU_NEWCHAR_3, // Sprite number
				(void*)spr_menu_Sprite, // Sprite name
				OBJ_SIZE_64X32, // Sprite size
				1, // 256 color mode
				AFRODS_PAL_MENU, // Sprite palette number
				144, 16); // X and Y position on the screen
	
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_3, AFRODS_MENU_FRAME_NEWCHAR_3);
	
	// on se place sur l'entrée de menu "Nouveau perso"
}

void AF_MenuEvents()
{
	// en cas d'appui sur A, on lance le jeu
	if (Pad.Newpress.A)
		AF_MenuLaunchGame();
}

void AF_MenuLaunchGame()
{
	// on supprime les sprites qu'on a utilisés
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_1);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_2);
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_MENU_NEWCHAR_3);
	
	AF_GameInit();
}

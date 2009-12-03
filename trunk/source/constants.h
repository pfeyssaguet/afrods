#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// constantes pour identifier les écrans
#define ECRAN_HAUT 1
#define ECRAN_BAS 0

// constantes pour identifier les modules
#define AFRODS_MODULE_SPLASH 1
#define AFRODS_MODULE_MENU 2
#define AFRODS_MODULE_GAME 3

// nom du fichier de sauvegarde
#define AFRODS_SAVE_FILENAME "AfroDS.dat"

// constantes de palettes pour les sprites
#define AFRODS_PAL_MENU 0
#define AFRODS_PAL_MENU_BUTTON 2
#define AFRODS_PAL_PERSO 1

// constantes de numéros de sprites
#define AFRODS_SPRITE_MENU_SELECT_1 0
#define AFRODS_SPRITE_MENU_SELECT_2 1
#define AFRODS_SPRITE_MENU_SELECT_3 2

#define AFRODS_SPRITE_MENU_ICON_1 3
#define AFRODS_SPRITE_MENU_ICON_2 AFRODS_SPRITE_MENU_ICON_1 + 1
#define AFRODS_SPRITE_MENU_ICON_3 AFRODS_SPRITE_MENU_ICON_2 + 1
#define AFRODS_SPRITE_MENU_ICON_4 AFRODS_SPRITE_MENU_ICON_3 + 1

#define AFRODS_SPRITE_PERSO 0

// constantes des numéros de menus : 0 pour aucun menu sélectionné
#define AFRODS_MENU_SELECTED_NONE 0
#define AFRODS_MENU_SELECTED_1 1
#define AFRODS_MENU_SELECTED_2 2
#define AFRODS_MENU_SELECTED_3 3
#define AFRODS_MENU_SELECTED_4 4

// constantes des frames pour le menu
#define AFRODS_MENU_FRAME_SELECT_1 0
#define AFRODS_MENU_FRAME_SELECT_2 1
#define AFRODS_MENU_FRAME_SELECT_3 2
#define AFRODS_MENU_FRAME_NEWCHAR_1 0
#define AFRODS_MENU_FRAME_NEWCHAR_2 1
#define AFRODS_MENU_FRAME_NEWCHAR_3 2

// constantes des layers
#define AFRODS_LAYER_BG 3

#endif

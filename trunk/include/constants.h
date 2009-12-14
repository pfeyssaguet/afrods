#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// constante pour identifier la version
#define AFRODS_VERSION "0.1"

// constantes pour identifier les écrans
#define ECRAN_BAS 0
#define ECRAN_HAUT 1

// constantes pour la taille d'un écran de NDS
#define AFRODS_SCREEN_WIDTH 256
#define AFRODS_SCREEN_HEIGHT 192

// constantes pour identifier les modules
enum AFRODS_MODULE {AFRODS_MODULE_SPLASH, AFRODS_MODULE_MENU, AFRODS_MODULE_NEWCHAR, AFRODS_MODULE_GAME};

// nom du fichier de sauvegarde
#define AFRODS_SAVE_FILENAME "/AfroDS.dat"

// taille du sprite du perso
#define AFRODS_GAME_PERSO_WIDTH 32
#define AFRODS_GAME_PERSO_HEIGHT 32

// décalage des tiles par rapport à l'écran
#define AFRODS_GAME_OFFSET_TILES_X 8
#define AFRODS_GAME_OFFSET_TILES_Y 8


// constantes de numéros de sprites
#define AFRODS_SPRITE_MENU_ICON_1 0
#define AFRODS_SPRITE_MENU_ICON_2 1
#define AFRODS_SPRITE_MENU_ICON_3 2
#define AFRODS_SPRITE_MENU_ICON_4 3
#define AFRODS_SPRITE_MENU_SELECT_1 4
#define AFRODS_SPRITE_MENU_SELECT_2 5
#define AFRODS_SPRITE_MENU_SELECT_3 6
#define AFRODS_SPRITE_MENU_ARROW_UP 7
#define AFRODS_SPRITE_MENU_ARROW_DOWN 8

// constantes de palettes pour les sprites
#define AFRODS_PAL_BOTTOM_MENU 0
#define AFRODS_PAL_BOTTOM_PERSO 1
#define AFRODS_PAL_TOP_PERSO 0
#define AFRODS_PAL_TOP_GAME 1

// constantes pour les polices de caractères
#define AFRODS_FONT_MENU 5

// constantes de numéros de sprites
#define AFRODS_SPRITE_GAME_PERSO 0
#define AFRODS_SPRITE_GAME_ICON_STATUS 1
#define AFRODS_SPRITE_GAME_ICON_INVENTORY 2
#define AFRODS_SPRITE_GAME_ICON_EQUIPMENT 3
#define AFRODS_SPRITE_GAME_ICON_OPTIONS 4
#define AFRODS_SPRITE_GAME_ICON_QUIT 5

#define AFRODS_GAME_ICONS_FRAME_STATUS 0
#define AFRODS_GAME_ICONS_FRAME_INVENTORY 1
#define AFRODS_GAME_ICONS_FRAME_EQUIPMENT 2
#define AFRODS_GAME_ICONS_FRAME_OPTIONS 3
#define AFRODS_GAME_ICONS_FRAME_QUIT 4


// constantes des layers (par ordre de priorité : le 3 est passé devant car 8bit)
#define AFRODS_LAYER_BOTTOM_8BIT 3
#define AFRODS_LAYER_BOTTOM_SPRITES 1
#define AFRODS_LAYER_BOTTOM_KEYBOARD 0
#define AFRODS_LAYER_BOTTOM_BG 2
#define AFRODS_LAYER_TOP_TEXT 0
#define AFRODS_LAYER_TOP_BG 2

#endif

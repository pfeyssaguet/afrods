#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// constante pour identifier la version
#define AFRODS_VERSION "0.1"

// constantes pour identifier les écrans
#define SCREEN_MAIN 1
#define SCREEN_SUB 0

// constantes pour la taille d'un écran de NDS
#define AFRODS_SCREEN_WIDTH 256
#define AFRODS_SCREEN_HEIGHT 192

// taille du sprite du perso
#define AFRODS_CHAR_WIDTH 32
#define AFRODS_CHAR_HEIGHT 32

// pour centrer le perso
#define AFRODS_GAME_OFFSET_CENTER_CHAR_X 8
#define AFRODS_GAME_OFFSET_CENTER_CHAR_Y 16

// constantes des layers : la console prend automatiquement le layer 0 sur le Sub Screen
#define AFRODS_LAYER_SPLASH_TOP_BG 3
#define AFRODS_LAYER_SPLASH_TOP_BOTTOM 3
#define AFRODS_LAYER_MENU_TOP_BG 2
#define AFRODS_LAYER_MENU_BOTTOM_BG 3
#define AFRODS_LAYER_GAME_TOP_MAP_FLOOR 1
#define AFRODS_LAYER_GAME_TOP_MAP_ABOVE 0
#define AFRODS_LAYER_GAME_BOTTOM_BG 3


#endif

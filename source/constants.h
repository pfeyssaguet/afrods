#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// constantes pour identifier les écrans
#define ECRAN_HAUT 1
#define ECRAN_BAS 0

// constantes pour identifier les modules
enum AFRODS_MODULE {AFRODS_MODULE_SPLASH, AFRODS_MODULE_MENU, AFRODS_MODULE_NEWCHAR, AFRODS_MODULE_GAME};

// nom du fichier de sauvegarde
#define AFRODS_SAVE_FILENAME "AfroDS.dat"

// constantes de palettes pour les sprites
#define AFRODS_PAL_MENU 0
#define AFRODS_PAL_MENU_BUTTON 2
#define AFRODS_PAL_PERSO 1

// constantes de numéros de sprites
#define AFRODS_SPRITE_GAME_PERSO 0


// constantes des layers
#define AFRODS_LAYER_BG 3
#define AFRODS_LAYER_TEXT 0
#define AFRODS_LAYER_SPRITES 1

#endif

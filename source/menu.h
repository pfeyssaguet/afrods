#ifndef __MENU_H__
#define __MENU_H__

#include "afrods.h"
#include "save.h"


/**
 * Initialisation du module Menu
 */
void AF_MenuInit();

/**
 * Gestion des événements du module Menu
 */
void AF_MenuEvents();

/**
 * Nettoyage du module
 */
void AF_MenuClean();

/**
 * Affiche la liste des persos sur l'écran
 */
void AF_MenuListChars();

/**
 * Sélectionne une entrée dans le menu
 * @param int numéro de l'entrée à sélectionner (1-4)
 */
void AF_MenuSelect(int);

/**
 * Déselectionne l'entrée sélectionnée dans le menu
 */
void AF_MenuDeselect();

/**
 * Lance le module qui va bien
 */
void AF_MenuLaunchModule();

#endif

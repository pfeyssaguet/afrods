#ifndef __MENU_H__
#define __MENU_H__

#include "afrods.h"
#include "save.h"


/**
 * Initialisation du module Menu
 */
void AF_MenuInit();

/**
 * Gestion des �v�nements du module Menu
 */
void AF_MenuEvents();

/**
 * Nettoyage du module
 */
void AF_MenuClean();

/**
 * Affiche la liste des persos sur l'�cran
 */
void AF_MenuListChars();

/**
 * S�lectionne une entr�e dans le menu
 * @param int num�ro de l'entr�e � s�lectionner (1-4)
 */
void AF_MenuSelect(int);

/**
 * D�selectionne l'entr�e s�lectionn�e dans le menu
 */
void AF_MenuDeselect();

/**
 * Lance le module qui va bien
 */
void AF_MenuLaunchModule();

#endif

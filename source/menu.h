#ifndef __MENU_H__
#define __MENU_H__

#include "module.h"
#include "save.h"
#include "all_gfx.h"
#include "constants.h"
#include "externs.h"
#include <PA9.h>
#include <vector>

// constantes des num�ros de menus : 0 pour aucun menu s�lectionn�
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

// constantes de num�ros de sprites
#define AFRODS_SPRITE_MENU_ICON_1 0
#define AFRODS_SPRITE_MENU_ICON_2 1
#define AFRODS_SPRITE_MENU_ICON_3 2
#define AFRODS_SPRITE_MENU_ICON_4 3
#define AFRODS_SPRITE_MENU_SELECT_1 4
#define AFRODS_SPRITE_MENU_SELECT_2 5
#define AFRODS_SPRITE_MENU_SELECT_3 6


class Menu : public Module {
	public:
		Menu();
		~Menu();

		/**
		 * Gestion des �v�nements du module Menu
		 * Surcharge de Module::moduleEvents()
		 */
		void moduleEvents();

		/**
		 * Affiche la liste des persos sur l'�cran
		 */
		void listChars();

		/**
		 * S�lectionne une entr�e dans le menu
		 * @param int num�ro de l'entr�e � s�lectionner (1-4)
		 */
		void selectEntry(int);

		/**
		 * D�selectionne l'entr�e s�lectionn�e dans le menu
		 */
		void selectNothing();

		/**
		 * Lance le module qui va bien
		 */
		void launchModule();

	private:
		int m_iActiveMenu;
		int m_iNbMenus;
		Save * m_save;
};

#endif

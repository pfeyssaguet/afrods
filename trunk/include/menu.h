#ifndef __MENU_H__
#define __MENU_H__

#include "module.h"
#include <string>

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
#define AFRODS_MENU_FRAME_ICON_ARROW_UP_OFF 1
#define AFRODS_MENU_FRAME_ICON_ARROW_UP_ON 3
#define AFRODS_MENU_FRAME_ICON_ARROW_DOWN_OFF 2
#define AFRODS_MENU_FRAME_ICON_ARROW_DOWN_ON 4

// constantes pour gérer les positions des items de menus
#define AFRODS_MENU_BOX_OFFSET_X 16
#define AFRODS_MENU_BOX_OFFSET_Y 14
#define AFRODS_MENU_BOX_SPACE 12
#define AFRODS_MENU_BOX_WIDTH 192
#define AFRODS_MENU_BOX_HEIGHT 32

// constantes pour gérer les positions des flèches dans le menu
#define AFRODS_MENU_ARROWS_X 220
#define AFRODS_MENU_ARROW_UP_Y 55
#define AFRODS_MENU_ARROW_DOWN_Y 150

#define AFRODS_MENU_OFFSET_CHAR 4

namespace AfroDS {
	/**
	 * Classe Module Menu
	 */
	class Menu : public Module {
		public:
			Menu();
			~Menu();

			/**
			 * Gestion des événements du module Menu
			 * Surcharge de Module::moduleEvents()
			 */
			void moduleEvents();

		private:
			/**
			 * Affiche la liste des persos sur l'écran
			 */
			void listChars();

			/**
			 * Sélectionne une entrée dans le menu
			 * @param int numéro de l'entrée à sélectionner (1-4)
			 */
			void selectEntry(int);

			/**
			 * Déselectionne l'entrée sélectionnée dans le menu
			 */
			void selectNothing();

			/**
			 * Lance le module qui va bien
			 */
			void launchModule();

			/**
			 * Affiche une ligne de texte dans le menu
			 * @param int iEntry numéro de l'entrée de menu (1-4)
			 * @param string sText chaîne à afficher
			 */
			void printEntry(int iEntry, std::string sText);

			/** Le menu actuellement sélectionné */
			int m_iActiveMenu;

			/** Nombre de menus en tout */
			int m_iNbMenus;

			/** Décalage du menu dans le cas où on a plus de 3 persos */
			int m_iOffset;
	};

}

#endif

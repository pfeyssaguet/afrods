#ifndef __MENU_H__
#define __MENU_H__

#include "module.h"
#include <string>

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
#define AFRODS_MENU_FRAME_ICON_ARROW_UP_OFF 1
#define AFRODS_MENU_FRAME_ICON_ARROW_UP_ON 3
#define AFRODS_MENU_FRAME_ICON_ARROW_DOWN_OFF 2
#define AFRODS_MENU_FRAME_ICON_ARROW_DOWN_ON 4

// constantes pour g�rer les positions des items de menus
#define AFRODS_MENU_BOX_OFFSET_X 16
#define AFRODS_MENU_BOX_OFFSET_Y 14
#define AFRODS_MENU_BOX_SPACE 12
#define AFRODS_MENU_BOX_WIDTH 192
#define AFRODS_MENU_BOX_HEIGHT 32

// constantes pour g�rer les positions des fl�ches dans le menu
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
			 * Gestion des �v�nements du module Menu
			 * Surcharge de Module::moduleEvents()
			 */
			void moduleEvents();

		private:
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

			/**
			 * Affiche une ligne de texte dans le menu
			 * @param int iEntry num�ro de l'entr�e de menu (1-4)
			 * @param string sText cha�ne � afficher
			 */
			void printEntry(int iEntry, std::string sText);

			/** Le menu actuellement s�lectionn� */
			int m_iActiveMenu;

			/** Nombre de menus en tout */
			int m_iNbMenus;

			/** D�calage du menu dans le cas o� on a plus de 3 persos */
			int m_iOffset;
	};

}

#endif

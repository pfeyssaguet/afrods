#ifndef __MENU_H__
#define __MENU_H__

#include "module.h"
#include "spritemenubutton.h"
#include "background.h"

#include <string>

// constantes des numéros de menus
#define AFRODS_MENU_SELECTED_1 1
#define AFRODS_MENU_SELECTED_2 2
#define AFRODS_MENU_SELECTED_3 3
#define AFRODS_MENU_SELECTED_4 4

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

// offset vertical du perso à partir de la 2e ligne (négatif)
#define AFRODS_MENU_OFFSET_CHAR 4

namespace AfroDS {
	// frames pour les flèches du menu
	enum FrameIconArrow {
		FRAME_ICON_ARROW_UP_OFF = 1,
		FRAME_ICON_ARROW_DOWN_OFF = 2,
		FRAME_ICON_ARROW_UP_ON = 3,
		FRAME_ICON_ARROW_DOWN_ON = 4
	};

	/**
	 * Classe Module Menu
	 */
	class ModuleMenu : public Module {
		public:
			ModuleMenu(Context * context);
			virtual ~ModuleMenu();

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
			 * Lance le module qui va bien
			 */
			void launchModule();

			/**
			 * Affiche une ligne de texte dans le menu
			 * @param int iEntry numéro de l'entrée de menu (1-4)
			 * @param string sText chaîne à afficher
			 */
			void printEntry(int iEntry, GraphicsSprite graphics, std::string sText);

			/** Le menu actuellement sélectionné */
			int m_iActiveMenu;

			/** Nombre de menus en tout */
			int m_iNbMenus;

			/** Décalage du menu dans le cas où on a plus de 3 persos */
			int m_iOffset;

			int m_bgTop;
			int m_bgBottom;

			Background * m_bg_top;
			Background * m_bg_bottom;

			SpriteMenuButton * m_spriteMenuButton;
			Sprite * m_spriteMenuIcons[4];
			Sprite * m_spriteMenuArrowUp;
			Sprite * m_spriteMenuArrowDown;
	};

}

#endif

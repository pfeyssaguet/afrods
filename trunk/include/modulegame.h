#ifndef __GAME_H__
#define __GAME_H__

#include "module.h"
#include "map.h"
#include "spritechar.h"
#include "spritegameicon.h"
#include "background.h"

// décalage des icônes du menu en bas
#define AFRODS_GAME_OFFSET_ICONS_X 216
#define AFRODS_GAME_OFFSET_ICONS_Y 8
#define AFRODS_GAME_OFFSET_ICONS_SPACE 0

// décalage du doigt vers le haut
#define AFRODS_GAME_OFFSET_FINGER_Y 3

// nombre de lignes dans l'inventaire
#define AFRODS_GAME_INVENTORY_NBLINES 12

namespace AfroDS {

	/**
	 * Permet de gérer les sous-modes qu'on gère dans le module Game.
	 * Cette enum est utilisée par la variable m_gameMode
	 * - MODE_WALK : personnage en train de marcher
	 * - MODE_INVENTORY : mode sélection dans l'inventaire
	 * - MODE_EQUIPMENT : mode sélection dans l'équipement
	 */
	enum GameMode {MODE_WALK, MODE_INVENTORY, MODE_EQUIPMENT, MODE_SHOP};

	/**
	 * Classe Module Game
	 */
	class ModuleGame : public Module {
		public:
			/**
			 * Lancement du module Game, création du niveau
			 */
			ModuleGame(Context * context);

			/**
			 * Destructeur du module, supprime tous les sprites et backgrounds
			 */
			virtual ~ModuleGame();

			/**
			 * Gestion des événements du module Game
			 */
			void moduleEvents();
			void modulePause();
			void moduleResume();

		private:
			/**
			 * Initialisation du menu en bas :
			 * - affichage du background
			 * - affichage des 5 sprites de menu
			 */
			void initMenu();

			/**
			 * Initialisation du monde affiché en haut, géré
			 * au travers de la classe Map
			 */
			void initWorld(MapWarp warp);

			void initConsoles();

			/**
			 * Gestion du déplacement du perso, avec scrolling en conséquence
			 */
			void moveChar();

			/**
			 * Méthode appelée lorsqu'on veut quitter le jeu
			 */
			void quit();

			/**
			 * Gestion du mode MODE_WALK : interactions :
			 * - déplacer le personnage avec les flèches
			 * - activer le mode MODE_INVENTORY en appuyant sur Start
			 * - afficher les stats du personnage en cliquant sur le sprite Status
			 * - afficher l'inventaire en cliquant sur le sprite Inventory
			 * - afficher l'équipement en cliquant sur le sprite Equipment
			 * - quitter le jeu en cliquant sur le sprite Quit
			 * @return bool
			 */
			bool doModeWalk();

			/**
			 * Gestion des modes MODE_INVENTORY et MODE_EQUIPMENT : interactions :
			 * - revenir en mode MODE_WALK en appuyant sur Start
			 * - basculer entre MODE_INVENTORY et MODE_EQUIPMENT en appuyant sur R ou L
			 * - naviguer dans l'inventaire ou l'équipement avec haut/bas
			 * - équiper un item de l'inventaire avec A
			 * - retirer un item de l'équipement avec A
			 */
			void doModeSelection();

			void initShop();

			void doModeShop();

			/**
			 * Affiche les stats du personnage. Correspond à l'icône "Status" du menu
			 */
			void showStatus();

			/**
			 * Affiche l'inventaire du personnage. Correspond à l'icône "Inventory" du menu
			 */
			void showInventory();

			/**
			 * Affiche l'équipement du personnage. Correspond à l'icône "Equipment" du menu
			 */
			void showEquipment();

			void updatePositions();

			void battle();

			/** Console principale */
			PrintConsole m_consoleMain;

			/** Console de description */
			PrintConsole m_consoleDesc;

			PrintConsole m_consolePrices;

			/** Le mode actuel */
			GameMode m_gameMode;

			/** L'entrée sélectionnée en mode Inventory */
			unsigned int m_selectedEntry;

			/** Offset pour l'inventaire */
			int m_offsetInventory;

			std::vector<MapWarp> m_doors;

			/** Représente la map courante dans laquelle évolue le personnage principal */
			Map * m_activeMap;

			/** Le background du bas */
			Background * m_bgBottom;

			/** Sprite du haut : le perso */
			SpriteChar * m_spritePlayer;

			/** Sprites du bas : icône de menu, à droite */
			SpriteGameIcon * m_spriteIconStatus;
			SpriteGameIcon * m_spriteIconInventory;
			SpriteGameIcon * m_spriteIconEquipment;
			SpriteGameIcon * m_spriteIconOptions;
			SpriteGameIcon * m_spriteIconQuit;

			/** le sprite du doigt */
			Sprite * m_spriteFinger;

			/** Le sprite pour l'icône de l'item sélectionné */
			Sprite * m_spriteSelectedItem;
	};
}

#endif

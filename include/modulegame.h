#ifndef __GAME_H__
#define __GAME_H__

#include "module.h"
#include "map.h"
#include "spritechar.h"
#include "spritegameicon.h"
#include "background.h"

// d�calage des ic�nes du menu en bas
#define AFRODS_GAME_OFFSET_ICONS_X 216
#define AFRODS_GAME_OFFSET_ICONS_Y 8
#define AFRODS_GAME_OFFSET_ICONS_SPACE 0

// d�calage du doigt vers le haut
#define AFRODS_GAME_OFFSET_FINGER_Y 3

// nombre de lignes dans l'inventaire
#define AFRODS_GAME_INVENTORY_NBLINES 12

namespace AfroDS {

	/**
	 * Permet de g�rer les sous-modes qu'on g�re dans le module Game.
	 * Cette �num est utilis�e par la variable m_gameMode
	 * - MODE_WALK : personnage en train de marcher
	 * - MODE_INVENTORY : mode s�lection dans l'inventaire
	 * - MODE_EQUIPMENT : mode s�lection dans l'�quipement
	 */
	enum GameMode {MODE_WALK, MODE_INVENTORY, MODE_EQUIPMENT};

	/**
	 * Classe Module Game
	 */
	class ModuleGame : public Module {
		public:
			/**
			 * Lancement du module Game, cr�ation du niveau
			 */
			ModuleGame(Context * context);

			/**
			 * Destructeur du module, supprime tous les sprites et backgrounds
			 */
			virtual ~ModuleGame();

			/**
			 * Gestion des �v�nements du module Game
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
			 * Initialisation du monde affich� en haut, g�r�
			 * au travers de la classe Map
			 */
			void initWorld(MapWarp warp);

			void initConsoles();

			/**
			 * Gestion du d�placement du perso, avec scrolling en cons�quence
			 */
			void moveChar();

			/**
			 * M�thode appel�e lorsqu'on veut quitter le jeu
			 */
			void quit();

			/**
			 * Gestion du mode MODE_WALK : interactions :
			 * - d�placer le personnage avec les fl�ches
			 * - activer le mode MODE_INVENTORY en appuyant sur Start
			 * - afficher les stats du personnage en cliquant sur le sprite Status
			 * - afficher l'inventaire en cliquant sur le sprite Inventory
			 * - afficher l'�quipement en cliquant sur le sprite Equipment
			 * - quitter le jeu en cliquant sur le sprite Quit
			 * @return bool
			 */
			bool doModeWalk();

			/**
			 * Gestion des modes MODE_INVENTORY et MODE_EQUIPMENT : interactions :
			 * - revenir en mode MODE_WALK en appuyant sur Start
			 * - basculer entre MODE_INVENTORY et MODE_EQUIPMENT en appuyant sur R ou L
			 * - naviguer dans l'inventaire ou l'�quipement avec haut/bas
			 * - �quiper un item de l'inventaire avec A
			 * - retirer un item de l'�quipement avec A
			 */
			void doModeSelection();

			/**
			 * Affiche les stats du personnage. Correspond � l'ic�ne "Status" du menu
			 */
			void showStatus();

			/**
			 * Affiche l'inventaire du personnage. Correspond � l'ic�ne "Inventory" du menu
			 */
			void showInventory();

			/**
			 * Affiche l'�quipement du personnage. Correspond � l'ic�ne "Equipment" du menu
			 */
			void showEquipment();

			void updatePositions();

			void battle();

			/** Console principale */
			PrintConsole m_consoleMain;

			/** Console de description */
			PrintConsole m_consoleDesc;

			/** Le mode actuel */
			GameMode m_gameMode;

			/** L'entr�e s�lectionn�e en mode Inventory */
			unsigned int m_selectedEntry;

			/** Offset pour l'inventaire */
			int m_offsetInventory;

			std::vector<MapWarp> m_doors;

			/** Repr�sente la map courante dans laquelle �volue le personnage principal */
			Map * m_activeMap;

			/** Le background du bas */
			Background * m_bgBottom;

			/** Sprite du haut : le perso */
			SpriteChar * m_spritePlayer;

			/** Sprites du bas : ic�ne de menu, � droite */
			SpriteGameIcon * m_spriteIconStatus;
			SpriteGameIcon * m_spriteIconInventory;
			SpriteGameIcon * m_spriteIconEquipment;
			SpriteGameIcon * m_spriteIconOptions;
			SpriteGameIcon * m_spriteIconQuit;

			/** le sprite du doigt */
			Sprite * m_spriteFinger;

			/** Le sprite pour l'ic�ne de l'item s�lectionn� */
			Sprite * m_spriteSelectedItem;
	};
}

#endif

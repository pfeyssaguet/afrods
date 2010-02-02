#ifndef __GRAPHICSENGINE_H__
#define __GRAPHICSENGINE_H__

#include "characterplayer.h"
#include "charactermonster.h"

// includes standards
#include <nds.h>
#include <set>
#include <map>

#define AFRODS_BOX_TOP char(138)
#define AFRODS_BOX_TOP_LEFT char(157)
#define AFRODS_BOX_TOP_RIGHT char(140)
#define AFRODS_BOX_BOTTOM char(154)
#define AFRODS_BOX_BOTTOM_LEFT char(158)
#define AFRODS_BOX_BOTTOM_RIGHT char(159)
#define AFRODS_BOX_LEFT char(152)
#define AFRODS_BOX_RIGHT char(153)
#define AFRODS_BOX_BLANK char(155)


#define RegisterSprite(name, description) do {\
	registerSprite(name, SpriteDescription(\
		description##Tiles,\
		description##TilesLen,\
		description##Pal,\
		description##PalLen)\
	);\
} while(0);

#define RegisterBackground(name, description) do {\
	registerBackground(name, BackgroundDescription(\
		description##Tiles,\
		description##TilesLen,\
		description##Map,\
		description##MapLen,\
		description##Pal,\
		description##PalLen)\
	);\
} while(0);

namespace AfroDS {
	/**
	 * Décrit les différents sprites.
	 * Les numéros sont aussi utilisés pour choisir la palette étendue (dans le constructeur de Sprite)
	 */
	enum GraphicsSprite {
			SPRITE_HUMAN,
			SPRITE_WARRIOR, SPRITE_WIZARD, SPRITE_RANGER, SPRITE_PRIEST, SPRITE_MONK,
			SPRITE_BATTLE_WARRIOR, SPRITE_BATTLE_WIZARD, SPRITE_BATTLE_RANGER, SPRITE_BATTLE_PRIEST, SPRITE_BATTLE_MONK,
			SPRITE_NPC, SPRITE_WOMAN, SPRITE_FROG,
			SPRITE_NPC_BAZAR, SPRITE_NPC_BANK, SPRITE_NPC_ARMORY, SPRITE_NPC_MAGIC,
			SPRITE_MENU_ICONS, SPRITE_MENU_BUTTON,
			SPRITE_GAME_ICONS, SPRITE_GAME_ITEMS,
			SPRITE_FINGER,
			SPRITE_MONSTERS64_1,
			SPRITE_SIZE
	};

	enum GraphicsBackground {
			BG_SPLASH_TOP, BG_SPLASH_BOTTOM,
			BG_MENU_TOP, BG_MENU_BOTTOM01, BG_MENU_BOTTOM02, BG_MENU_BOTTOM03, BG_MENU_BOTTOM04,
			BG_GAME_BOTTOM,
			BG_BATTLE_BOTTOM, BG_BATTLE_TOP_FOREST, BG_BATTLE_TOP_DUNGEON,
			BG_GAMEOVER_BOTTOM,
			BG_SHOP_BOTTOM
	};

	struct BackgroundDescription {
		BackgroundDescription() {

		}

		BackgroundDescription(const unsigned int * p_tiles, const int p_tilesLen, const unsigned short * p_map, const int p_mapLen, const unsigned short * p_pal, const int p_palLen) {
			tiles = p_tiles;
			tilesLen = p_tilesLen;
			map = p_map;
			mapLen = p_mapLen;
			pal = p_pal;
			palLen = p_palLen;
		}

		const unsigned int * tiles;
		int tilesLen;
		const unsigned short * map;
		int mapLen;
		const unsigned short * pal;
		int palLen;
	};

	struct SpriteDescription {
		SpriteDescription() {

		}

		SpriteDescription(const unsigned int * p_tiles, const int p_tilesLen, const unsigned short * p_pal, const int p_palLen) {
			tiles = p_tiles;
			tilesLen = p_tilesLen;
			pal = p_pal;
			palLen = p_palLen;
		}

		const unsigned int * tiles;
		int tilesLen;
		const unsigned short * pal;
		int palLen;
	};

	class GraphicsEngine {
		public:
			/**
			 * Renvoie l'instance du singleton, en l'instanciant si nécessaire
			 * @return GraphicsEngine * pointeur vers le singleton
			 */
			static GraphicsEngine * getInstance();

			/**
			 * Renvoie un sprite correspondant au type de monstre demandé
			 * TODO déplacer cette méthode GraphicsEngine::MonsterTypeToGraphicsSprite pour virer la dépendance à charactermonster.h
			 *
			 * @param const MonsterType type type de monstre demandé
			 * @return GraphicsSprite sprite demandé
			 */
			static GraphicsSprite MonsterTypeToGraphicsSprite(const MonsterType type);

			/**
			 * Renvoie un sprite correspondant à la classe de personnage demandée, en mode battle ou en mode normal
			 * TODO déplacer cette méthode GraphicsEngine::CharacterClassToGraphicsSprite pour virer la dépendance à characterplayer.h
			 *
			 * @param const CharacterClass charClass classe de personnage demandée
			 * @param const bool battle true pour avoir le sprite en mode Battle
			 * @return GraphicsSprite sprite demandé
			 */
			static GraphicsSprite CharacterClassToGraphicsSprite(const CharacterClass charClass, const bool battle);

			BackgroundDescription getBackgroundDescription(const GraphicsBackground background) const;
			SpriteDescription getSpriteDescription(const GraphicsSprite sprite) const;

			/**
			 * Renvoie un numéro de sprite pour l'écran demandé
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @return unsigned short numéro de sprite
			 */
			unsigned short pickSpriteNum(const short screen);

			/**
			 * Remet un numéro de sprite dans la liste pour l'écran demandé
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param unsigned short num numéro de sprite à relâcher
			 */
			void releaseSpriteNum(const short screen, const unsigned short num);

			unsigned short pickSpritePaletteNum(const short screen);

			void releaseSpritePaletteNum(const short screen, const unsigned short num);

			/**
			 * Renvoie la palette demandée
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite à utiliser
			 * @return unsigned short * palette
			 */
			const unsigned short * getSpritePalette(const short screen, const GraphicsSprite sprite);

			/**
			 * Renvoie la taille de la palette demandée
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite à utiliser
			 * @return int taille de la palette
			 */
			int getSpritePaletteLen(const short screen, const GraphicsSprite sprite);

			int getSpritePaletteNum(const short screen, const GraphicsSprite sprite);

			PrintConsole * getConsole();

			void initConsoles();
			void createBox();

			/**
			 * Lance les 2 fonctions oamUpdate, pour chaque écran
			 */
			static void updateOam();

			/**
			 * Lance la fonction oamUpdate sur l'écran demandé
			 * @param const short screen écran demandé, SCREEN_MAIN ou SCREEN_SUB
			 */
			static void updateOam(const short screen);

		private:
			/**
			 * Constructeur privé car c'est un Singleton
			 */
			GraphicsEngine();

			/**
			 * Charge une palette
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite à charger
			 */
			void loadSpritePalette(short screen, GraphicsSprite sprite);

			/**
			 * Déclare l'ensemble des backgrounds pour pouvoir les utiliser
			 */
			void registerBackgrounds();

			/**
			 * Déclare un background pour pouvoir l'utiliser.
			 * Cette méthode est utilisée avec la macro RegisterBackground()
			 *
			 * @param GraphicsBackground background constante du backgroud sélectionné
			 * @param BackgroundDescription description structure qui contient les pointeurs générés par grit
			 */
			void registerBackground(GraphicsBackground background, BackgroundDescription description);

			/**
			 * Déclare l'ensemble des sprites pour pouvoir les utiliser
			 */
			void registerSprites();

			/**
			 * Déclare un sprite pour pouvoir l'utiliser.
			 * Cette méthode est utilisée avec la macro RegisterSprite()
			 *
			 * @param GraphicsSprite sprite constante du sprite sélectionné
			 * @param SpriteDescription description structure qui contient les pointeurs générés par grit
			 */
			void registerSprite(GraphicsSprite sprite, SpriteDescription description);

			/** Liste des descriptions de backgrounds, indexées par background */
			std::map<GraphicsBackground, BackgroundDescription> m_backgroundDescriptions;

			/** Liste des descriptions de sprites, indexées par sprite */
			std::map<GraphicsSprite, SpriteDescription> m_spriteDescriptions;

			/** Pool de sprites pour l'écran principal */
			std::set<unsigned short> m_spritePoolMain;

			/** Pool de sprites pour l'écran secondaire */
			std::set<unsigned short> m_spritePoolSub;

			/** Pool de palettes de sprites pour l'écran principal */
			std::set<unsigned short> m_spritePoolPaletteMain;

			/** Pool de palettes de sprites pour l'écran secondaire */
			std::set<unsigned short> m_spritePoolPaletteSub;

			/** Gestionnaire de palettes */
			const unsigned short * m_spritePalettes[SPRITE_SIZE];

			/** Gestionnaire de tailles de palettes */
			int m_spritePalettesLen[SPRITE_SIZE];

			/** Numéros de palettes : 1ère dimension pour l'écran */
			int m_spritePalettesNums[2][SPRITE_SIZE];

			PrintConsole * m_consoleText;
			PrintConsole * m_consoleBox;

			/** Instance du Singleton */
			static GraphicsEngine * m_Instance;
	};
}

#endif

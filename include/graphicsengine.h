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
	 * D�crit les diff�rents sprites.
	 * Les num�ros sont aussi utilis�s pour choisir la palette �tendue (dans le constructeur de Sprite)
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
			 * Renvoie l'instance du singleton, en l'instanciant si n�cessaire
			 * @return GraphicsEngine * pointeur vers le singleton
			 */
			static GraphicsEngine * getInstance();

			/**
			 * Renvoie un sprite correspondant au type de monstre demand�
			 * TODO d�placer cette m�thode GraphicsEngine::MonsterTypeToGraphicsSprite pour virer la d�pendance � charactermonster.h
			 *
			 * @param const MonsterType type type de monstre demand�
			 * @return GraphicsSprite sprite demand�
			 */
			static GraphicsSprite MonsterTypeToGraphicsSprite(const MonsterType type);

			/**
			 * Renvoie un sprite correspondant � la classe de personnage demand�e, en mode battle ou en mode normal
			 * TODO d�placer cette m�thode GraphicsEngine::CharacterClassToGraphicsSprite pour virer la d�pendance � characterplayer.h
			 *
			 * @param const CharacterClass charClass classe de personnage demand�e
			 * @param const bool battle true pour avoir le sprite en mode Battle
			 * @return GraphicsSprite sprite demand�
			 */
			static GraphicsSprite CharacterClassToGraphicsSprite(const CharacterClass charClass, const bool battle);

			BackgroundDescription getBackgroundDescription(const GraphicsBackground background) const;
			SpriteDescription getSpriteDescription(const GraphicsSprite sprite) const;

			/**
			 * Renvoie un num�ro de sprite pour l'�cran demand�
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @return unsigned short num�ro de sprite
			 */
			unsigned short pickSpriteNum(const short screen);

			/**
			 * Remet un num�ro de sprite dans la liste pour l'�cran demand�
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param unsigned short num num�ro de sprite � rel�cher
			 */
			void releaseSpriteNum(const short screen, const unsigned short num);

			unsigned short pickSpritePaletteNum(const short screen);

			void releaseSpritePaletteNum(const short screen, const unsigned short num);

			/**
			 * Renvoie la palette demand�e
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite � utiliser
			 * @return unsigned short * palette
			 */
			const unsigned short * getSpritePalette(const short screen, const GraphicsSprite sprite);

			/**
			 * Renvoie la taille de la palette demand�e
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite � utiliser
			 * @return int taille de la palette
			 */
			int getSpritePaletteLen(const short screen, const GraphicsSprite sprite);

			int getSpritePaletteNum(const short screen, const GraphicsSprite sprite);

			PrintConsole * getConsole();

			void initConsoles();
			void createBox();

			/**
			 * Lance les 2 fonctions oamUpdate, pour chaque �cran
			 */
			static void updateOam();

			/**
			 * Lance la fonction oamUpdate sur l'�cran demand�
			 * @param const short screen �cran demand�, SCREEN_MAIN ou SCREEN_SUB
			 */
			static void updateOam(const short screen);

		private:
			/**
			 * Constructeur priv� car c'est un Singleton
			 */
			GraphicsEngine();

			/**
			 * Charge une palette
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite � charger
			 */
			void loadSpritePalette(short screen, GraphicsSprite sprite);

			/**
			 * D�clare l'ensemble des backgrounds pour pouvoir les utiliser
			 */
			void registerBackgrounds();

			/**
			 * D�clare un background pour pouvoir l'utiliser.
			 * Cette m�thode est utilis�e avec la macro RegisterBackground()
			 *
			 * @param GraphicsBackground background constante du backgroud s�lectionn�
			 * @param BackgroundDescription description structure qui contient les pointeurs g�n�r�s grit
			 */
			void registerBackground(GraphicsBackground background, BackgroundDescription description);

			/**
			 * D�clare l'ensemble des sprites pour pouvoir les utiliser
			 */
			void registerSprites();

			/**
			 * D�clare un sprite pour pouvoir l'utiliser.
			 * Cette m�thode est utilis�e avec la macro RegisterSprite()
			 *
			 * @param GraphicsSprite sprite constante du sprite s�lectionn�
			 * @param SpriteDescription description structure qui contient les pointeurs g�n�r�s par grit
			 */
			void registerSprite(GraphicsSprite sprite, SpriteDescription description);

			/** Liste des descriptions de backgrounds, index�es par background */
			std::map<GraphicsBackground, BackgroundDescription> m_backgroundDescriptions;

			/** Liste des descriptions de sprites, index�es par sprite */
			std::map<GraphicsSprite, SpriteDescription> m_spriteDescriptions;

			/** Pool de sprites pour l'�cran principal */
			std::set<unsigned short> m_spritePoolMain;

			/** Pool de sprites pour l'�cran secondaire */
			std::set<unsigned short> m_spritePoolSub;

			/** Pool de palettes de sprites pour l'�cran principal */
			std::set<unsigned short> m_spritePoolPaletteMain;

			/** Pool de palettes de sprites pour l'�cran secondaire */
			std::set<unsigned short> m_spritePoolPaletteSub;

			/** Gestionnaire de palettes */
			const unsigned short * m_spritePalettes[SPRITE_SIZE];

			/** Gestionnaire de tailles de palettes */
			int m_spritePalettesLen[SPRITE_SIZE];

			/** Num�ros de palettes : 1�re dimension pour l'�cran */
			int m_spritePalettesNums[2][SPRITE_SIZE];

			PrintConsole * m_consoleText;
			PrintConsole * m_consoleBox;

			/** Instance du Singleton */
			static GraphicsEngine * m_Instance;
	};
}

#endif

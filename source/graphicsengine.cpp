// includes internes
#include "graphicsengine.h"
#include "constants.h"

// les sprites
#include "spr_char_human_male.h"
#include "spr_char_warrior.h"
#include "spr_char_wizard.h"
#include "spr_char_ranger.h"
#include "spr_char_priest.h"
#include "spr_char_monk.h"
#include "spr_char_pnj_oldman01.h"
#include "spr_char_pnj_oldwomen01.h"
#include "spr_char_pnj_frog01.h"
#include "spr_char_pnj_bazar.h"
#include "spr_char_pnj_bank.h"
#include "spr_char_pnj_armory.h"
#include "spr_char_pnj_magic.h"
#include "spr_battle_warrior.h"
#include "spr_battle_wizard.h"
#include "spr_battle_ranger.h"
#include "spr_battle_priest.h"
#include "spr_battle_monk.h"
#include "spr_monsters64_1.h"
#include "spr_finger.h"
#include "spr_menu_icons.h"
#include "spr_menu_button.h"
#include "spr_game_icons.h"
#include "spr_game_items.h"

// les backgrounds
#include "bg_splash_top.h"
#include "bg_splash_bottom.h"
#include "bg_menu_top.h"
#include "bg_menu_bottom_01.h"
#include "bg_menu_bottom_02.h"
#include "bg_menu_bottom_03.h"
#include "bg_menu_bottom_04.h"
#include "bg_game_bottom.h"
#include "bg_battle_bottom.h"
#include "bg_battle_top_forest.h"
#include "bg_battle_top_dungeon.h"
#include "bg_gameover_bottom.h"
#include "bg_shop_bottom.h"

#include "fnt_arialia.h"
#include "fnt_ffstyle.h"

#include <stdio.h>

using namespace AfroDS;

GraphicsEngine * GraphicsEngine::m_Instance = NULL;

GraphicsEngine::GraphicsEngine() {
	for (unsigned short i = 0 ; i <= 127 ; i++) {
		m_spritePoolMain.insert(i);
		m_spritePoolSub.insert(i);
	}

	for (unsigned short i = 0 ; i <= 15 ; i++) {
		m_spritePoolPaletteMain.insert(i);
		m_spritePoolPaletteSub.insert(i);
	}

	for (int i = 0 ; i < SPRITE_SIZE ; i++) {
		m_spritePalettes[i] = NULL;
		m_spritePalettesLen[i] = 0;
	}
	for (int screen = 0 ; screen < 2 ; screen++) {
		for (int i = 0 ; i < SPRITE_SIZE ; i++) {
			m_spritePalettesNums[screen][i] = -1;
		}
	}

	registerBackgrounds();
	registerSprites();
}

GraphicsEngine * GraphicsEngine::getInstance() {
	if (m_Instance == NULL) {
		m_Instance = new GraphicsEngine();
	}
	return m_Instance;
}

void GraphicsEngine::registerBackgrounds() {
	RegisterBackground(BG_BATTLE_BOTTOM, bg_battle_bottom);
	RegisterBackground(BG_SPLASH_TOP, bg_splash_top);
	RegisterBackground(BG_SPLASH_BOTTOM, bg_splash_bottom);
	RegisterBackground(BG_MENU_TOP, bg_menu_top);
	RegisterBackground(BG_MENU_BOTTOM01, bg_menu_bottom_01);
	RegisterBackground(BG_MENU_BOTTOM02, bg_menu_bottom_02);
	RegisterBackground(BG_MENU_BOTTOM03, bg_menu_bottom_03);
	RegisterBackground(BG_MENU_BOTTOM04, bg_menu_bottom_04);
	RegisterBackground(BG_GAME_BOTTOM, bg_game_bottom);
	RegisterBackground(BG_BATTLE_BOTTOM, bg_battle_bottom);
	RegisterBackground(BG_BATTLE_TOP_FOREST, bg_battle_top_forest);
	RegisterBackground(BG_BATTLE_TOP_DUNGEON, bg_battle_top_dungeon);
	RegisterBackground(BG_GAMEOVER_BOTTOM, bg_gameover_bottom);
	RegisterBackground(BG_SHOP_BOTTOM, bg_shop_bottom);
}

void GraphicsEngine::registerSprites() {
	RegisterSprite(SPRITE_WARRIOR, spr_char_warrior);
	RegisterSprite(SPRITE_WIZARD, spr_char_wizard);
	RegisterSprite(SPRITE_RANGER, spr_char_ranger);
	RegisterSprite(SPRITE_PRIEST, spr_char_priest);
	RegisterSprite(SPRITE_MONK, spr_char_monk);
	RegisterSprite(SPRITE_BATTLE_MONK, spr_battle_monk);
	RegisterSprite(SPRITE_BATTLE_PRIEST, spr_battle_priest);
	RegisterSprite(SPRITE_BATTLE_RANGER, spr_battle_ranger);
	RegisterSprite(SPRITE_BATTLE_WARRIOR, spr_battle_warrior);
	RegisterSprite(SPRITE_BATTLE_WIZARD, spr_battle_wizard);
	RegisterSprite(SPRITE_FINGER, spr_finger);
	RegisterSprite(SPRITE_FROG, spr_char_pnj_frog01);
	RegisterSprite(SPRITE_NPC_BAZAR, spr_char_pnj_bazar);
	RegisterSprite(SPRITE_NPC_BANK, spr_char_pnj_bank);
	RegisterSprite(SPRITE_NPC_ARMORY, spr_char_pnj_armory);
	RegisterSprite(SPRITE_NPC_MAGIC, spr_char_pnj_magic);
	RegisterSprite(SPRITE_HUMAN, spr_char_human_male);
	RegisterSprite(SPRITE_MENU_ICONS, spr_menu_icons);
	RegisterSprite(SPRITE_MENU_BUTTON, spr_menu_button);
	RegisterSprite(SPRITE_GAME_ICONS, spr_game_icons);
	RegisterSprite(SPRITE_GAME_ITEMS, spr_game_items);
	RegisterSprite(SPRITE_MONSTERS64_1, spr_monsters64_1);
	RegisterSprite(SPRITE_NPC, spr_char_pnj_oldman01);
	RegisterSprite(SPRITE_WOMAN, spr_char_pnj_oldwomen01);
}


void GraphicsEngine::registerBackground(GraphicsBackground background, BackgroundDescription description) {
	m_backgroundDescriptions[background] = description;
}

void GraphicsEngine::registerSprite(GraphicsSprite sprite, SpriteDescription description) {
	m_spriteDescriptions[sprite] = description;
}

/**
 * Renvoie un sprite correspondant au type de monstre demandé
 * TODO déplacer cette méthode GraphicsEngine::MonsterTypeToGraphicsSprite pour virer la dépendance à charactermonster.h
 *
 * @param const MonsterType type type de monstre demandé
 * @return GraphicsSprite sprite demandé
 */
GraphicsSprite GraphicsEngine::MonsterTypeToGraphicsSprite(MonsterType type) {
	switch (type) {
		case MONSTER_BAT:
		case MONSTER_RAT:
		case MONSTER_FROG:
			return SPRITE_MONSTERS64_1;
			break;
		default:
			break;
	}
	return SPRITE_MONSTERS64_1;
}

/**
 * Renvoie un sprite correspondant à la classe de personnage demandée, en mode battle ou en mode normal
 * TODO déplacer cette méthode GraphicsEngine::CreatureClassToGraphicsSprite pour virer la dépendance à characterplayer.h
 *
 * @param const CreatureClass charClass classe de personnage demandée
 * @param const bool battle true pour avoir le sprite en mode Battle
 * @return GraphicsSprite sprite demandé
 */
GraphicsSprite GraphicsEngine::CreatureClassToGraphicsSprite(Job charClass, bool battle) {
	if (battle) {
		// on retourne les sprites du mode Battle
		switch (charClass) {
			case JOB_WARRIOR:
				return SPRITE_BATTLE_WARRIOR;
				break;
			case JOB_WIZARD:
				return SPRITE_BATTLE_WIZARD;
				break;
			case JOB_RANGER:
				return SPRITE_BATTLE_RANGER;
				break;
			case JOB_PRIEST:
				return SPRITE_BATTLE_PRIEST;
				break;
			case JOB_MONK:
				return SPRITE_BATTLE_MONK;
				break;
		}
	} else {
		// on retourne les sprites normaux (utilisés sur la map, dans le menu...)
		switch (charClass) {
			case JOB_WARRIOR:
				return SPRITE_WARRIOR;
				break;
			case JOB_WIZARD:
				return SPRITE_WIZARD;
				break;
			case JOB_RANGER:
				return SPRITE_RANGER;
				break;
			case JOB_PRIEST:
				return SPRITE_PRIEST;
				break;
			case JOB_MONK:
				return SPRITE_MONK;
				break;
		}
	}

	// par défaut on retourne un sprite d'humain simple
	return SPRITE_HUMAN;
}

BackgroundDescription GraphicsEngine::getBackgroundDescription(const GraphicsBackground background) const {
	if (m_backgroundDescriptions.find(background) == m_backgroundDescriptions.end()) {
		return BackgroundDescription();
	} else {
		//return m_backgroundDescriptions[background];
		return m_backgroundDescriptions.find(background)->second;
	}
}

SpriteDescription GraphicsEngine::getSpriteDescription(const GraphicsSprite sprite) const {
	if (m_spriteDescriptions.find(sprite) == m_spriteDescriptions.end()) {
		return SpriteDescription();
	} else {
		//return m_spriteDescriptions[sprite];
		return m_spriteDescriptions.find(sprite)->second;
	}
}

int GraphicsEngine::getSpritePaletteNum(short screen, GraphicsSprite sprite) {
	return m_spritePalettesNums[screen][sprite];
}

/**
 * Renvoie un numéro de sprite pour l'écran demandé
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @return unsigned short numéro de sprite
 */
unsigned short GraphicsEngine::pickSpriteNum(short screen) {
	if (screen == SCREEN_MAIN) {
		unsigned short num = *m_spritePoolMain.begin();
		m_spritePoolMain.erase(m_spritePoolMain.begin());
		return num;
	} else {
		unsigned short num = *m_spritePoolSub.begin();
		m_spritePoolSub.erase(m_spritePoolSub.begin());
		return num;
	}
}

/**
 * Remet un numéro de sprite dans la liste pour l'écran demandé
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param unsigned short num numéro de sprite à relâcher
 */
void GraphicsEngine::releaseSpriteNum(short screen, unsigned short num) {
	// selon l'écran demandé on met le numéro dans l'une ou l'autre liste
	if (screen == SCREEN_MAIN) {
		// écran main : on utilise m_pool_main
		m_spritePoolMain.insert(num);
	} else {
		// écran main : on utilise m_pool_sub
		m_spritePoolSub.insert(num);
	}
}

unsigned short GraphicsEngine::pickSpritePaletteNum(short screen) {
	if (screen == SCREEN_MAIN) {
		unsigned short num = *m_spritePoolPaletteMain.begin();
		m_spritePoolPaletteMain.erase(m_spritePoolPaletteMain.begin());
		return num;
	} else {
		unsigned short num = *m_spritePoolPaletteSub.begin();
		m_spritePoolPaletteSub.erase(m_spritePoolPaletteSub.begin());
		return num;
	}
}

void GraphicsEngine::releaseSpritePaletteNum(short screen, unsigned short num) {
	// selon l'écran demandé on met le numéro dans l'une ou l'autre liste
	if (screen == SCREEN_MAIN) {
		m_spritePoolPaletteMain.insert(num);
	} else {
		m_spritePoolPaletteSub.insert(num);
	}
}

/**
 * Charge une palette
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param GraphicsSprite sprite sprite à charger
 */
void GraphicsEngine::loadSpritePalette(short screen, GraphicsSprite sprite) {
	if (m_spritePalettesNums[screen][sprite] == -1) {
		m_spritePalettesNums[screen][sprite] = pickSpritePaletteNum(screen);
	}

	if (m_spriteDescriptions.find(sprite) != m_spriteDescriptions.end()) {
		SpriteDescription desc = m_spriteDescriptions[sprite];
		m_spritePalettes[sprite] = desc.pal;
		m_spritePalettesLen[sprite] = desc.palLen;
	}

	if (screen == SCREEN_MAIN) {
		// on active les palettes étendues des sprites pour cet écran
		REG_DISPCNT |= DISPLAY_SPR_EXT_PALETTE;

		// on copie la palette dans son slot
		vramSetBankF(VRAM_F_LCD);
		dmaCopy(m_spritePalettes[sprite], VRAM_F_EXT_SPR_PALETTE[m_spritePalettesNums[screen][sprite]], m_spritePalettesLen[sprite]);
		vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	} else {
		// on active les palettes étendues des sprites pour cet écran
		REG_DISPCNT_SUB |= DISPLAY_SPR_EXT_PALETTE;

		// on copie la palette dans son slot
		vramSetBankI(VRAM_I_LCD);
		dmaCopy(m_spritePalettes[sprite], VRAM_I_EXT_SPR_PALETTE[m_spritePalettesNums[screen][sprite]], m_spritePalettesLen[sprite]);
		vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	}
}

/**
 * Renvoie la palette demandée
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param GraphicsSprite sprite sprite à utiliser
 * @return unsigned short * palette
 */
const unsigned short * GraphicsEngine::getSpritePalette(short screen, GraphicsSprite sprite) {
	loadSpritePalette(screen, sprite);
	return m_spritePalettes[sprite];
}

/**
 * Renvoie la taille de la palette demandée
 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
 * @param GraphicsSprite sprite sprite à utiliser
 * @return int taille de la palette
 */
int GraphicsEngine::getSpritePaletteLen(short screen, GraphicsSprite sprite) {
	loadSpritePalette(screen, sprite);
	return m_spritePalettesLen[sprite];
}

PrintConsole * GraphicsEngine::getConsole() {
	return m_consoleText;
}

void GraphicsEngine::initConsoles() {

	// init de la console
	m_consoleText = consoleInit(0, 0, BgType_Text8bpp, BgSize_T_256x256, 0, 1, SCREEN_SUB, true);

	ConsoleFont font;

	font.gfx = (u16*)fnt_arialiaTiles;
	font.pal = (u16*)fnt_arialiaPal;
	//	font.gfx = (u16*)fnt_ffstyleTiles;
	//	font.pal = (u16*)fnt_ffstylePal;
	//font.numChars = 224;
	font.numChars = 256;
	font.numColors = fnt_arialiaPalLen/2;
	//	font.numColors = fnt_ffstylePalLen/2;
	font.bpp = 8;
	font.asciiOffset = 32;
	font.convertSingleColor = false;

	consoleSetFont(m_consoleText, &font);

//	m_consoleBox = consoleInit(0, 1, BgType_Text8bpp, BgSize_T_256x256, 1, 2, SCREEN_SUB, true);
//	consoleSetFont(m_consoleBox, &font);
/*
	int width = 26;
	int height = 9;

	int x = (28 - width) / 2;
	int y = (24 - height) - 1;
	consoleSelect(m_consoleText);
	consoleSetWindow(m_consoleText, x, y, width, height);
	createBox();
	*/
	//PrintConsole *console = consoleInit(0, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 1, SCREEN_SUB, true);
	consoleSelect(m_consoleText); //Set the previous console as default for printing

	//iprintf("\x1b[31m");

	// on copie la palette de la police
	vramSetBankH(VRAM_H_LCD);
	dmaCopy(m_consoleText->font.pal, VRAM_H_EXT_PALETTE[0], m_consoleText->font.numColors*2);
//	dmaCopy(m_consoleBox->font.pal, VRAM_H_EXT_PALETTE[1], m_consoleBox->font.numColors*2);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);

}

/**
 * Lance les 2 fonctions oamUpdate, pour chaque écran
 */
void GraphicsEngine::updateOam() {
	updateOam(SCREEN_MAIN);
	updateOam(SCREEN_SUB);
}

/**
 * Lance la fonction oamUpdate sur l'écran demandé
 * @param const short screen écran demandé, SCREEN_MAIN ou SCREEN_SUB
 */
void GraphicsEngine::updateOam(const short screen) {
	if (screen == SCREEN_MAIN) {
		oamUpdate(&oamMain);
	} else {
		oamUpdate(&oamSub);
	}
}

void GraphicsEngine::createBox() {
	return;
	int width = 26;
	int height = 9;

	int x = (28 - width) / 2;
	int y = (24 - height) - 1;
	consoleSetWindow(m_consoleBox, x, y, width, height);

	//iprintf("\x1b[%d;%dH", y, x);

	for (int i = 0 ; i < height ; i++) {
		for (int j = 0 ; j < width ; j++) {
			if (j == 0) {
				if (i == 0) {
					iprintf("%c", AFRODS_BOX_TOP_LEFT);
				} else if (i == height-1) {
					iprintf("%c", AFRODS_BOX_BOTTOM_LEFT);
				} else {
					iprintf("%c", AFRODS_BOX_LEFT);
				}
			} else if (j == width-1) {
				if (i == 0) {
					iprintf("%c", AFRODS_BOX_TOP_RIGHT);
				} else if (i == height-1) {
					iprintf("%c", AFRODS_BOX_BOTTOM_RIGHT);
				} else {
					iprintf("%c", AFRODS_BOX_RIGHT);
				}
			} else {
				if (i == 0) {
					iprintf("%c", AFRODS_BOX_TOP);
				} else if (i == height-1) {
					iprintf("%c", AFRODS_BOX_BOTTOM);
				} else {
					iprintf("%c", AFRODS_BOX_BLANK);
				}
			}
		}
		//iprintf("\x1b[%d;%dH", y+i+1, x);
		//iprintf("\n");
	}
	consoleSetWindow(m_consoleText, x+1, y+1, width-2, height-2);
	iprintf("si tu te la joues ca risque d'etre chaud pour ton matricule, ");
//	iprintf("tu marches sur le fil de la vie comme un funambule ");
//	iprintf("mais tu trouveras plus scarla que toi, ");
//	iprintf("plus mecra que mecra, ");
//	iprintf("et tes zefa de neclou tu les ravaleras");
}

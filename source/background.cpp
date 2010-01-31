#include "background.h"
#include "constants.h"

#include <nds.h>

using namespace AfroDS;

/** Variable statique : les 4 layers de backgrounds utilisés sur chaque écran */
int Background::s_backgrounds[2][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}};

/**
 * Constructeur de background : affiche directement le background après l'avoir chargé
 * @param short screen écran, utiliser SCREEN_MAIN ou SCREEN_SUB
 * @param short layer layer à utiliser, 0-3
 * @param GraphicsBackground background background à utiliser
 */
Background::Background(const short screen, const short layer, const GraphicsBackground background) {
	m_screen = screen;
	m_layer = layer;
	m_description = GraphicsEngine::getInstance()->getBackgroundDescription(background);

	// selon l'écran on fait un bgInit() ou un bgInitSub()
	if (m_screen == SCREEN_MAIN) {
		//m_id = bgInit(m_layer, BgType_Text8bpp, BgSize_T_256x256, (layer)*8, layer+1);
		m_id = bgInit(m_layer, BgType_Text8bpp, BgSize_T_256x256, layer, layer+1);
	} else {
		//m_id = bgInitSub(m_layer, BgType_Text8bpp, BgSize_T_256x256, (layer)*8, layer+1);
		m_id = bgInitSub(m_layer, BgType_Text8bpp, BgSize_T_256x256, layer, layer+1);
	}

	// on met l'id dans le tableau statique
	s_backgrounds[m_screen][m_layer] = m_id;

	// on fixe la priorité du background comme celle de son layer
	bgSetPriority(m_id, m_layer);

	// masquage du background
	bgHide(m_id);

	// chargement de la map
	loadBackgroundMap();

	// chargement des tiles
	loadBackgroundTiles();

	// chargement de la palette
	loadBackgroundPalette();

	// affichage du background
	bgShow(m_id);
}

/**
 * Destructeur de background : masque le background et libère sa mémoire vidéo
 */
Background::~Background() {
	// en fait on le cache juste
	bgHide(m_id);
	// on le vire du tableau statique
	s_backgrounds[m_screen][m_layer] = 0;
}

/**
 * Charge la map du background dans la mémoire vidéo
 */
void Background::loadBackgroundMap() {
	dmaCopy(m_description.map, bgGetMapPtr(m_id), m_description.mapLen);
}

/**
 * Charge les tiles du background dans la mémoire vidéo
 */
void Background::loadBackgroundTiles() {
	dmaCopy(m_description.tiles, bgGetGfxPtr(m_id), m_description.tilesLen);
}

/**
 * Charge la palette du background dans la mémoire vidéo
 */
void Background::loadBackgroundPalette() {
	if (m_screen == SCREEN_MAIN) {
		// on passe la bank E en LCD pour pouvoir écrire dedans
		vramSetBankE(VRAM_E_LCD);
		// on copie la palette
		dmaCopy(m_description.pal, VRAM_E_EXT_PALETTE[m_layer], m_description.palLen);
		// on remet la bank E sur le mode palette ext
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
		// on s'assure que le display utilise la palette ext
		REG_DISPCNT |= DISPLAY_BG_EXT_PALETTE;

		// pour une raison étrange si je ne copie pas aussi la palette dans le slot principal, ça merdouille un peu...
		dmaCopy(m_description.pal, BG_PALETTE, m_description.palLen);
	} else {

		vramSetBankH(VRAM_H_LCD);
		dmaCopy(m_description.pal, VRAM_H_EXT_PALETTE[m_layer], m_description.palLen);
		vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
		REG_DISPCNT_SUB |= DISPLAY_BG_EXT_PALETTE;

		// pour une raison étrange si je ne copie pas aussi la palette dans le slot principal, ça merdouille un peu...
		dmaCopy(m_description.pal, BG_PALETTE_SUB, m_description.palLen);
	}
}

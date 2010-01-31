#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "graphicsengine.h"

namespace AfroDS {
	/**
	 * Permet de gérer un background en tiles, avec sa palette, sa map et ses tiles
	 */
	class Background {
		public:
			/**
			 * Constructeur de background : affiche directement le background après l'avoir chargé
			 * @param short screen écran, utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param short layer layer à utiliser, 0-3
			 * @param GraphicsBackground background background à utiliser
			 */
			Background(const short screen, const short layer, const GraphicsBackground background);

			/**
			 * Destructeur de background : masque le background et libère sa mémoire vidéo
			 */
			~Background();
		private:
			/**
			 * Charge les tiles du background dans la mémoire vidéo
			 */
			void loadBackgroundTiles();

			/**
			 * Charge la palette du background dans la mémoire vidéo
			 */
			void loadBackgroundPalette();

			/**
			 * Charge la map du background dans la mémoire vidéo
			 */
			void loadBackgroundMap();

			/** Ecran sur lequel est affiché le background, SCREEN_SUB ou SCREEN_MAIN */
			short m_screen;

			/** Layer du background, 0-3 */
			short m_layer;

			BackgroundDescription m_description;

			/** MapBase utilisée */
			int m_mapBase;

			/** Id généré par bgInit() */
			int m_id;

			/** Variable statique : les 4 layers de backgrounds utilisés sur chaque écran */
			static int s_backgrounds[2][4];
	};
}

#endif

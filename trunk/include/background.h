#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "graphicsengine.h"

namespace AfroDS {
	/**
	 * Permet de g�rer un background en tiles, avec sa palette, sa map et ses tiles
	 */
	class Background {
		public:
			/**
			 * Constructeur de background : affiche directement le background apr�s l'avoir charg�
			 * @param short screen �cran, utiliser SCREEN_MAIN ou SCREEN_SUB
			 * @param short layer layer � utiliser, 0-3
			 * @param GraphicsBackground background background � utiliser
			 */
			Background(const short screen, const short layer, const GraphicsBackground background);

			/**
			 * Destructeur de background : masque le background et lib�re sa m�moire vid�o
			 */
			~Background();
		private:
			/**
			 * Charge les tiles du background dans la m�moire vid�o
			 */
			void loadBackgroundTiles();

			/**
			 * Charge la palette du background dans la m�moire vid�o
			 */
			void loadBackgroundPalette();

			/**
			 * Charge la map du background dans la m�moire vid�o
			 */
			void loadBackgroundMap();

			/** Ecran sur lequel est affich� le background, SCREEN_SUB ou SCREEN_MAIN */
			short m_screen;

			/** Layer du background, 0-3 */
			short m_layer;

			BackgroundDescription m_description;

			/** MapBase utilis�e */
			int m_mapBase;

			/** Id g�n�r� par bgInit() */
			int m_id;

			/** Variable statique : les 4 layers de backgrounds utilis�s sur chaque �cran */
			static int s_backgrounds[2][4];
	};
}

#endif

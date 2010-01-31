#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "types.h"
#include "graphicsengine.h"

#include <nds.h>

namespace AfroDS {
	class Sprite {
		public:
			/**
			 * Constructeur : cr�e le sprite
			 * @param short screen �cran � utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite � utiliser
			 */
			Sprite(short screen, GraphicsSprite sprite);

			/**
			 * Destructeur : Supprime le sprite
			 * Il est virtuel pour �tre appel� par les classes qui h�ritent de Sprite
			 */
			virtual ~Sprite();

			/**
			 * Met � jour le sprite par rapport � ses param�tres courants avec oamSet()
			 */
			void update();

			/**
			 * Renvoie la position X
			 * @return int position X
			 */
			int getPosX() const;

			/**
			 * D�finit la position X
			 * @param int x position X
			 */
			void setPosX(const int x);

			/**
			 * Renvoie la position Y
			 * @return int position Y
			 */
			int getPosY() const;

			/**
			 * D�finit la position Y
			 * @param int y position Y
			 */
			void setPosY(const int y);

			/**
			 * Renvoie la position avec un type personnalis�
			 * @return AF_Coords position
			 */
			Coords getPos() const;

			Coords getDimensions() const;
			int getWidth() const;
			int getHeight() const;


			/**
			 * D�finit la position avec un type personnalis�
			 * @param AF_Coords pos position
			 */
			void setPos(const Coords pos);

			/**
			 * D�finit les positions de X et Y
			 * @param int x position X
			 * @param int y position Y
			 */
			void setPos(const int x, const int y);

			/**
			 * Affiche ou masque un sprite
			 * @param bool visible true pour afficher le sprite
			 */
			void setVisible(bool visible);

			/**
			 * Permet de savoir si un point est dans la zone du sprite
			 * @param int x coordonn�e X
			 * @param int y coordonn�e Y
			 * @return bool true si le point est dans la zone du sprite
			 */
			bool isInZone(int x, int y);

			/**
			 * Permet de savoir si un point est dans la zone du sprite
			 * @param Coords zone coordonn�es
			 * @return bool true si le point est dans la zone du sprite
			 */
			bool isInZone(Coords zone);

			/**
			 * D�finit la frame courante du sprite
			 * @param short frame frame � s�lectionner
			 */
			void setCurrentFrame(short frame);

			/**
			 * Renvoie la frame courante
			 * @return short frame courante
			 */
			short getCurrentFrame();

			/**
			 * Renvoie le num�ro du sprite
			 * @return short num�ro de sprite
			 */
			short getSpriteNum();

			/**
			 * D�finit la priorit� du sprite (le layer sur lequel il est affich�)
			 * Un sprite est toujours devant un background pour un layer donn�.
			 * Donc les sprites auront par d�faut 1 comme priorit� pour �tre derri�re
			 * le background 0 utilis� pour le texte
			 * @param short priority priorit�
			 */
			void setPriority(short priority);

			/**
			 * Renvoie la priorit� du sprite
			 * @return short priorit�
			 */
			short getPriority();

			/**
			 * Pour faire clignoter le sprite
			 */
			void blink();

		protected:
			/** Graphisme allou� par oamAllocateGfx() */
			u16* m_gfx;

			/** Num�ro de sprite */
			short m_num_sprite;

			/** Frame actuelle du sprite */
			short m_current_frame;

			/** Ecran du sprite, SCREEN_MAIN ou SCREEN_SUB */
			short m_screen;

			/** Priorit� du sprite */
			short m_priority;

			/** Position du sprite � l'�cran */
			Coords m_pos;

			/** Indique si le sprite est visible ou pas */
			bool m_visible;

			/** Taille du sprite : 32x32 en principe */
			SpriteSize m_size;

			Coords m_dimensions;

			/** Format de couleurs : 256 en principe */
			SpriteColorFormat m_color_format;

			SpriteDescription m_description;

			/** Palette */
			const unsigned short * m_pal;

			/** Taille de la palette */
			int m_pal_len;

			/** Num�ro de palette */
			int m_pal_num;

	};
}

#endif

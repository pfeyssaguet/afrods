#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "types.h"
#include "graphicsengine.h"

#include <nds.h>

namespace AfroDS {
	class Sprite {
		public:
			/**
			 * Constructeur : crée le sprite
			 * @param short screen écran à utiliser : SCREEN_MAIN ou SCREEN_SUB
			 * @param GraphicsSprite sprite sprite à utiliser
			 */
			Sprite(short screen, GraphicsSprite sprite);

			/**
			 * Destructeur : Supprime le sprite
			 * Il est virtuel pour être appelé par les classes qui héritent de Sprite
			 */
			virtual ~Sprite();

			/**
			 * Met à jour le sprite par rapport à ses paramètres courants avec oamSet()
			 */
			void update();

			/**
			 * Renvoie la position X
			 * @return int position X
			 */
			int getPosX() const;

			/**
			 * Définit la position X
			 * @param int x position X
			 */
			void setPosX(const int x);

			/**
			 * Renvoie la position Y
			 * @return int position Y
			 */
			int getPosY() const;

			/**
			 * Définit la position Y
			 * @param int y position Y
			 */
			void setPosY(const int y);

			/**
			 * Renvoie la position avec un type personnalisé
			 * @return AF_Coords position
			 */
			Coords getPos() const;

			Coords getDimensions() const;
			int getWidth() const;
			int getHeight() const;


			/**
			 * Définit la position avec un type personnalisé
			 * @param AF_Coords pos position
			 */
			void setPos(const Coords pos);

			/**
			 * Définit les positions de X et Y
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
			 * @param int x coordonnée X
			 * @param int y coordonnée Y
			 * @return bool true si le point est dans la zone du sprite
			 */
			bool isInZone(int x, int y);

			/**
			 * Permet de savoir si un point est dans la zone du sprite
			 * @param Coords zone coordonnées
			 * @return bool true si le point est dans la zone du sprite
			 */
			bool isInZone(Coords zone);

			/**
			 * Définit la frame courante du sprite
			 * @param short frame frame à sélectionner
			 */
			void setCurrentFrame(short frame);

			/**
			 * Renvoie la frame courante
			 * @return short frame courante
			 */
			short getCurrentFrame();

			/**
			 * Renvoie le numéro du sprite
			 * @return short numéro de sprite
			 */
			short getSpriteNum();

			/**
			 * Définit la priorité du sprite (le layer sur lequel il est affiché)
			 * Un sprite est toujours devant un background pour un layer donné.
			 * Donc les sprites auront par défaut 1 comme priorité pour être derrière
			 * le background 0 utilisé pour le texte
			 * @param short priority priorité
			 */
			void setPriority(short priority);

			/**
			 * Renvoie la priorité du sprite
			 * @return short priorité
			 */
			short getPriority();

			/**
			 * Pour faire clignoter le sprite
			 */
			void blink();

		protected:
			/** Graphisme alloué par oamAllocateGfx() */
			u16* m_gfx;

			/** Numéro de sprite */
			short m_num_sprite;

			/** Frame actuelle du sprite */
			short m_current_frame;

			/** Ecran du sprite, SCREEN_MAIN ou SCREEN_SUB */
			short m_screen;

			/** Priorité du sprite */
			short m_priority;

			/** Position du sprite à l'écran */
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

			/** Numéro de palette */
			int m_pal_num;

	};
}

#endif

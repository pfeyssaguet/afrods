#include "game.h"

void AF_GameInit()
{
	// on indique qu'on est dans le module game
	G_Env.Module = AFRODS_MODULE_GAME;
	
	// on nettoie les écrans
	PA_DeleteBg(ECRAN_HAUT, AFRODS_LAYER_BG);
	PA_DeleteBg(ECRAN_BAS, AFRODS_LAYER_BG);
	
	// on charge le sprite du personnage
	PA_LoadSpritePal(ECRAN_BAS, // Screen
				AFRODS_PAL_PERSO, // Palette number
				(void*)perso_Pal);	// Palette name

	// initialisation de la position (pour l'instant, 50,50)
	G_Env.Perso.position.x = 50;
	G_Env.Perso.position.y = 50;
	
	// on crée le sprite à l'écran
	PA_CreateSprite(ECRAN_BAS, // Screen
				AFRODS_SPRITE_PERSO, // Sprite number
				(void*)perso_Sprite, // Sprite name
				OBJ_SIZE_32X32, // Sprite size
				1, // 256 color mode
				AFRODS_PAL_PERSO, // Sprite palette number
				G_Env.Perso.position.x, G_Env.Perso.position.y); // X and Y position on the screen
}

void AF_GameEvents()
{
	// Animation code...
	if(Pad.Newpress.Up)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_PERSO, 0, 2, 6);

	if(Pad.Newpress.Down)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_PERSO, 6, 8, 6);

	if(Pad.Newpress.Right)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_PERSO, 3, 5, 6);

	if(Pad.Newpress.Left)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_PERSO, 9, 11, 6);
	
	if(!((Pad.Held.Left)||(Pad.Held.Up)||(Pad.Held.Down)||(Pad.Held.Right)))
		PA_SpriteAnimPause(ECRAN_BAS, AFRODS_SPRITE_PERSO, 1);

	// Déplacement du personnage
	G_Env.Perso.position.y += Pad.Held.Down - Pad.Held.Up;
	G_Env.Perso.position.x += Pad.Held.Right - Pad.Held.Left;
	
	// On redessine le sprite
	PA_SetSpriteXY(ECRAN_BAS, AFRODS_SPRITE_PERSO, G_Env.Perso.position.x, G_Env.Perso.position.y);

}

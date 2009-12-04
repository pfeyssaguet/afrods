#include "game.h"

Game::Game() {
	// on met un fond de couleur noire
	PA_SetBgColor(ECRAN_BAS, PA_RGB(0, 0, 0));
	PA_SetBgColor(ECRAN_HAUT, PA_RGB(0, 0, 0));

	// initialisation du personnage (avec des valeurs bidons pour l'instant)
	m_activeChar.setName("deuspi");
	m_activeChar.setPosXY(50, 50);

	// on crée le sprite à l'écran
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO,
		(void*)spr_perso_Sprite, OBJ_SIZE_32X32,
		1, AFRODS_PAL_PERSO,
		m_activeChar.getPosX(), m_activeChar.getPosY());
}

Game::~Game() {
	// on supprime le sprite du perso
	PA_DeleteSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO);
}

void Game::moduleEvents()
{
	// pour l'instant on quitte le jeu en faisant Start
	if (Pad.Newpress.Start)
		quit();

	// Animation code...
	if(Pad.Newpress.Up)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, 0, 2, 6);

	if(Pad.Newpress.Down)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, 6, 8, 6);

	if(Pad.Newpress.Right)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, 3, 5, 6);

	if(Pad.Newpress.Left)
		PA_StartSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, 9, 11, 6);

	if(!((Pad.Held.Left)||(Pad.Held.Up)||(Pad.Held.Down)||(Pad.Held.Right)))
		PA_SpriteAnimPause(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, 1);

	// Déplacement du personnage
	m_activeChar.setPosX(m_activeChar.getPosX() + Pad.Held.Right - Pad.Held.Left);
	m_activeChar.setPosY(m_activeChar.getPosY() + Pad.Held.Down - Pad.Held.Up);

	// On redessine le sprite
	PA_SetSpriteXY(ECRAN_BAS, AFRODS_SPRITE_GAME_PERSO, m_activeChar.getPosX(), m_activeChar.getPosY());
}

void Game::quit()
{
	// on indique qu'on veut sortir
	m_bIsStopped = true;

	// pour aller dans le module Splash
	G_Env.NextModule = AFRODS_MODULE_SPLASH;
}

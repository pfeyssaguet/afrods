#include "game.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

using namespace AfroDS;

Game::Game() {
	// on charge la palette du personnage
	PA_LoadSpritePal(ECRAN_HAUT, AFRODS_PAL_TOP_PERSO, (void*)palPerso_Pal);

	// on met un fond de couleur noire
	PA_SetBgColor(ECRAN_HAUT, PA_RGB(0, 0, 0));

	// chargement du menu
	initMenu();

	// création de la map
	m_activeMap = Map();

	// initialisation du personnage
	m_activeChar = G_Env.ActiveChar;

	// on place le perso sur la position de départ de la map
	Coords coords = m_activeMap.getStartingPos();
	coords.x = coords.x * 16 - AFRODS_GAME_OFFSET_TILES_X;
	coords.y = coords.y * 16 - AFRODS_GAME_OFFSET_TILES_Y;
	m_activeChar.setPos(coords);

	// On redessine la map
	m_activeMap.prepareTiles();

	// on crée le sprite à l'écran
	PA_CreateSprite(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, (void*)spr_perso_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_PERSO, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 7);
}

Game::~Game() {
	PA_ResetBgSys();
	PA_ResetSpriteSys();
}

void Game::moduleEvents()
{
	// pour l'instant on quitte le jeu en faisant Start
	if (Pad.Newpress.Start) {
		quit();
	}

	// si on touche le sprite pour quitter, on quitte
	if (PA_SpriteTouched(AFRODS_SPRITE_GAME_ICON_QUIT)) {
		PA_WaitFor(Stylus.Released);
		quit();
	}

	// Déplacement du personnage
	moveChar();
}

void Game::initMenu() {
	Coords coords;
	// chargement du background
	PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_game_bottom);

	// chargement de la palette
	PA_LoadSpritePal(ECRAN_BAS, AFRODS_PAL_TOP_GAME, (void*)palGame_Pal);

	// on charge les sprites de l'écran du bas
	coords.x = AFRODS_GAME_OFFSET_ICONS_X;
	coords.y = AFRODS_GAME_OFFSET_ICONS_Y;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_STATUS, (void*)spr_game_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_GAME, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_STATUS, AFRODS_GAME_ICONS_FRAME_STATUS);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_INVENTORY, (void*)spr_game_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_GAME, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_INVENTORY, AFRODS_GAME_ICONS_FRAME_INVENTORY);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_EQUIPMENT, (void*)spr_game_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_GAME, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_EQUIPMENT, AFRODS_GAME_ICONS_FRAME_EQUIPMENT);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_OPTIONS, (void*)spr_game_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_GAME, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_OPTIONS, AFRODS_GAME_ICONS_FRAME_OPTIONS);

	coords.y += 32 + AFRODS_GAME_OFFSET_ICONS_SPACE;
	PA_CreateSprite(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_QUIT, (void*)spr_game_icons_Sprite, OBJ_SIZE_32X32, 1, AFRODS_PAL_TOP_GAME, coords.x, coords.y);
	PA_SetSpriteAnim(ECRAN_BAS, AFRODS_SPRITE_GAME_ICON_QUIT, AFRODS_GAME_ICONS_FRAME_QUIT);
}

bool Game::moveChar() {
	bool hasMoved = false;

	// si on commence à appuyer, on lance l'animation
	if(Pad.Newpress.Up) {
		PA_StartSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 0, 2, 6);
		hasMoved = true;
	}
	if(Pad.Newpress.Down) {
		PA_StartSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 6, 8, 6);
		hasMoved = true;
	}
	if(Pad.Newpress.Right) {
		PA_StartSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 3, 5, 6);
		hasMoved = true;
	}
	if(Pad.Newpress.Left) {
		PA_StartSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 9, 11, 6);
		hasMoved = true;
	}

	// si on est pas en train d'appuyer, on stoppe l'animation
	if(!((Pad.Held.Left)||(Pad.Held.Up)||(Pad.Held.Down)||(Pad.Held.Right))) {
		PA_SpriteAnimPause(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 1);
	}

	// si on relâche la direction, on se remet dans la bonne frame
	if (Pad.Released.Up) {
		PA_SetSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 1);
	}
	if (Pad.Released.Down) {
		PA_SetSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 7);
	}
	if (Pad.Released.Right) {
		PA_SetSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 4);
	}
	if (Pad.Released.Left) {
		PA_SetSpriteAnim(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, 10);
	}

	// Déplacement du personnage
	if (Pad.Held.Right && m_activeChar.getPosX() < (m_activeMap.getWidth()) * 16 - AFRODS_GAME_PERSO_WIDTH) {
		m_activeChar.setPosX(m_activeChar.getPosX() + m_activeChar.getMoveSpeed());
	}
	if (Pad.Held.Left && m_activeChar.getPosX() > 0) {
		m_activeChar.setPosX(m_activeChar.getPosX() - m_activeChar.getMoveSpeed());
	}
	if (Pad.Held.Down && m_activeChar.getPosY() < (m_activeMap.getHeight()) * 16 - AFRODS_GAME_PERSO_HEIGHT) {
		m_activeChar.setPosY(m_activeChar.getPosY() + m_activeChar.getMoveSpeed());
	}
	if (Pad.Held.Up && m_activeChar.getPosY() > 0) {
		m_activeChar.setPosY(m_activeChar.getPosY() - m_activeChar.getMoveSpeed());
	}

	// on calcule les coordonnées où afficher le perso
	Coords coords;
	if (m_activeChar.getPosX() < AFRODS_SCREEN_WIDTH / 2 - AFRODS_GAME_OFFSET_TILES_X) {
		// s'il est proche de la gauche, on récupère directement sa position
		coords.x = m_activeChar.getPosX() - AFRODS_GAME_OFFSET_TILES_X;
		// pas de scrolling
		hasMoved = false;
	} else if (m_activeChar.getPosX() > ((m_activeMap.getWidth()-1) * 16) - AFRODS_SCREEN_WIDTH / 2 - AFRODS_GAME_OFFSET_TILES_X) {
		// s'il est proche de la droite, on calcule sa position par rapport à la droite de l'écran
		coords.x = AFRODS_SCREEN_WIDTH - ((m_activeMap.getWidth()-1) * 16 - m_activeChar.getPosX()) - AFRODS_GAME_OFFSET_TILES_X;
		// pas de scrolling
		hasMoved = false;
	} else {
		// s'il n'est pas près du bord, c'est au centre
		coords.x = AFRODS_SCREEN_WIDTH / 2 - AFRODS_GAME_PERSO_WIDTH / 2;
		// et donc on doit scroller
		if (Pad.Held.Left || Pad.Held.Right) {
			PA_EasyBgScrollX(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, m_activeChar.getPosX() - coords.x);
		}
	}
	if (m_activeChar.getPosY() < AFRODS_SCREEN_HEIGHT / 2 - AFRODS_GAME_OFFSET_TILES_Y) {
		// s'il est proche du haut, on récupère directement sa position
		coords.y = m_activeChar.getPosY() - AFRODS_GAME_OFFSET_TILES_Y;
		// pas de scrolling
		hasMoved = false;
	} else if (m_activeChar.getPosY() > ((m_activeMap.getHeight()-1) * 16) - AFRODS_SCREEN_HEIGHT / 2 - AFRODS_GAME_OFFSET_TILES_Y) {
		// s'il est proche du bas, on calcule sa position par rapport au bas de l'écran
		coords.y = AFRODS_SCREEN_HEIGHT - ((m_activeMap.getHeight()-1) * 16 - m_activeChar.getPosY()) - AFRODS_GAME_OFFSET_TILES_Y;
		// pas de scrolling
		hasMoved = false;
	} else {
		// s'il n'est pas près du bord, c'est au centre
		coords.y = AFRODS_SCREEN_HEIGHT / 2 - AFRODS_GAME_PERSO_HEIGHT / 2;
		// et donc on doit scroller
		if (Pad.Held.Down || Pad.Held.Up) {
			PA_EasyBgScrollY(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, m_activeChar.getPosY() - coords.y);
		}
	}

	// On repositionne le sprite
	PA_SetSpriteXY(ECRAN_HAUT, AFRODS_SPRITE_GAME_PERSO, coords.x, coords.y);

	// on renvoie true si le perso a été déplacé
	return hasMoved;
}

void Game::quit()
{
	// on indique qu'on veut sortir
	m_bIsStopped = true;

	// pour aller dans le module Splash
	G_Env.NextModule = AFRODS_MODULE_SPLASH;
}

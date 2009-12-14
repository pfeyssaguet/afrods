#include "newchar.h"
#include "constants.h"
#include "externs.h"
#include "all_gfx.h"
#include <PA9.h>

using namespace AfroDS;

NewChar::NewChar() : m_sCharName("") {
	// initialisation pour la police en smart
	PA_Init8bitBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_8BIT); // init du bg 8bit
	PA_SetBgPrio(ECRAN_BAS, AFRODS_LAYER_BOTTOM_8BIT, 0); // on le passe au 1er plan

	// on charge la palette de la police
	PA_Load8bitBgPal(ECRAN_BAS, (void*)bg_font_menu_Pal); // chargement de la palette des polices du menu
	PA_8bitCustomFont(AFRODS_FONT_MENU, bg_font_menu);

	// on charge les 2 backgrounds du module NewChar
	PA_LoadTiledBg(ECRAN_HAUT, AFRODS_LAYER_TOP_BG, bg_newchar_top);;
	PA_LoadTiledBg(ECRAN_BAS, AFRODS_LAYER_BOTTOM_BG, bg_newchar_bottom);

	// initialisation du clavier
	PA_InitKeyboard(AFRODS_LAYER_BOTTOM_KEYBOARD);

	// on fait apparaître le clavier
	PA_KeyboardIn(24, 90);
}

NewChar::~NewChar() {
	// on fait disparaître le clavier
	PA_KeyboardOut();
	PA_ResetBgSys();
}

void NewChar::moduleEvents() {
	// si on appuie sur Start, on lance la création du perso
	if (Pad.Newpress.Start) {
		createChar();
	}

	// si on appuie sur B, on sort
	if (Pad.Newpress.B) {
		// on va quitter le module
		m_bIsStopped = true;

		// on retourne au menu
		G_Env.NextModule = AFRODS_MODULE_MENU;
	}

	// gestion du clavier : on récupère la touche éventuellement entrée
	char readKeyboard = PA_CheckKeyboard();

	// si la touche est différente de 0 alors le clavier a été utilisé
	if (readKeyboard) {
		// gestion des touches spéciales du clavier
		if (readKeyboard == PA_BACKSPACE) {
			// si le nom n'est pas vide, on efface la dernière lettre
			if (m_sCharName.length() > 0) {
				// on efface la dernière lettre
				m_sCharName = m_sCharName.substr(0, m_sCharName.length() - 1);

				// on l'efface l'écran
				PA_Clear8bitBg(ECRAN_BAS);
			}
		} else if (readKeyboard == PA_ENTER) {
			// on lance la création du perso
			createChar();
		} else {
			// on ajoute la lettre au nom du perso
			m_sCharName += readKeyboard;

			size_t size = m_sCharName.size() + 1;
			char * buffer = new char[size];
			// copier la chaîne
			strncpy(buffer, m_sCharName.c_str(), size );

			// on affiche le nouveau nom à l'écran
			PA_SmartText(ECRAN_BAS,
				56, 56,
				56 + 192, 56 + 16,
				buffer, 1, AFRODS_FONT_MENU, 1, 100
			);

			delete[] buffer;
		}
	}
}

void NewChar::createChar() {
	// si le perso n'a pas de nom, on sort
	if (m_sCharName.length() == 0) {
		return;
	}

	// on doit créer un nouveau perso
	Character newchar = Character(m_sCharName);

	// on l'ajoute au module de sauvegarde
	G_Env.save->addCharacter(newchar);

	// on va quitter le module
	m_bIsStopped = true;

	// on retourne au menu
	G_Env.NextModule = AFRODS_MODULE_MENU;
}

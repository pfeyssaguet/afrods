#include "newchar.h"

NewChar::NewChar() : m_sCharName("") {
	PA_OutputText(ECRAN_HAUT, 2, 2, "Enter your name");
	PA_InitKeyboard(AFRODS_LAYER_BG);
	PA_KeyboardIn(10, 10);
}

NewChar::~NewChar() {
	PA_ClearTextBg(ECRAN_HAUT);
	PA_KeyboardOut();
}

void NewChar::moduleEvents() {
	if (Pad.Newpress.Start) {
		m_bIsStopped = true;
		G_Env.NextModule = AFRODS_MODULE_GAME;
	}

	char readKeyboard = PA_CheckKeyboard();
	if (readKeyboard) {
		if (readKeyboard == PA_BACKSPACE) {
			if (m_sCharName.length() > 0) {
				// on efface la dernière lettre
				m_sCharName = m_sCharName.substr(0, m_sCharName.length() - 1);
				// on l'efface à l'écran en affichant un espace à sa place
				PA_OutputText(ECRAN_HAUT, 8 + m_sCharName.length(), 6, " ");
			}
		} else {
			m_sCharName += readKeyboard;
		}

		PA_OutputText(ECRAN_HAUT, 8, 6, m_sCharName.c_str());
	}

}

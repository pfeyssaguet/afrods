#ifndef __EXTERNS_H__
#define __EXTERNS_H__

#include "constants.h"
#include "module.h"
#include "save.h"

using namespace AfroDS;

namespace AfroDS {

	/**
	 * Structure destinée à contenir les "variables d'environnement"
	 */
	struct Env
	{
		/** Permet d'indiquer le prochain module à charger */
		AFRODS_MODULE NextModule;

		/** Le personnage sélectionné */
		Character ActiveChar;

		/** Les données de sauvegarde */
		Save * save;

		/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
		Module * currentModule;
	};

	/**
	 * Référence vers G_Env, déclaré dans globals.cpp
	 */
	extern Env G_Env;

}

#endif

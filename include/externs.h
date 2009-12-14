#ifndef __EXTERNS_H__
#define __EXTERNS_H__

#include "constants.h"
#include "module.h"
#include "save.h"

using namespace AfroDS;

namespace AfroDS {

	/**
	 * Structure destin�e � contenir les "variables d'environnement"
	 */
	struct Env
	{
		/** Permet d'indiquer le prochain module � charger */
		AFRODS_MODULE NextModule;

		/** Le personnage s�lectionn� */
		Character ActiveChar;

		/** Les donn�es de sauvegarde */
		Save * save;

		/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
		Module * currentModule;
	};

	/**
	 * R�f�rence vers G_Env, d�clar� dans globals.cpp
	 */
	extern Env G_Env;

}

#endif

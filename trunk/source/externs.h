#ifndef EXTERNS_H_
#define EXTERNS_H_

#include "constants.h"
#include "module.h"
#include "save.h"

/**
 * Structure destinée à contenir les "variables d'environnement"
 */
typedef struct AF_Env
{
	/** Les données de sauvegarde */
	Save * save;

	/** Permet d'indiquer le prochain module à charger */
	AFRODS_MODULE NextModule;

	/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
	Module * currentModule;
} AF_Env;

/**
 * Référence vers G_Env, déclaré dans globals.cpp
 */
extern AF_Env G_Env;

#endif /*EXTERNS_H_*/

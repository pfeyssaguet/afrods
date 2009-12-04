#ifndef EXTERNS_H_
#define EXTERNS_H_

#include "constants.h"
#include "module.h"
#include "save.h"

/**
 * Structure destin�e � contenir les "variables d'environnement"
 */
typedef struct AF_Env
{
	/** Les donn�es de sauvegarde */
	Save * save;

	/** Permet d'indiquer le dernier module par lequel on est pass� */
	AFRODS_MODULE LastModule;

	/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
	Module * currentModule;
} AF_Env;

/**
 * R�f�rence vers G_Env, d�clar� dans globals.cpp
 */
extern AF_Env G_Env;

#endif /*EXTERNS_H_*/

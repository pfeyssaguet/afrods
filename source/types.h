#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * Structure pour d�crire un couple de coordonn�es
 */
typedef struct AF_Coords
{
	int x;
	int y;
} AF_Coords;

/**
 * Structure pour d�finir le personnage
 */
typedef struct AF_Perso
{
	/** Nom du perso */
	char * sName;
	
	/** Position du perso � l'�cran */
	AF_Coords position;
} AF_Perso;

/**
 * Structure destin�e � contenir les "variables d'environnement"
 */
typedef struct AF_Env
{
	/** Le perso */
	AF_Perso Perso;
	
	/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
	int Module;
} AF_Env;

#endif

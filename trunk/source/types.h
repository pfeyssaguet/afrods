#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * Structure pour décrire un couple de coordonnées
 */
typedef struct AF_Coords
{
	int x;
	int y;
} AF_Coords;

/**
 * Structure pour définir le personnage
 */
typedef struct AF_Perso
{
	/** Nom du perso */
	char * sName;
	
	/** Position du perso à l'écran */
	AF_Coords position;
} AF_Perso;

/**
 * Structure destinée à contenir les "variables d'environnement"
 */
typedef struct AF_Env
{
	/** Le perso */
	AF_Perso Perso;
	
	/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
	int Module;
} AF_Env;

#endif

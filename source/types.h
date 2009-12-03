#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * Structure pour stocker les �l�ments du menu
 */
typedef struct AF_Menu
{
	int iActiveMenu;
	int iNbMenus;
} AF_Menu;

/**
 * Structure pour d�crire un couple de coordonn�es
 */
typedef struct AF_Coords
{
	int x;
	int y;
} AF_Coords;

/**
 * Structure pour d�finir un personnage
 */
typedef struct AF_Perso
{
	/** Nom du perso */
	char * sName;
	
	/** Position du perso � l'�cran */
	AF_Coords position;
} AF_Perso;

typedef struct AF_SavePerso
{
	char * sName;

	struct AF_SavePerso * next;

	struct AF_SavePerso * prev;
} AF_SavePerso;

typedef struct AF_Save
{
	/** Les persos */
	AF_SavePerso * persos;
} AF_Save;

/**
 * Structure destin�e � contenir les "variables d'environnement"
 */
typedef struct AF_Env
{
	/** Les donn�es du menu */
	AF_Menu Menu;

	/** Les donn�es de sauvegarde */
	AF_Save Save;
	
	/** Le perso actif */
	AF_Perso Perso;
	
	/** Permet d'indiquer le module actuel, pour savoir si on est dans le menu ou en jeu */
	int Module;

	/** Permet d'indiquer qu'on veut sortir du module */
	int ModuleStop;
} AF_Env;

#endif

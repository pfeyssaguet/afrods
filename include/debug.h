#ifndef __DEBUG_H__
#define __DEBUG_H__

// OPTIONS DE DEBUG

// activer le mode debug en d�commentant cette ligne
#define AFRODS_DEBUG

#ifdef AFRODS_DEBUG

// afficher la map de collision � la place de la map Floor => fait bugger les map generated :s
//#define AFRODS_DEBUG_SHOW_COLLISION_MAP

// d�sactiver les collisions du personnage
//#define AFRODS_DEBUG_NOCLIP

// vitesse du personnage (normalement AFRODS_CHAR_SPEED qui doit valoir 1)
#define AFRODS_DEBUG_CHAR_SPEED 2

#endif

#endif

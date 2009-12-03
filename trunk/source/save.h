#ifndef __SAVE_H__
#define __SAVE_H__

#include "afrods.h"


void AF_SaveInit();

int AF_SaveGetNbPersos();

void AF_SaveLoadPersos();

int AF_SavePersoCount();

void AF_SavePersoAdd(char * sNom);

void AF_SavePersoClear();

#endif

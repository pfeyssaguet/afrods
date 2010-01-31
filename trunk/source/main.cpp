#ifndef ARM9
#define ARM9
#endif

#include "main.h"
#include "game.h"

using namespace AfroDS;

volatile int frame = 0;

void Vblank() {
	// fonction un peu bidon mais c'est pour test le fait d'appeler
	// une fonction perso à chaque vblank (fin de rafraîchissement vertical)
	frame++;
}

int main(int argc, char ** argv) {
	// Initialisations principales
	Game * game = Game::getInstance();
	game->init();

	// Boucle principale
	while (true) {
		game->run();
	}
	return 0;
}

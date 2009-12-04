#ifndef __SAVE_H__
#define __SAVE_H__

#include "character.h"
#include <vector>

class Save {
	public:
		Save();

		void loadPersos();
		int getNbCharacters();
		std::vector<Character> getCharacters();

	private:

		std::vector<Character> m_characters;
		//AF_SavePerso * m_persos;
};


#endif

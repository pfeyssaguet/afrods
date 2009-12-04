#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "types.h"
#include <string>

class Character {
	public:
		Character();
		Character(std::string sName);

		std::string getName();
		void setName(std::string sName);
		void setPosX(int x);
		void setPosY(int y);
		void setPosXY(int x, int y);
		void setPos(AF_Coords pos);
		int getPosX();
		int getPosY();
		AF_Coords getPos();

	private:
		std::string m_sName;
		AF_Coords m_position;
};

#endif

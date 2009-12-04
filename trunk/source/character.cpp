/*
 * character.cpp
 *
 *  Created on: 3 déc. 2009
 *      Author: deuspi
 */

#include "character.h"

using namespace std;

Character::Character() {

}

Character::Character(string sName) {
	m_sName = sName;
}

string Character::getName() {
	return m_sName;
}
void Character::setName(string sName) {
	m_sName = sName;
}

void Character::setPosX(int x) {
	m_position.x = x;
}

void Character::setPosY(int y) {
	m_position.y = y;
}

void Character::setPosXY(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

void Character::setPos(AF_Coords pos) {
	m_position = pos;
}

int Character::getPosX() {
	return m_position.x;
}

int Character::getPosY() {
	return m_position.y;
}

AF_Coords Character::getPos() {
	return m_position;
}

#include "character.h"

using namespace AfroDS;

/**
 * Constructeur par d�faut
 */
Character::Character() : m_move_speed(1) {

}

/**
 * Constructeur initialisant le nom
 * @param std::string sName nom du personnage
 */
Character::Character(const std::string sName) : m_move_speed(1) {
	m_sName = sName;
}

/**
 * Renvoie le nom du personnage
 * @return std::string nom du personnage
 */
std::string Character::getName() const {
	return m_sName;
}

/**
 * D�finit le nom du personnage
 * @param std::string sName nom du personnage
 */
void Character::setName(const std::string sName) {
	m_sName = sName;
}

/**
 * Renvoie la position X
 * @return int position X
 */
int Character::getPosX() const {
	return m_position.x;
}

/**
 * D�finit la position X
 * @param int x position X
 */
void Character::setPosX(const int x) {
	m_position.x = x;
}

/**
 * Renvoie la position Y
 * @return int position Y
 */
int Character::getPosY() const {
	return m_position.y;
}

/**
 * D�finit la position Y
 * @param int y position Y
 */
void Character::setPosY(const int y) {
	m_position.y = y;
}

/**
 * Renvoie la position avec un type personnalis�
 * @return AF_Coords position
 */
Coords Character::getPos() const {
	return m_position;
}

/**
 * D�finit la position avec un type personnalis�
 * @param AF_Coords pos position
 */
void Character::setPos(const Coords pos) {
	m_position = pos;
}

/**
 * D�finit les positions de X et Y
 * @param int x position X
 * @param int y position Y
 */
void Character::setPosXY(const int x, const int y) {
	m_position.x = x;
	m_position.y = y;
}

/**
 * Renvoie la vitesse de d�placement du personnage
 */
int Character::getMoveSpeed() const {
	return m_move_speed;
}

#include "character.h"

using namespace AfroDS;

/**
 * Constructeur par défaut
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
 * Définit le nom du personnage
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
 * Définit la position X
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
 * Définit la position Y
 * @param int y position Y
 */
void Character::setPosY(const int y) {
	m_position.y = y;
}

/**
 * Renvoie la position avec un type personnalisé
 * @return AF_Coords position
 */
Coords Character::getPos() const {
	return m_position;
}

/**
 * Définit la position avec un type personnalisé
 * @param AF_Coords pos position
 */
void Character::setPos(const Coords pos) {
	m_position = pos;
}

/**
 * Définit les positions de X et Y
 * @param int x position X
 * @param int y position Y
 */
void Character::setPosXY(const int x, const int y) {
	m_position.x = x;
	m_position.y = y;
}

/**
 * Renvoie la vitesse de déplacement du personnage
 */
int Character::getMoveSpeed() const {
	return m_move_speed;
}

/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * implementation of the player class. it stores all of the player data like its position and 
 * current weapon and current/max hp
 */

#include "Player.h"
#include "Weapon.h"

Player::Player(){
    this->hp = 50;
    this->maxHP = 50;
    this->xPos = 0;
    this->yPos = 0;
}

int Player::getHP() const {
    return this->hp;
}

int Player::getMaxHP() const {
    return this->maxHP;
}

int Player::getXPos() const{
    return this->xPos;
}

int Player::getYPos() const{
    return this->yPos;
}

Weapon Player::getCurrWeapon() const{
    return this->currWeapon;
}

void Player::updateHP(const int TO_ADD){
    this->hp += TO_ADD;
}

void Player::updateMaxHP(const int TO_ADD){
    this->maxHP += TO_ADD;
}

void Player::fillHP(){
    this->hp = this->maxHP;
}

void Player::updateXPos(const int NEW_POS){
    //changes the player's x pos to the new pos
    this->xPos = NEW_POS;
}

void Player::updateYPos(const int NEW_POS){
    //changes the player's y pos to the new pos
    this->yPos = NEW_POS;
}

void Player::addWeapon(const Weapon WEAPON_TO_ADD){
    this->weaponList.push_back(WEAPON_TO_ADD);
    this->currWeapon = WEAPON_TO_ADD;
}
#include "Player.h"


Player::Player(){
    this->hp = 5;
    this->maxHP = 5;
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

std::string Player::getWeaponAtPos(const int POS){
    return this->weaponList.at(POS);
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
    //if the bool is true, update xPos by one (like stepping to the right once),otherwise opp
    this->xPos = NEW_POS;
}

void Player::updateYPos(const int NEW_POS){
    //if the bool is true, update yPos down by one (like stepping down once),otherwise opp
    this->yPos = NEW_POS;
}

void Player::addWeapon(const std::string WEAPON_TO_ADD){
    this->weaponList.push_back(WEAPON_TO_ADD);
}
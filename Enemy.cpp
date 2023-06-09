/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * implementation of the enemy class. its level can be set, which determines its maxhp and damage output
 */

#include "Enemy.h"

Enemy::Enemy(){
    this->maxHP = 10;
    this->currHP = this->maxHP;
    this->damageCapability = 1;
}

int Enemy::getMaxHP() const {
    return this->maxHP;
} 

int Enemy::getCurrHP() const {
    return this->currHP;
}

int Enemy::getDamageCapability() const {
    return this->damageCapability;
}

void Enemy::setEnemyLevel(const int LEVEL){
    this->maxHP = 10 * LEVEL;
    this->currHP = this->maxHP;
    this->damageCapability = 5 * LEVEL;
}

void Enemy::setCurrHP(const int AMT){
    this->currHP += AMT;
}
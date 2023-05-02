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
#ifndef ENEMY_HPP
#define ENEMY_HPP
class Enemy{
public:
    Enemy();
    int getMaxHP() const;
    int getCurrHP() const;
    int getDamageCapability() const;
    void setEnemyLevel(const int LEVEL);
    void setCurrHP(const int AMT);
private:
    int maxHP;
    int currHP;
    int damageCapability;
};

/**
 * @brief default constructor
*/
Enemy::Enemy(){
    this->maxHP = 10;
    this->currHP = this->maxHP;
    this->damageCapability = 1;
}

/**
 * @brief getter function for the maxHP
*/
int Enemy::getMaxHP() const {
    return this->maxHP;
} 

/**
 * @brief getter function for the currHP
*/
int Enemy::getCurrHP() const {
    return this->currHP;
}

/**
 * @brief getter function for the damageCapability
*/
int Enemy::getDamageCapability() const {
    return this->damageCapability;
}

/**
 * @brief sets up the enemy's stats based on what level its supposed to be
*/
void Enemy::setEnemyLevel(const int LEVEL){
    this->maxHP = 10 * LEVEL;
    this->currHP = this->maxHP;
    this->damageCapability = 5 * LEVEL;
}

/**
 * @brief mutator function for currHP. adds the amount of HP in AMT
*/
void Enemy::setCurrHP(const int AMT){
    this->currHP += AMT;
}
#endif
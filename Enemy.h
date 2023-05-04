/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * header file for the Enemy class
 */

#ifndef ENEMY_H
#define ENEMY_H

class Enemy{
public:
/**
 * @brief constructor
*/
    Enemy();

/**
 * @brief getter function for the maxHP
*/
    int getMaxHP() const;

/**
 * @brief getter function for the currHP
*/
    int getCurrHP() const;

/**
 * @brief getter function for the damageCapability
*/
    int getDamageCapability() const;

/**
 * @brief sets up the enemy's stats based on what level its supposed to be
*/
    void setEnemyLevel(const int LEVEL);

/**
 * @brief mutator function for currHP. adds the amount of HP in AMT
*/
    void setCurrHP(const int AMT);
private:
    int maxHP;
    int currHP;
    int damageCapability;
};
#endif
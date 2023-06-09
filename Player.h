/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * header file for the player class
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"

#include <vector>

class Player{

public:
/**
 * @brief Construct a new Player object
 */
    Player();

    //all the accessor functions
    int getHP() const;
    int getMaxHP() const;
    int getXPos() const;
    int getYPos() const;
    Weapon getCurrWeapon() const;


    //all the mutator functions
    void updateHP(const int TO_ADD);
    void updateMaxHP(const int TO_ADD);
    void fillHP();
    void updateXPos(const int NEW_POS);
    void updateYPos(const int NEW_POS);

    /**
     * @brief adds the new weapon to the player's inventory then makes that weapon the player's current weapon
    */
    void addWeapon(const Weapon WEAPON_TO_ADD);

private:
    int hp;
    int maxHP;
    int xPos;
    int yPos;
    std::vector<Weapon> weaponList;
    Weapon currWeapon;
};
#endif
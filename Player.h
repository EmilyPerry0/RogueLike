#ifndef PLAYER_H
#define PLAYER_H

#include <string>
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
    std::string getWeaponAtPos(const int POS);

    //all the mutator functions
    void updateHP(const int TO_ADD);
    void updateMaxHP(const int TO_ADD);
    void fillHP();
    void updateXPos(const int NEW_POS);
    void updateYPos(const int NEW_POS);
    void addWeapon(const std::string WEAPON_TO_ADD);

private:
    int hp;
    int maxHP;
    int xPos;
    int yPos;
    std::vector<std::string> weaponList;
};
#endif
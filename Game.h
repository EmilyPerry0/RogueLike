#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"

#include <fstream>
#include <vector>


class Game{
    public:
/**
 * @brief constructs a new Game object
*/
    Game();
/**
 * @brief main game
 */
    void playGame();

/**
 * @brief initializes all possible weapons
 * @return the vector containing all weapons
*/
    std::vector<Weapon> initWeapons();

/**
 * @brief loads level data from premade files into a 2d array to prep for gameplay 
*/
    void loadNextLevel();

/**
 * @brief getter function for things in the level array
 * @return the char at a certain position in the level array
*/
    char getElementAtPos(const int X_POS, const int Y_POS) const;

/**
 * @brief getter function for inEnemyEncounter
*/
    bool getInEnemyEncounter() const;

/**
 * @brief updates the player's position based on the key pressed
*/
    void updatePlayerPos(const char KEY);

/**
 * @brief updates the player's positon based on which direction they should move
*/
    void playerSpaceCheckAndUpdate(const int PLAYER_X_POS_CHANGE, const int PLAYER_Y_POS_CHANGE);

/**
 * @brief sets up a new enemy with the appropriate stats
*/
    void setUpNewEnemy();

/**
 * @brief does damage to the enemy and the enemy does damage to the player
*/
    void attack();

    private:
    std::vector<Weapon> allWeapons;
    std::ofstream outputFile;
    std::ifstream levelFile;
    int currLevel;
    char levelArray[40][60];
    const int MAX_X = 60;
    const int MAX_Y = 40;
    Player player;
    Enemy currEnemy;
    bool inEnemyEncounter;
    bool inChestOpening;
};
#endif
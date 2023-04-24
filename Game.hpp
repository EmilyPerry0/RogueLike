#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "item.hpp"
#include "Player.hpp"

class Game{
    public:
    Game();
    void playGame();
    std::vector<Item> initItems();
    void loadNextLevel();
    char getElementAtPos(const int X_POS, const int Y_POS) const;
    void updatePlayerPos(char direction);
    void playerSpaceCheckAndUpdate(const int PLAYER_X_POS_CHANGE, const int PLAYER_Y_POS_CHANGE);
    
    private:
    std::vector<Item> items;
    std::ofstream outputFile;
    std::ifstream levelFile;
    int currLevel;
    char levelArray[40][60];
    const int MAX_X = 60;
    const int MAX_Y = 40;
    Player player;

};

/**
 * @brief constructs a new Game object
*/
Game::Game(){
    this->items = initItems();
    this->currLevel = 0;
}

/**
 * @brief main game loop
 * 
 */
void Game::playGame(){
    //start by going to the first level
    this->loadNextLevel();
}

/**
 * @brief initializes all possible items
 * @return the vector containing all items
*/
std::vector<Item> Game::initItems(){
    std::cout << "Initializing all items..." << std::endl;

    std::vector<Item> items;

    Item shortSword("Short Sword", 'W', "The most basic sword.", 5);

    items.push_back(shortSword);

    return items;
}

/**
 * @brief loads level data from premade files into a 2d array to prep for gameplay 
 */
void Game::loadNextLevel(){
    //levels are 60*40 rectangles
    //character key: # = wall, P = player, E = exit space
    int xPos;
    int yPos;

    //player wins
    if(this->currLevel == 6){
        //go to hub
    }

    this->levelFile.open("levels/level" + std::to_string(this->currLevel) + ".txt");
    //make sure the level file was properly opened
    if(!this->levelFile){
        std::cout << "file not opened";
    }
    //go through the level and enter it into a 2d array to make operations easier
    for(int row = 0; row < 40; row++){
        for(int col = 0; col < 60; col++){
            this->levelFile >> std::noskipws >> this->levelArray[row][col];
        }
        //skip the newline characters
        this->levelFile.ignore();
    }

    //load up the level's start pos
    this->levelFile >> xPos >> std::skipws >> yPos;

    //set the player's x and y pos to the level's starting pos
    this->player.updateXPos(xPos);
    this->player.updateYPos(yPos);
    this->levelArray[yPos][xPos] = 'P';

    //cleanup
    this->levelFile.close();
}

/**
 * @brief getter function for things in the level array
 * @return the char at a certain position in the level array
*/
char Game::getElementAtPos(const int X_POS, const int Y_POS) const {
    return this->levelArray[Y_POS][X_POS];
}

/**
 * @brief updates the player's position based on the key pressed
*/
void Game::updatePlayerPos(const char KEY){
    //player moving up
    if(KEY == 'w'){
        playerSpaceCheckAndUpdate(0, -1);
    //player moving left
    }else if(KEY == 'a'){
        playerSpaceCheckAndUpdate(-1, 0);
    //player moving down
    }else if(KEY == 's'){
        playerSpaceCheckAndUpdate(0, 1);
    //player moving right
    }else if(KEY == 'd'){
        playerSpaceCheckAndUpdate(1, 0);
    }
}

/**
 * @brief updates the player's positon based on which direction they should move
*/
void Game::playerSpaceCheckAndUpdate(const int PLAYER_X_POS_CHANGE, const int PLAYER_Y_POS_CHANGE){
    int playerXPos = this->player.getXPos();
    int playerYPos = this->player.getYPos();
    //make sure the space the player wants to move to is open
    if(this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] != '#'){
        if(this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] == 'E'){
            //the player has reached the end space, so load the next level
            this->currLevel++;
            this->loadNextLevel();
        }else{
            //if it is, update the level array and the player's current position
            if(PLAYER_X_POS_CHANGE != 0){
                this->player.updateXPos(playerXPos + PLAYER_X_POS_CHANGE);
            }else{
                this->player.updateYPos(playerYPos + PLAYER_Y_POS_CHANGE);
            }
            this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] = 'P';
            this->levelArray[playerYPos][playerXPos] = ' ';
        }
    }
}

#endif
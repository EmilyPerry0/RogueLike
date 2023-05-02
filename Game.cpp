#include "Game.h"

#include <iostream>

Game::Game(){
    this->weapons = initWeapons();
    this->currLevel = 0;
    this->inEnemyEncounter = false;
}

void Game::playGame(){
    //start by going to the first level
    this->loadNextLevel();
}


std::vector<Weapon> Game::initWeapons(){
    std::vector<Weapon> weapons;
    Weapon shortSword("Short Sword", 5);
    weapons.push_back(shortSword);
    return weapons;
}

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

char Game::getElementAtPos(const int X_POS, const int Y_POS) const {
    return this->levelArray[Y_POS][X_POS];
}

bool Game::getInEnemyEncounter() const{
    return this->inEnemyEncounter;
}

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

void Game::playerSpaceCheckAndUpdate(const int PLAYER_X_POS_CHANGE, const int PLAYER_Y_POS_CHANGE){
    int playerXPos = this->player.getXPos();
    int playerYPos = this->player.getYPos();
    //make sure the space the player wants to move to is open
    if(this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] != '#'){
        if(this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] == 'E'){
            //the player has reached the end space, so load the next level
            this->currLevel++;
            this->loadNextLevel();
        }else if(this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE] == 'M'){
            //player has run into an enemy. run enemy encounter
            this->inEnemyEncounter = true;
            this->setUpNewEnemy();
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

void Game::setUpNewEnemy(){
    this->currEnemy.setEnemyLevel(this->currLevel);
}

void Game::attack(){
    //damage the enemy
    // this->currEnemy.setCurrHP(-1*)
}

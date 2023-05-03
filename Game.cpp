#include "Game.h"

#include <iostream>

Game::Game(){
    this->allWeapons = initWeapons();
    this->allChests = initChests();
    this->player.addWeapon(allWeapons.at(0));
    this->currLevel = 0;
    this->inEnemyEncounter = false;
    this->inChestOpening = false;
}

void Game::playGame(){
    //start by going to the first level
    this->loadNextLevel();
}


std::vector<Weapon> Game::initWeapons(){
    std::vector<Weapon> allWeapons;

    //initialize all the weapons
    Weapon stick("Stick", 1);
    Weapon shortSword("Short Sword", 5);

    //add the weapons to the weapons vector
    allWeapons.push_back(stick);
    allWeapons.push_back(shortSword);

    return allWeapons;
}

std::vector<Chest> Game::initChests(){
    std::vector<Chest> allChests;

    //initialize all the weapons
    Chest stickChest(this->allWeapons.at(0));
    Chest shortSwordChest(this->allWeapons.at(1));

    //add the chests to the chests vector
    allChests.push_back(stickChest);
    allChests.push_back(shortSwordChest);

    return allChests;
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
    char spaceToCheck = this->levelArray[playerYPos  + PLAYER_Y_POS_CHANGE][playerXPos + PLAYER_X_POS_CHANGE];
    //make sure the space the player wants to move to is open
    if(spaceToCheck != '#'){
        if(spaceToCheck >= 48 && spaceToCheck <= 57){
            //player has run into a chest, run chest opening sequence
            this->inChestOpening = true;
            this->openChest(spaceToCheck-48);
        }
        if(spaceToCheck == 'M'){
            //player has run into an enemy. run enemy encounter
            this->inEnemyEncounter = true;
            this->setUpNewEnemy();
        }
        if(spaceToCheck == 'E'){
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

void Game::setUpNewEnemy(){
    this->currEnemy.setEnemyLevel(this->currLevel + 1);
}

void Game::attack(){
    //damage the enemy
    this->currEnemy.setCurrHP(-1*(this->player.getCurrWeapon().getDamage()));

    //check to see if the enemy is dead
    if(this->currEnemy.getCurrHP() <= 0){
        //leave the encounter
        this->inEnemyEncounter = false;
        std::cout << "enemy HP: " << currEnemy.getCurrHP() << std::endl
                  << "your HP: " << player.getHP() << std::endl;
    }

    //enemy damages player
    this->player.updateHP(-1*(this->currEnemy.getDamageCapability()));

    //check to see if the player is dead
    if(this->player.getHP() <= 0){
        this->inEnemyEncounter = false;
    }
}

bool Game::getInChestOpening(){
    return this->inChestOpening;
}

void Game::openChest(const int CHEST_NUM){
    this->player.addWeapon(this->allChests.at(CHEST_NUM).getChestContents());
}

Weapon Game::getCurrWeapon(){
    return this->player.getCurrWeapon();
}

void Game::leaveChestOpening(){
    //delete the chest from the level array
    this->inChestOpening = false;
}
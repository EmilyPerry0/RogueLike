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
    void beginGame();
    bool doSavesExist();
    void newGame();
    void playGame();
    std::vector<Item> initItems();
    void loadNextLevel();
    void playLevel();
    char getElementAtPos(const int X_POS, const int Y_POS) const;
    
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

Game::Game(){
    this->items = initItems();
    this->currLevel = 0;
}

/**
 * @brief runs on start, moves into newGame after a couple steps
 * 
 */
void Game::beginGame(){
    char input;
    std::cout << "Starting..." << std::endl;
    do{
        std::cout << "Would you like to (l)oad a previous save or (c)reate a new one?" << std::endl;
        std:: cin >> input; 
        if(input != 'l' && input != 'c'){
           std::cout << "That was not a valid choice. Please enter 'l' for load or 'c' for create" << std::endl;
        }
    }while(input != 'l' && input != 'c');
    if(input == 'l'){
        //print out all game log files with numbers in front of them
        //could also be nice to display each save's stats like money, and exp n such
        std::cout << "Above are the available saves. Please enter the number of a save to load: ";
        std::cin >> input;
        //validate this input

        //run continueGame
    }else{
        //the name of the save will be whatever the player chooses to name themselves
        //if a save with that name already exists, add "(i)" to it where i is the number of files
        //with that same name
            
        //run new game start
        newGame();
    }    
}

/**
 * @brief check to see if the save file the player requested exists
 * 
 * return whether the  save exists
 */
bool Game::doSavesExist(){
    // LPCWSTR SAVESFOLDER = L"\\saves";
    // WIN32_FIND_DATA findData;
    // HANDLE handleFind = ::FindFirstFile(SAVESFOLDER, &findData);
    // if(handleFind == INVALID_HANDLE_VALUE){
    //     return false;
    // }else{
    //     return true;
    // }

    
    //fs::directory_iterator("\\saves");
    return true;
}

/**
 * @brief beginning of game setup and interface
 * 
 */
void Game::newGame(){
    std::string name;
    std::cout << "Welcome to RogueLike! Please enter your rogue's name:" << std::endl;
    std::cin >> name;
    //if(name already exists in the filesystem){add (i) to it to differentiate}
    outputFile.open("saves/" + name + ".log");

    //set up the money, xp, food, potions, and weapons of the player's permainventory
    outputFile << "M : 0" << std::endl
               << "XP: 0" << std::endl
               << "F : "  << std::endl
               << "P : "  << std::endl
               << "W : ";
    //cleanup
    outputFile.close();

    playGame();
}

/**
 * @brief main game loop
 * 
 */
void Game::playGame(){
    //game loop where the player is thrown into a dungeon

    //if the player dies at any point, return them to the hub w/ prizes

    //if the player gets through a dungeon, go to the next one.
    loadNextLevel();
    //playLevel();
}

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
    //character key: # = wall, X = player
    int xPos;
    int yPos;

    levelFile.open("levels/level" + std::to_string(currLevel) + ".txt");
    //make sure the level file was properly opened
    if(!levelFile){
        std::cout << "file not opened";
    }
    //go through the level and enter it into a 2d array to make operations easier
    for(int row = 0; row < 40; row++){
        for(int col = 0; col < 60; col++){
            levelFile >> std::noskipws >> this->levelArray[row][col];
        }
        //skip the newline characters
        levelFile.ignore();
    }

    //load up the level's start pos
    levelFile >> xPos >> std::skipws >> yPos;

    //set the player's x and y pos to the level's starting pos
    player.updateXPos(xPos);
    player.updateYPos(yPos);

    //cleanup
    levelFile.close();
}

void Game::playLevel(){
    //until ive got gui skills, ill use a 3x3 grid to display the surrounding area
    bool notDead = true;
    bool levelNotComplete = true;
    int xPos;
    int yPos;
    char input;
    bool invalidMove;
    while(notDead && levelNotComplete){
        //check to see if there's any restrictions on what the player can see
        //e.g. theres a wall on one side, we don't wanna go oob to try and access it
        //not a problem when theres just a 3x3 grid, but good to keep in mind for gui times?
        
        //reset invalidMove tracker
        invalidMove = false;

        //print out a 3x3 grid of the player's surroundings
        xPos = player.getXPos();
        yPos = player.getYPos();
        std::cout << levelArray[yPos-1][xPos-1] << levelArray[yPos-1][xPos] << levelArray[yPos-1][xPos+1] << std::endl
                  << levelArray[yPos][xPos-1] << levelArray[yPos][xPos] << levelArray[yPos][xPos+1] << std::endl
                  << levelArray[yPos+1][xPos-1] << levelArray[yPos+1][xPos] << levelArray[yPos+1][xPos+1] << std::endl << std::endl;
        //validate the input
        do{
            std::cout << "Please enter (u)p, (d)own, (l)eft, or (r)ight: ";
        std::cin >> input;
        }while(input != 'u' && input != 'd' && input != 'l' && input != 'r');
        //update the x or y pos of the player (validating if its a valid move that is)
        if((input == 'u' && levelArray[yPos-1][xPos] == '#') || (input == 'd' && levelArray[yPos+1][xPos] == '#')){
            invalidMove = true;
        }

    }
}

char Game::getElementAtPos(const int X_POS, const int Y_POS) const {
    return this->levelArray[Y_POS][X_POS];
}

#endif
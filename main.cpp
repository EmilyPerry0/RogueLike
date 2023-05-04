/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * sets up everything needed for the game and contains the main SFML draw loop so that a
 * nice lil gui can be used while playing the game. also has event handling so the player can
 * move n interact with the game n such
 */

#include "Game.h"

#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

using namespace sf;
using namespace std;

int main()
{
    Game rogueLike;
    //start and setup the game w/ command line stuff
    rogueLike.loadNextLevel();
    cout << "The game window is now open." << endl << 
            "Please Tap the WASD keys to move." << endl;

    //create a window
    RenderWindow window( VideoMode(1200, 800), "RogueLike" );

    //create an event object once to store future events
    Event event;
        
    //load in the character
    Texture characterTexture;
    if(!characterTexture.loadFromFile("data/characterSprite.png")){
        cerr << "Could not load character sprite" << endl;
        return -1;
    }

    //load in the enemy
    Texture enemyTexture;
    if(!enemyTexture.loadFromFile("data/mario.png")){
        cerr << "Could not load enemy sprite" << endl;
        return -2;
    }

    //load in the encounter screen
    Texture encounterScreen;
    if(!encounterScreen.loadFromFile("data/encounterScreen.jpg")){
        cerr << "Could not load encounter screen" << endl;
        return -3;
    }

    //load in the chest
    Texture chestTexture;
    if(!chestTexture.loadFromFile("data/chest.jpg")){
        cerr << "could not load chest sprite" << endl;
        return -4;
    }

    //load in the font
    Font font;
    if(!font.loadFromFile("data/arial.ttf")){
        cerr << "Could not load font" << endl;
        return -5;
    }
    
    //sprite setup
    Sprite characterSprite;
    characterSprite.setTexture(characterTexture);

    Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);

    Sprite encounterScreenSprite;
    encounterScreenSprite.setTexture(encounterScreen);

    Sprite chestSprite;
    chestSprite.setTexture(chestTexture);

    //while running
    while( window.isOpen() ) {
        //clear any existing contents
        window.clear();

        //are we in an enemy encounter?
        if(rogueLike.getInEnemyEncounter()){
            //draw the encounter screen so that it covers the whole screen
            encounterScreenSprite.setPosition(0,0);
            window.draw(encounterScreenSprite);

            //make the character sprite and the enemy sprite big
            characterSprite.setScale(Vector2f(5, 5));
            enemySprite.setScale(Vector2f(5,5));

            //draw the character in the nearby pad and the enemy on the opposite pad
            characterSprite.setPosition(300, 450);
            enemySprite.setPosition(850, 200);
            window.draw(characterSprite);
            window.draw(enemySprite);

            //draw the names of you and the enemy
            Text enemyName;
            Text playerName;

            enemyName.setFont(font);
            playerName.setFont(font);

            enemyName.setString("Enemy");
            playerName.setString("Player");

            enemyName.setPosition(100, 100);
            playerName.setPosition(710, 390);

            enemyName.setFillColor(Color::Black);
            playerName.setFillColor(Color::Black);

            window.draw(playerName);
            window.draw(enemyName);

            //draw the attack button
            RectangleShape attackButton;
            Text attackText;
            attackButton.setSize(Vector2f(1100, 150));
            attackButton.setFillColor(Color::Red);
            attackButton.setPosition(50, 600);
            window.draw(attackButton);
            attackText.setString("Attack (enter)");
            attackText.setFont(font);
            attackText.setPosition(500, 650);
            window.draw(attackText);
            
            //draw enemy and player hp bars
            RectangleShape playerHpBar;
            playerHpBar.setFillColor(Color::Green);
            playerHpBar.setSize(Vector2f(250/((double)rogueLike.getPlayerMaxHP()/rogueLike.getPlayerCurrHP()), 35));
            playerHpBar.setPosition(870, 440);
            window.draw(playerHpBar);

            RectangleShape enemyHpBar;
            enemyHpBar.setFillColor(Color::Green);
            enemyHpBar.setSize(Vector2f(250/((double)rogueLike.getEnemyMaxHP()/rogueLike.getEnemyCurrHP()), 35));
            enemyHpBar.setPosition(260, 150);
            window.draw(enemyHpBar);



        }else{
            //draw all things in the level
            for(int x = 0; x < 60; x++){
                for(int y = 0; y < 40; y++){
                    char element = rogueLike.getElementAtPos(x, y);
                    if(element == '#'){
                        //walls
                        RectangleShape newRect;
                        newRect.setSize(Vector2f(20, 20));
                        newRect.setFillColor(Color::Blue);
                        newRect.setPosition(x * 20, y * 20);
                        window.draw(newRect);
                    }else if(element == 'P'){
                        //character
                        characterSprite.setPosition(x * 20, y * 20);
                        characterSprite.setScale(1, 1);
                        window.draw(characterSprite);
                    }else if(element == 'E'){
                        //exit space
                        RectangleShape newRect;
                        newRect.setSize(Vector2f(20, 20));
                        newRect.setFillColor(Color::Green);
                        newRect.setPosition(x * 20, y * 20);
                        window.draw(newRect);
                    }else if(element == 'M'){
                        //enemy (marios)
                        enemySprite.setPosition(x* 20, y * 20);
                        enemySprite.setScale(1,1);
                        window.draw(enemySprite);
                    }else if (element >= 48 && element <= 57){
                        //chests (represented by 0-9 to indicate the contents of the chest)
                        chestSprite.setPosition(x * 20, y * 20);
                        window.draw(chestSprite);
                    }
                }
            }
            //do the chest overlay if we are in a chest encounter
            if(rogueLike.getInChestOpening()){
                //draw the text box background
                RectangleShape textBoxBackground;
                textBoxBackground.setSize(Vector2f(1100, 150));
                textBoxBackground.setFillColor(Color::White);
                textBoxBackground.setPosition(50, 600);
                window.draw(textBoxBackground);

                //draw the text about the chest contents
                Text chestContentsInfo;
                chestContentsInfo.setFont(font);
                chestContentsInfo.setFillColor(Color::Black);
                string chestInfo = "You found a new Weapon! Name: " + rogueLike.getCurrWeapon().getName() + 
                                   "  Damage: " + to_string(rogueLike.getCurrWeapon().getDamage()) + " (Enter)";
                chestContentsInfo.setString(chestInfo);
                chestContentsInfo.setPosition(100, 660);
                window.draw(chestContentsInfo);
            }
        }
        //display the stuff we just drew
        window.display();

        //run at 24 fps so we don't eat up the cpu and graphics processing like it's ice cream at mines market
        window.setFramerateLimit(24);
    
        //event handling
        while( window.pollEvent(event) ) {
            //if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                //tell the window to close
                window.close();
            }
            //if we are in the battle screen
            if(rogueLike.getInEnemyEncounter()){
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                    rogueLike.attack();
                }
            }
            //if we are in a chest opening screen
            else if(rogueLike.getInChestOpening()){
                if(Keyboard::isKeyPressed(Keyboard::Enter)){
                    //go out of the chest opening screen
                    rogueLike.leaveChestOpening();
                }
            //otherwise we are not in the battle screen or the chest opening screen
            }else{
                if(Keyboard::isKeyPressed(Keyboard::W)){
                    //move up
                    rogueLike.updatePlayerPos('w');
                }else if(Keyboard::isKeyPressed(Keyboard::A)){
                    //move left
                    rogueLike.updatePlayerPos('a');
                }else if(Keyboard::isKeyPressed(Keyboard::S)){
                    //move down
                    rogueLike.updatePlayerPos('s');
                }else if(Keyboard::isKeyPressed(Keyboard::D)){
                    //move right
                    rogueLike.updatePlayerPos('d');
                }
                //make movement a little bit more controllable
                if(event.type == Event::KeyPressed){
                    this_thread::sleep_for(chrono::milliseconds(30));
                }
            }
        }
    }
    return 0;
}
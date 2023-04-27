#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace sf;
using namespace std;

void deleteDisplayElements(Shape* elementArray[40][60]){
    for(int x = 0; x < 60; x++){
        for(int y = 0; y < 40; y++){
            delete elementArray[y][x];
        }
    }
}

int main()
{
    Game rogueLike;
    //start and setup the game w/ command line stuff
    rogueLike.playGame();
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

    //load in the enconuter screen
    Texture encounterScreen;
    if(!encounterScreen.loadFromFile("data/encounterScreen.jpg")){
        cerr << "Could not load encounter screen" << endl;
        return -3;
    }

    //load in the font
    Font font;
    if(!font.loadFromFile("data/arial.ttf")){
        cerr << "Could not load font" << endl;
        return -4;
    }

    Sprite characterSprite;
    characterSprite.setTexture(characterTexture);

    Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);

    Sprite encounterScreenSprite;
    encounterScreenSprite.setTexture(encounterScreen);
    

    //while running
    while( window.isOpen() ) {
        //clear any existing contents
        window.clear();

        //are we in an enemy encounter?
        if(rogueLike.getInEnemyEncounter()){
            //draw the encounter screen so that it covers the whole screen
            encounterScreenSprite.setPosition(0,0);
            window.draw(encounterScreenSprite);


            //make the character sprite and the enemy sprite beeg
            characterSprite.setScale(Vector2f(5, 5));
            enemySprite.setScale(Vector2f(5,5));

            //draw the character in the nearby thing and the enemy on the opposite pad
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
                        window.draw(enemySprite);
                    }
                }
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
            }else if(Keyboard::isKeyPressed(Keyboard::W)){
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
<<<<<<< HEAD
                this_thread::sleep_for(chrono::milliseconds(30));
=======
                sleep(milliseconds(25));
>>>>>>> e9deadeb96763a0ed86b2b9d7b818b187a896dbc
            }
        }
    }
    return 0;
}

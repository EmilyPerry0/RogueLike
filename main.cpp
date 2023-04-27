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

        int currButtonChoice = 0;
        bool itemScreen = false;

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

            //draw the attack and item buttons
            RectangleShape attackButton;
            RectangleShape itemsButton;
            Text attackText;
            Text itemsText;

            attackButton.setSize(Vector2f(550, 150));
            itemsButton.setSize(Vector2f(550, 150));

            attackButton.setFillColor(Color::Red);
            itemsButton.setFillColor(Color::Blue);

            attackButton.setPosition(50, 600);
            itemsButton.setPosition(600, 600);

            window.draw(attackButton);
            window.draw(itemsButton);

            attackText.setString("Attack");
            itemsText.setString("Items");

            attackText.setFont(font);
            itemsText.setFont(font);

            attackText.setPosition(250, 650);
            itemsText.setPosition(800, 650);

            window.draw(attackText);
            window.draw(itemsText);

            //display which button is being highlighted
            RectangleShape buttonHighlight;
            buttonHighlight.setFillColor(Color(255,255,255));
            buttonHighlight.setSize(Vector2f(100, 10));
            if(currButtonChoice == 0){
                //draw the highlight under the left button
                buttonHighlight.setPosition(250, 700);
            //otherwise draw it under the right button
            }else{
                buttonHighlight.setPosition(800, 700);
            }
            window.draw(buttonHighlight);
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
            //if we are in the battle screen
            if(rogueLike.getInEnemyEncounter()){
                if(Keyboard::isKeyPressed(Keyboard::A)){
                //move the cursor thing left
                currButtonChoice = 0;
                }else if(Keyboard::isKeyPressed(Keyboard::D)){
                //move the cursor thing left
                currButtonChoice = 1;
                }
            //otherwise we are not in the battle screen
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
    }
    return 0;
}
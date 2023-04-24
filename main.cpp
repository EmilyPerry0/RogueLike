#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include "time.h"

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

    Sprite characterSprite;
    characterSprite.setTexture(characterTexture);

    //while running
    while( window.isOpen() ) {
        //clear any existing contents
        window.clear();

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
                }
            }
        }


        //display the stuff we just drew
        window.display();

        //run at 24 fps so we don't eat up the cpu and graphics processing like it's ice cream at mines market
        sleep(milliseconds(41.66667));
    
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
                sleep(milliseconds(30));
            }
        }
    }
    return 0;
}

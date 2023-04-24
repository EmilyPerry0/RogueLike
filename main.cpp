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
    rogueLike.beginGame();
    
    //create a window
    RenderWindow window( VideoMode(1200, 800), "RogueLike" );

    //create an event object once to store future events
    Event event;
        
    //while running
    while( window.isOpen() ) {
        //clear any existing contents
        window.clear();

    //draw all things in the level
    for(int x = 0; x < 60; x++){
        for(int y = 0; y < 40; y++){
            char element = rogueLike.getElementAtPos(x, y);
            if(element == '#'){
                RectangleShape newRect;
                newRect.setSize(Vector2f(20, 20));
                newRect.setFillColor(Color::Blue);
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
                //delete all the display elements
                //deleteDisplayElements(displayElementArray);
            }
            //check addition event types to handle additional events (movement WASD, other stuff)
        }
    }
    return 0;
}

/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * adds things to a chest and has a getter for whats in the chest
 */

#include "Chest.h"

Chest::Chest(const Weapon CHEST_CONTENTS){
    this->chestContents = CHEST_CONTENTS;
}

Weapon Chest::getChestContents()const{
    return this->chestContents;
}
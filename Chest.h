/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * header file for the chest class
 */

#ifndef CHEST_H
#define CHEST_H

#include "Weapon.h"

class Chest {
public:
    /**
     * @brief Construct a new Chest object that has a Weapon in it
     */
    Chest(const Weapon CHEST_CONTENTS);

    /**
     * @brief getter function for whats in the chest
     */
    Weapon getChestContents()const;
private:
    Weapon chestContents;
};
#endif
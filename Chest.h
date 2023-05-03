#ifndef CHEST_H
#define CHEST_H

#include "Weapon.h"

#include <string>

class Chest {
public:
    /**
     * @brief Construct a new Chest object that has a Weapon in it
     */
    Chest(const Weapon CHEST_CONTENTS);

    /**
     * @brief getter function for whats in the chest
     */
    Weapon getChestContents();
private:
    Weapon chestContents;
};
#endif
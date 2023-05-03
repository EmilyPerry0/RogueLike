#include "Chest.h"

Chest::Chest(const Weapon CHEST_CONTENTS){
    this->chestContents = CHEST_CONTENTS;
}

Weapon Chest::getChestContents(){
    return this->chestContents;
}
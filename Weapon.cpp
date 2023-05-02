#include "Weapon.h"

Weapon::Weapon(){
    this->name = "swordy sword of swords";
    this->damage = 100000;
}

Weapon::Weapon(const std::string NAME, const int DAMAGE){
    this->name = NAME;
    this->damage = DAMAGE;
}

std::string Weapon::getName(){
    return this->name;
}

int Weapon::getDamage(){
    return this->damage;
}
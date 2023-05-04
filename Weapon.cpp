/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * implementation of the weapon class. each weapon has a unique name and damage output.
 */

#include "Weapon.h"

Weapon::Weapon(){
    this->name = "swordy sword of swords";
    this->damage = 100000;
}

Weapon::Weapon(const std::string NAME, const int DAMAGE){
    this->name = NAME;
    this->damage = DAMAGE;
}

std::string Weapon::getName()const{
    return this->name;
}

int Weapon::getDamage()const{
    return this->damage;
}
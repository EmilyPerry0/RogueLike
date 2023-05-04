/* CSCI 200: Final Project: RogueLike
 *
 * Author: Emily Perry
 * Resources used: Ed, private email communication with professors to help me figure out how to 
 * do file i/o for specific things. Other students helped me with small debugging problems. 
 * The SFML + cpp docs helped with syntax and how things worked so I could implement them.
 *
 * header file for the weapon class
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon{
public:
    /**
     * @brief default constructor
     */
    Weapon();

    /**
     * @brief parameterized constructor
     * 
     * @param NAME the name of the weapon
     * @param DAMAGE the damage the weapon does on each swing
     */
    Weapon(const std::string NAME, const int DAMAGE);

    /**
     * @brief Get the Name string
     */
    std::string getName()const;

    /**
     * @brief Get the Damage int
     */
    int getDamage()const;
private:
    std::string name;
    int damage;
};
#endif
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
    std::string getName();

    /**
     * @brief Get the Damage int
     */
    int getDamage();
private:
    std::string name;
    int damage;
};
#endif
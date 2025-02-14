/*
    Andy Wu
    cw4483
    hw03.cpp
    Spring 2025
 */

#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class Warrior{
public:

    Warrior (const string& warrior_name, const string& warrior_weapon
             ,int strength)
        : name(warrior_name), weapon(warrior_weapon, strength){}

private:

    class Weapon {
    public:

        Weapon(const string& warrior_weapon_name, int warrior_weapon_strength)
            : weapon_name(warrior_weapon_name), weapon_strength(warrior_weapon_strength){}

    private:
        string weapon_name;
        int weapon_strength;
    };

    string name;
    Weapon weapon;
};

int main(){

}
/*
    Andy Wu
    cw4483
    hw03.cpp
    Spring 2025
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
	public:

		Warrior(const string& the_warrior_name, const string& the_weapon_name, int the_weapon_strength)
		  	: warrior_name(the_warrior_name), weapon(the_weapon_name, the_weapon_strength) {}

        //methods
    	int get_strength() const {
        	return weapon.get_strength();
    	}

        string get_name() const {
          return warrior_name;
        }

        void set_strength(int strength) {
			weapon.set_strength(strength);
        }

	private:
		class Weapon {
        	public:

				Weapon(const string& the_weapon_name, int the_strength)
                    : weapon_name(the_weapon_name), strength(the_strength) {}

				//methods
				int get_strength() const {
					return strength;
				}

            	string get_name() const {
                	return weapon_name;
                }

				void set_strength(const int& new_strength) {
         			strength = new_strength;
				}

           	private:

				friend ostream& operator << (ostream& os, const Warrior::Weapon& weapon);
				string weapon_name;
	            int strength;

    	};

		friend ostream& operator << (ostream& os, const Warrior& warrior);
        friend ostream& operator << (ostream& os, const Warrior::Weapon& weapon);

        string warrior_name;
        Weapon weapon;
};

void open_file(const ifstream& file);
void battle(Warrior* warrior1, Warrior* warrior2);

ostream& operator << (ostream& os, const Warrior& warrior) {
	os << "Warrior: " << warrior.warrior_name << ", " << warrior.weapon;
	return os;
}

ostream& operator << (ostream& os, const Warrior::Weapon& weapon) {
	os << "weapon: " << weapon.weapon_name << ", " << weapon.strength << endl;
    return os;
}

void open_file(ifstream& file) {
 	file.clear();
	file.open("warriors.txt");
    if (!file){
    	cerr << "Error opening file" << endl;
        exit(1);
    }
}

void battle(Warrior* warrior1, Warrior* warrior2) {
	int warrior1_strength = warrior1->get_strength();
    int warrior2_strength = warrior2->get_strength();
    string warrior1_name = warrior1->get_name();
    string warrior2_name = warrior2->get_name();

	cout << warrior1_name << " battles " << warrior2_name << endl;

	if ((warrior1_strength == 0 && warrior2_strength != 0)
                || (warrior1_strength != 0 && warrior2_strength == 0)) {

		if (warrior1_strength == 0) {
			cout << "He's dead, " << warrior2_name << endl;
		}

		if (warrior2_strength == 0) {
			cout << "He's dead, " << warrior1_name << endl;
		}

		return; //prevents further checks
	}

	if (warrior1_strength == 0 && warrior2_strength == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;

		return; //prevents further checks
	}

	if (warrior1_strength == warrior2_strength){
		cout << "Mutual Annihilation: " << warrior1_name << " and "
			 << warrior2_name << " die at each other's hands" << endl;
		warrior1->set_strength(0);
		warrior2->set_strength(0);

		return; //prevents further checks
	}

	if (warrior1_strength > warrior2_strength) {
		cout << warrior1_name << " defeats " << warrior2_name << endl;
		warrior1->set_strength(warrior1_strength - warrior2_strength);
		warrior2->set_strength(0);

		return; //prevents further checks
	}

	if (warrior2_strength > warrior1_strength) {
		cout << warrior2_name << " defeats " << warrior1_name << endl;
		warrior2->set_strength(warrior2_strength - warrior1_strength);
		warrior1->set_strength(0);
	}
}

int main() {
  	vector<Warrior> warriors;
	ifstream warrior_file;
    open_file(warrior_file);
    string token;

    while (warrior_file >> token){

		if (token == "Warrior") {

			string warrior_name, weapon_name;
			int strength;

			warrior_file >> warrior_name >> weapon_name >> strength;
            Warrior new_warrior = Warrior(warrior_name, weapon_name, strength);
            warriors.emplace_back(new_warrior);
		}

		if (token == "Status"){
			cout << "There are: " << warriors.size() << " warriors." << endl;

			for (const Warrior& warrior : warriors) {
			  cout << warrior << endl;
			}
		}

        if (token == "Battle"){
          	Warrior* warrior1ptr = nullptr;
            Warrior* warrior2ptr = nullptr;
        	string warrior1_name, warrior2_name;
            warrior_file >> warrior1_name >> warrior2_name;

            for (Warrior& warrior : warriors) {
              if (warrior.get_name() == warrior1_name) {
                warrior1ptr = &warrior;
              }

              if (warrior.get_name() == warrior2_name) {
                warrior2ptr = &warrior;
              }
        	}

            battle(warrior1ptr, warrior2ptr);
        }
    }
}
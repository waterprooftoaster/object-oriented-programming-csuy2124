#include "Noble.h"
#include "Warrior.h"
#include <iostream>

namespace WarriorCraft {
	//output operator overloader
	std::ostream& operator <<(std::ostream& os, const Noble& noble) {
		os << noble . name << "  has an army of " << noble . warriors . size() <<
				std::endl;
		for (const Warrior* curr_warrior : noble . warriors) {
			os << *curr_warrior << std::endl;
		}
		return os;
	}

	//Noble Methods
        
	void Noble::kill() { dead = true; }

	std::string Noble::get_name() const { return name; }

    //remove_without_iterators
    bool Noble::remove_without_iterators(Warrior* warrior) {
    	for (size_t i = 0; i < warriors . size(); i++) {
        	if (warriors[i] == warrior){
        		 for (size_t j = i + 1; j < warriors . size(); j++) {
                    warriors[j - 1] = warriors [j];
        		}
                warriors.pop_back();
                return true;
            }
    	}
		std::cout << "warrior not found" << std::endl;
        return false;
	}//remove_without_iterators

	//hire
	bool Noble::hire(Warrior& warrior) {
		// do not hire if warrior is already hired or noble is dead
		if (warrior . get_employment_status() == true || dead == true) {
			std::cout << name << " failed to hire " << warrior . get_name()
                      << std::endl;
			return false;
		}

		Warrior* warriorptr = &warrior;
		//first, allow warrior to know their boss is
		if (!warriorptr -> set_employer(this)) { return false; }
		warrior . set_employment_status(true);
		//now add warrior to army
		warriors . emplace_back(warriorptr);
		return true;
	}//hire
        
	//fire
	bool Noble::fire(Warrior& warrior) {
		if (dead == true) {
			std::cout << name << " is dead when trying to fire warrior"
                      << std::endl;
			return false;
		}

		std::cout << warrior . get_name()
                  << ", you don't work for me anymore! -- " << name << std::endl;

		for (size_t i = 0 ; i < warriors . size() ; ++i) {
			if (warriors[i] -> get_name() == warrior . get_name()) {
				warriors[i] = nullptr;
				remove_without_iterators(&warrior);
			}
		}
		warrior . set_employment_status(false);
		warrior . set_employer(nullptr);
		return true;
	}//fire
        
	//remove_warrior
	bool Noble::remove_warrior(Warrior* warrior) {
		if (dead == true) {
			std::cout << name << " is dead when trying to remove warrior"
                      << std::endl;
			return false;
		} 

		for (size_t i = 0 ; i < warriors . size() ; ++i) {
			if (warriors[i] == warrior) {
				warriors[i] = nullptr;
				remove_without_iterators(warrior);
			}
		}
		warrior -> set_employment_status(false);
        warrior -> set_employer(nullptr);
		return true;
	}//remove_warrior

	//get_army_strength
	double Noble::get_army_strength() const {
		double army_strength = 0;
		for (const Warrior* curr_warrior : warriors) {
			army_strength += curr_warrior -> get_strength();
		}
		return army_strength;
	}//get_army_strength

	
    //set_strength 
	void Noble::set_strength(double reduction_ratio) {
		for (Warrior* curr_warrior : warriors) {
			curr_warrior -> set_strength(reduction_ratio);
		}
	}//set_strength 

        
	//battle
	void Noble::battle(Noble& opponent) {
		double opponent_army = opponent . get_army_strength();
		double self_army = get_army_strength();
		std::string opponent_name = opponent . get_name();

		std::cout << name << " battles " << opponent_name << std::endl;

		if ((self_army == 0 && opponent_army != 0) || (
			    self_army != 0 && opponent_army == 0)) {
			if (self_army == 0) {
                std::cout << "He's dead, " << opponent_name << std::endl;
            }

			if (opponent_army == 0) {
                std::cout << "He's dead, " << name << std::endl;
            }
			return; 
		}

		if (self_army == 0 && opponent_army == 0) {
			std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
			return;
		}

		if (self_army == opponent_army) {
			std::cout << "Mutual Annihilation: " << name << " and "
                      << opponent_name << " die at each other's hands"
                      << std::endl;
			kill();
			opponent . kill();
			set_strength(0);
			opponent . set_strength(0);
			return; 
		}

		if (self_army > opponent_army) {
			std::cout << name << " defeats " << opponent_name << std::endl;
			double reduction_ratio = 1 - (opponent_army / self_army);
			set_strength(reduction_ratio);
			opponent . set_strength(0);
			opponent . kill();
			return; 
		}

		if (opponent_army > self_army) {
			std::cout << opponent_name << " defeats " << name << std::endl;
			double reduction_ratio = 1 - (self_army / opponent_army);
			set_strength(0);
			opponent . set_strength(reduction_ratio);;
			kill();
		}
	}
}// battle
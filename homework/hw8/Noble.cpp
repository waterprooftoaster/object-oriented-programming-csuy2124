#include "Noble.h"
#include "Protector.h"

namespace WarriorCraft {

//output operator overloader
std::ostream& operator <<(std::ostream& os, const Noble& noble) {
	os << noble . name << "  has an army of " << noble . protectors . size() <<
			std::endl;
	for (const Protector* curr_protector : noble . protectors) {
		os << *curr_protector << std::endl;
	}
	return os;
}

//Noble Methods
bool Noble::is_dead() const { return dead; }

void Noble::kill() { dead = true; }

std::string Noble::get_name() const { return name; }

//speak
void Noble::speak() const {
	for (Protector* curr_protector : protectors) {
          curr_protector -> speak();
	}
}//speak

//hire
bool Noble::hires(Protector& protector) {
	// do not hire if Protector is already hired or noble is dead
	if (protector . get_employer() != nullptr || dead == true) {
		std::cout << name << " failed to hire " << protector . get_name()
                  << std::endl;
		return false;
	}

	Protector* protectorptr = &protector;
	//first, allow Protector to know their boss is
	if (!protectorptr -> set_employer(this)) { return false; }
	protector . set_employment_status(true);
	//now add Protector to army
	protectors . emplace_back(protectorptr);
	return true;
}//hire

//fire
bool Noble::fires(Protector& protector) {
	if (!remove_protector(&protector)) {
		std::cout << name << " failed to fire " << protector . get_name()
                  << std::endl;
		return false;
	}

	std::cout << protector . get_name()
              << ", you don't work for me anymore! -- " << name << std::endl;
	return true;
}//fire

//remove_protector
bool Noble::remove_protector(Protector* protector) {
	if (dead == true || protectors.empty()) {
		std::cout << name << "failed to remove" << protector -> get_name()
				  << std::endl;
		return false;
	}
	for (size_t i = 0; i < protectors . size(); i++) {
        size_t last_index = protectors . size() - 1;
		if (protectors[i] == protector){
            protectors[i] -> set_employer(nullptr);
			for (size_t j = i + 1; j < protectors . size(); j++) {
				protectors[j - 1] = protectors [j];
			}
			protectors.pop_back();
			return true;
		}
	}
	std::cout << "Protector not found" << std::endl;
	return false;
}//remove_Protector

//get_army_strength
double Noble::get_army_strength() const {
	double army_strength = 0;
	for (const Protector* curr_protector : protectors) {
		army_strength += curr_protector -> get_strength();
	}
	return army_strength;
}//get_army_strength


//set_strength
void Noble::set_strength(double reduction_ratio) {
	for (Protector* curr_rotector : protectors) {
		curr_rotector -> set_strength(reduction_ratio);
	}
}//set_strength


//battle
void Noble::battle(Noble& opponent) {
	double opponent_army = opponent . get_army_strength();
	double self_army = get_army_strength();
	std::string opponent_name = opponent . get_name();

	std::cout << name << " battles " << opponent_name << std::endl;
	speak();
    opponent.speak();

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
}// battle

}
#include "Warrior.h"
#include "Noble.h"
#include <iostream>

namespace WarriorCraft {
	//ouput overloader
	std::ostream& operator <<(std::ostream& os, const Warrior& warrior) {
		os << warrior . name << ": " << warrior . strength << std::endl;
		return os;
	}

	//methods
	bool Warrior::isHired() const { return hired; }

	bool Warrior::get_employment_status() const { return hired; }

	double Warrior::get_strength() const { return strength; }

	std::string Warrior::get_name() const { return name; }

	bool Warrior::set_employer(Noble* new_employer) {
		employer = new_employer;
		if (employer == nullptr) {
			std::cout << "somehow failed to set " << this -> name
					  << "to be employed by"<< new_employer -> get_name()
                      << std::endl;
			return false;
		}
		return true;
	}

	bool Warrior::runaway() {
		if (!employer -> remove_warrior(this)) { return false; }
		std::cout << name << " flees in terror, abandoning his lord, "
                  << employer -> get_name() << std::endl;

		return true;
	}

	bool Warrior::set_employment_status(bool status) {
		bool old_status = hired;
		hired = status;
		if (hired == old_status) { return false; }
		return true;
	}

	bool Warrior::set_strength(double reduction_ratio) {
		int old_strength = strength;
		strength = strength * reduction_ratio;
		if (strength == old_strength) { return false; }
		return true;
	}
}

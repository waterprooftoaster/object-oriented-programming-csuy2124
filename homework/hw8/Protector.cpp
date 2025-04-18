#include "Protector.h"
#include "Noble.h"
#include <iostream>

namespace WarriorCraft {
//output overloader
std::ostream& operator <<(std::ostream& os, const Protector& protector) {
	os << protector.name << " has strength " << protector.strength << std::endl;
	return os;
}

//methods
Noble* Protector::get_employer() const { return employer; }

std::string Protector::get_sound() const { return ""; }

void Protector::speak() const { std::cout << get_sound() << std::endl; }

double Protector::get_strength() const { return strength; }

std::string Protector::get_name() const { return name; }

//set_employer
bool Protector::set_employer(Noble* new_employer) {
	if (new_employer == nullptr || new_employer->is_dead() == true) {
		return false;
	}
	employer = new_employer;
	return true;
} //set_employer

//runaway
bool Protector::runaway() {
	if (!employer->remove_protector(this)) { return false; }
	std::cout << name << " flees in terror, abandoning his lord, " << employer->
			get_name() << std::endl;
	employer = nullptr;
	return true;
} //runaway

//set_strength
bool Protector::set_strength(const double reduction_ratio) {
	if (reduction_ratio < 0 || reduction_ratio > 1) {
		std::cout << "invalid reductin ratio" << std::endl;
		return false;
	}
	strength = strength * reduction_ratio;
	return true;
} //set_strength
}

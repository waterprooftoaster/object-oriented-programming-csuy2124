#ifndef WARRIOR_H
#define WARRIOR_H

#include <string>
#include <iostream>

namespace WarriorCraft {
class Noble;

class Warrior {
	std::string name;
	int strength;
	bool hired = false;
	Noble* employer = nullptr;

	// friend
	friend std::ostream& operator <<(std::ostream& os, const Warrior& warrior);

public:
	//constructor
	Warrior(const std::string& warrior_name, const double& warrior_strength)
	: name(warrior_name), strength(warrior_strength) {}

	//method prototypes
	bool isHired() const;

	bool get_employment_status() const;

	double get_strength() const;

	std::string get_name() const;

	bool set_employment_status(bool status);

	bool set_strength(double reduction_ratio);

	bool set_employer(Noble* employer);

	bool runaway();
}; //class Warrior
}

#endif

#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include "Warrior.h"

namespace WarriorCraft {
class Noble {
	std::vector <Warrior*> warriors;
	bool dead = false;
	std::string name;

	//friends
	friend std::ostream& operator <<(std::ostream& os, const Noble& noble);

public:
	//constructor
	explicit Noble(const std::string& noble_name) : name(noble_name) {}

	//method prototypes
	std::string get_name() const;

	double get_army_strength() const;

	bool hire(Warrior& warrior);

	bool fire(Warrior& warrior);

	void set_strength(double reduction_ratio);

	void battle(Noble& opponent);

	bool remove_warrior(Warrior* warrior);

	void kill();
}; //class Noble
}

#endif

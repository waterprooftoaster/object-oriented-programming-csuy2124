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

	virtual bool remove_without_iterators(Warrior* warrior);

	virtual std::string get_name() const;

	virtual double get_army_strength() const;

	virtual bool hire(Warrior& warrior);

	virtual bool fire(Warrior& warrior);

	virtual void set_strength(double reduction_ratio);

	virtual void battle(Noble& opponent);

	virtual bool remove_warrior(Warrior* warrior);

	virtual void kill();
}; //class Noble
}

#endif
#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include <iostream>
#include "Protector.h"

namespace WarriorCraft {
class Noble {
	std::vector<Protector*> protectors;
	bool dead = false;
	std::string name;

	//friends
	friend std::ostream& operator <<(std::ostream& os, const Noble& noble);

public:
	virtual ~Noble() = default;

	//constructor
	explicit Noble(const std::string& noble_name) : name(noble_name) {}

	//method prototype
	virtual std::string get_name() const;

	virtual double get_strength() const;

	virtual bool hires(Protector& protector);

	virtual bool fires(Protector& protector);

	virtual bool set_strength(double reduction_ratio);

	virtual void battle(Noble& opponent);

	virtual bool remove_protector(Protector* protector);

	virtual void kill();

	virtual bool is_dead() const;

	virtual void speak() const;
}; //class Noble
}

#endif

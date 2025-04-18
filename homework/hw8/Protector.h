#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <string>
#include <iostream>

namespace WarriorCraft {
class Noble;

class Protector {
	std::string name;
	int strength;
	Noble* employer = nullptr;

	// friend
	friend std::ostream& operator <<(std::ostream& os, const Protector& protector);

public:
	//constructor
	Protector(const std::string& protector_name, const double& protector_strength)
	: name(protector_name), strength(protector_strength) {}

	//method prototypes


	virtual bool isHired() const;

	virtual Noble* get_employer() const;

	virtual double get_strength() const;

	virtual std::string get_name() const;

	virtual bool set_employment_status(bool status);

	virtual bool set_strength(double reduction_ratio);

	virtual bool set_employer(Noble* employer);

	virtual bool runaway();

	virtual void speak() const;

	virtual std::string get_sound() const = 0;
}; //class Warrior
}

#endif

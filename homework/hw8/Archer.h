#ifndef ARCHER_H
#define ARCHER_H

#include "Warrior.h"

namespace WarriorCraft {

class Archer : public Warrior {
	std::string sound = "TWANG!";

public:
	Archer(const std::string& protector_name, const double& protector_strength)
	: Warrior(protector_name, protector_strength) {}

	std::string get_sound() const override;
};

}
#endif
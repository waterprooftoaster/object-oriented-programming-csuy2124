#ifndef ARCHER_H
#define ARCHER_H

#include "Warrior.h"

namespace WarriorCraft {
class Archer : public Warrior {
public:
	Archer(const std::string& warrior_name, const double& warrior_strength)
	: Warrior(warrior_name), Warrior(warrior_strength) {}
};
}
#endif
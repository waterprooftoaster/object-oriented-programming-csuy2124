#ifndef WARRIOR_H
#define WARRIOR_H

#include "Protector.h"
#include "Noble.h"

namespace WarriorCraft {
class Warrior : public Protector {
public:
	Warrior(const std::string& protector_name, const double& protector_strength)
	: Protector(protector_name, protector_strength) {}

	void speak() const override;

};
}
#endif
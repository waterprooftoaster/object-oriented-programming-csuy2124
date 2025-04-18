#include "PersonWithStrengthToFight.h"

namespace WarriorCraft {
void PersonWithStrengthToFight::speak() const {
	std::cout << "Ugh!" << std::endl;
}

std::ostream& operator<<(
std::ostream& os,
const PersonWithStrengthToFight& person) {
	os << person.get_name() << " has strength: " << person.strength <<
			std::endl;
	return os;
}

double PersonWithStrengthToFight::get_strength() const { return strength; }

bool PersonWithStrengthToFight::set_strength(double reduction_ratio) {
	if (reduction_ratio < 0 || reduction_ratio > 1) {
		std::cout << "invalid reduction ratio" << std::endl;
		return false;
	}
	strength = strength * reduction_ratio;
	return true;
}
}

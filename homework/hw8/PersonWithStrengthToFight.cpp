#include "PersonWithStrengthToFight.h"

namespace WarriorCraft{

void PersonWithStrengthToFight::speak() const {
	std::cout << "Ugh!" << std::endl;
}

std::ostream &operator<<(std::ostream &os,
                         const PersonWithStrengthToFight& person) {
	os << person.get_name() << "has strength: " << person.strength << std::endl;
    return os;
}

}
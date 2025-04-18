#include "Warrior.h"

namespace WarriorCraft{

void Warrior::speak() const {
	Protector::speak();
	std::cout << " Take that in the name of my lord, "
			  << get_employer() -> get_name() << std:: endl;
}

}
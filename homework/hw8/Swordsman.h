// Swordsman.h
// A type of Warrior that uses swords and makes a CLANG! sound

#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "Warrior.h"

namespace WarriorCraft
{
	class Swordsman : public Warrior
	{
		std::string sound = "CLANG!";

	public:
		Swordsman(
				const std::string &protector_name,
				const double &protector_strength)
				: Warrior(protector_name, protector_strength) {}

		void speak() const override;
	};
}
#endif

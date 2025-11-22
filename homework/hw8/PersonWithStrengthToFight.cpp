// PersonWithStrengthToFight.cpp
// Implementation of PersonWithStrengthToFight class
// Andy Wu
// cw4483

#include "PersonWithStrengthToFight.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{
	void PersonWithStrengthToFight::speak() const
	{
		cout << "Ugh!" << endl;
	}

	ostream &operator<<(
			ostream &os,
			const PersonWithStrengthToFight &person)
	{
		os << person.get_name() << " has strength: " << person.strength << endl;
		return os;
	}

	double PersonWithStrengthToFight::get_strength() const { return strength; }

	bool PersonWithStrengthToFight::set_strength(double reduction_ratio)
	{
		if (reduction_ratio < 0 || reduction_ratio > 1)
		{
			cout << "invalid reduction ratio" << endl;
			return false;
		}
		strength = strength * reduction_ratio;
		return true;
	}
}

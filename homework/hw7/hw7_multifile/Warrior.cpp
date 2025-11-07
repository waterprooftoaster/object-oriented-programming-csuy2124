#include "Warrior.h"
#include "Noble.h"
#include <iostream>

namespace WarriorCraft
{
	// ouput overloader
	std::ostream &operator<<(std::ostream &os, const Warrior &warrior)
	{
		os << warrior.name << ": " << warrior.strength << '\n';
		return os;
	}

	// methods
	bool Warrior::isHired() const { return hired; }

	double Warrior::get_strength() const { return strength; }

	std::string Warrior::get_name() const { return name; }

	void Warrior::set_employer(Noble *new_employer) { employer = new_employer; }

	void Warrior::remove_employer() { employer = nullptr; }

	bool Warrior::runaway()
	{
		std::cout << name << " flees in terror, abandoning his lord, "
							<< employer->get_name() << '\n';
		if (!employer->remove_warrior(this))
		{
			return false;
		}
		this->set_employment_status(false);
		this->remove_employer();
		return true;
	}

	bool Warrior::set_employment_status(bool status)
	{
		bool old_status = hired;
		hired = status;
		if (hired == old_status)
		{
			return false;
		}
		return true;
	}

	bool Warrior::set_strength(double reduction_ratio)
	{
		int old_strength = strength;
		strength = strength * reduction_ratio;
		if (strength == old_strength)
		{
			return false;
		}
		return true;
	}
}

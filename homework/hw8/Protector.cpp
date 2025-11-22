// Protector.cpp
// Implementation of the Protector abstract base class
// Andy Wu
// cw4483

#include "Protector.h"
#include "Noble.h"
#include "Lord.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{
	// output overloader
	ostream &operator<<(ostream &os, const Protector &protector)
	{
		os << "\t" << protector.name << " has strength " << protector.strength;
		return os;
	}

	// methods
	Noble *Protector::get_employer() const { return employer; }

	double Protector::get_strength() const { return strength; }

	string Protector::get_name() const { return name; }

	// set_employer
	bool Protector::set_employer(Noble *new_employer)
	{
		if (new_employer == nullptr || new_employer->is_dead() == true)
		{
			return false;
		}
		employer = new_employer;
		return true;
	} // set_employer

	// runaway
	bool Protector::runaway()
	{
		Lord *lord_employer = static_cast<Lord *>(employer);
		if (!lord_employer->remove_protector(this))
		{
			return false;
		}
		cout << name << " flees in terror, abandoning his lord, " << employer->get_name() << endl;
		employer = nullptr;
		return true;
	} // runaway

	// set_strength
	bool Protector::set_strength(const double reduction_ratio)
	{
		if (reduction_ratio < 0 || reduction_ratio > 1)
		{
			cout << "invalid reductin ratio" << endl;
			return false;
		}
		strength = strength * reduction_ratio;
		return true;
	} // set_strength
}

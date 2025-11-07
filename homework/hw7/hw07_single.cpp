/*
Andy Wu
cw4483
hw07-start.cpp
 */

// Comment out these two includes for the single file solution
// #include "Noble.h"
// #include "Warrior.h"

// Comment out this "using namespace" for the single file solution
// using namespace WarriorCraft;

#include <iostream>
#include <utility>
#include <vector>
#include <string>
using namespace std;

class Noble;
class Warrior;

class Noble
{
	vector<Warrior *> warriors;
	bool dead = false;
	string name;

	// friends
	friend ostream &operator<<(ostream &os, const Noble &noble);

public:
	// constructor
	explicit Noble(const string &noble_name) : name(noble_name) {}

	// method prototypes
	string get_name() const;

	double get_army_strength() const;

	bool hire(Warrior &warrior);

	bool fire(Warrior &warrior);

	void set_strength(double reduction_ratio);

	void battle(Noble &opponent);

	bool remove_warrior(Warrior *warrior);

	void kill();
}; // class Noble

class Warrior
{
	string name;
	int strength;
	bool hired = false;
	Noble *employer = nullptr;

	// friend
	friend ostream &operator<<(ostream &os, const Warrior &warrior);

public:
	// constructor
	Warrior(const string &warrior_name, const double &warrior_strength)
			: name(warrior_name), strength(warrior_strength) {}

	// method prototypes
	bool isHired() const;

	bool get_employment_status() const;

	double get_strength() const;

	string get_name() const;

	bool set_employment_status(bool status);

	bool set_strength(double reduction_ratio);

	bool set_employer(Noble *employer);

	bool runaway();
	void remove_employer() { employer = nullptr; }
}; // class Warrior

int main()
{
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
			 << lance << endl
			 << jim << endl
			 << linus << endl
			 << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl
			 << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
			 << lance << endl
			 << jim << endl
			 << linus << endl
			 << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}

/*
output overloaders
 */
ostream &operator<<(ostream &os, const Noble &noble)
{
	os << noble.name << "  has an army of " << noble.warriors.size() << endl;
	for (Warrior *curr_warrior : noble.warriors)
	{
		os << *curr_warrior << endl;
	}
	return os;
}

ostream &operator<<(ostream &os, const Warrior &warrior)
{
	os << warrior.name << ": " << warrior.strength << endl;
	return os;
}

// Warrior Methods
bool Warrior::isHired() const { return hired; }

bool Warrior::get_employment_status() const { return hired; }

double Warrior::get_strength() const { return strength; }

string Warrior::get_name() const { return name; }

bool Warrior::set_employer(Noble *new_employer)
{
	employer = new_employer;
	if (employer == nullptr)
	{
		cout << "somehow failed to set " << this->name << "to be employed by"
				 << new_employer->get_name() << endl;
		return false;
	}
	return true;
}

bool Warrior::runaway()
{
	cout << name << " flees in terror, abandoning his lord, " << employer->get_name() << endl;
	if (!employer->remove_warrior(this))
	{
		return false;
	}
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

// Noble Methods
void Noble::kill() { dead = true; }

string Noble::get_name() const { return name; }

bool Noble::hire(Warrior &warrior)
{
	// do not hire if warrior is already hired or noble is dead
	if (warrior.get_employment_status() == true || dead == true)
	{
		cout << name << " failed to hire " << warrior.get_name() << endl;
		return false;
	}

	Warrior *warriorptr = &warrior;
	// first, allow warrior to know their boss is
	if (!warriorptr->set_employer(this))
	{
		return false;
	}
	warrior.set_employment_status(true);
	// now add warrior to army
	warriors.emplace_back(warriorptr);
	return true;
}

bool Noble::fire(Warrior &warrior)
{
	if (dead == true)
	{
		cout << name << " is dead" << endl;
		return false;
	}

	cout << warrior.get_name() << ", you don't work for me anymore! -- " << name << endl;

	for (size_t i = 0; i < warriors.size(); ++i)
	{
		if (warriors[i]->get_name() == warrior.get_name())
		{
			warriors[i] = nullptr;
			// remove without iterators
			for (size_t j = i; j < warriors.size() - 1; ++j)
			{
				warriors[j] = warriors[j + 1];
			}
			warriors.pop_back();
			warrior.set_employment_status(false);
			warrior.remove_employer();
			return true;
		}
	}
	warrior.set_employment_status(false);
	return true;
}

bool Noble::remove_warrior(Warrior *warrior)
{
	if (dead == true)
	{
		cout << name << " is dead" << endl;
		return false;
	}

	for (size_t i = 0; i < warriors.size(); ++i)
	{
		if (warriors[i] == warrior)
		{
			// remove without iterators
			for (size_t j = i; j < warriors.size() - 1; ++j)
			{
				warriors[j] = warriors[j + 1];
			}
			warriors.pop_back();
			warrior->set_employment_status(false);
			warrior->remove_employer();
			return true;
		}
	}
	return false;
}

double Noble::get_army_strength() const
{
	double army_strength = 0;
	for (Warrior *curr_warrior : warriors)
	{
		army_strength += curr_warrior->get_strength();
	}
	return army_strength;
}

void Noble::set_strength(double reduction_ratio)
{
	for (Warrior *curr_warrior : warriors)
	{
		curr_warrior->set_strength(reduction_ratio);
	}
}

void Noble::battle(Noble &opponent)
{
	double opponent_army = opponent.get_army_strength();
	double self_army = get_army_strength();
	string opponent_name = opponent.get_name();

	cout << name << " battles " << opponent_name << endl;

	if ((self_army == 0 && opponent_army != 0) || (self_army != 0 && opponent_army == 0))
	{
		if (self_army == 0)
		{
			cout << "He's dead, " << opponent_name << endl;
		}

		if (opponent_army == 0)
		{
			cout << "He's dead, " << name << endl;
		}

		return; // prevents further checks
	}

	if (self_army == 0 && opponent_army == 0)
	{
		cout << "Oh, NO! They're both dead! Yuck!" << endl;

		return; // prevents further checks
	}

	if (self_army == opponent_army)
	{
		cout << "Mutual Annihilation: " << name << " and " << opponent_name << " die at each other's hands" << endl;
		kill();
		opponent.kill();
		set_strength(0);
		opponent.set_strength(0);

		return; // prevents further checks
	}

	if (self_army > opponent_army)
	{
		cout << name << " defeats " << opponent_name << endl;
		double reduction_ratio = 1 - (opponent_army / self_army);
		set_strength(reduction_ratio);
		opponent.set_strength(0);
		opponent.kill();

		return; // prevents further checks
	}

	if (opponent_army > self_army)
	{
		cout << opponent_name << " defeats " << name << endl;
		double reduction_ratio = 1 - (self_army / opponent_army);
		set_strength(0);
		opponent.set_strength(reduction_ratio);
		;
		kill();
	}
}

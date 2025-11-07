#include "Noble.h"
#include "Warrior.h"
#include <iostream>

namespace WarriorCraft
{
	// output operator overloader
	std::ostream &operator<<(std::ostream &os, const Noble &noble)
	{
		os << noble.name << " has an army of " << noble.warriors.size() << '\n';
		for (const Warrior *curr_warrior : noble.warriors)
		{
			os << '\t' << *curr_warrior;
		}
		return os;
	}

	// Noble Methods
	void Noble::kill() { dead = true; }

	std::string Noble::get_name() const { return name; }

	bool Noble::hire(Warrior &warrior)
	{
		// do not hire if warrior is already hired or noble is dead
		if (warrior.isHired() == true || dead == true)
		{
			std::cout << name << " failed to hire " << warrior.get_name() << std::endl;
			return false;
		}
		Warrior *warriorptr = &warrior;
		// first, allow warrior to know their boss is
		warriorptr->set_employer(this);
		warrior.set_employment_status(true);
		// now add warrior to army
		warriors.emplace_back(warriorptr);
		return true;
	}

	bool Noble::fire(Warrior &warrior)
	{
		if (dead == true)
		{
			std::cout << name << " is dead";
			return false;
		}
		std::cout << warrior.get_name()
							<< ", you don't work for me anymore! -- " << name << '\n';
		for (size_t i = 0; i < warriors.size(); ++i)
		{
			if (warriors[i]->get_name() == warrior.get_name())
			{
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
		return false;
	}

	bool Noble::remove_warrior(Warrior *warrior)
	{
		if (dead == true)
		{
			std::cout << name << " is dead";
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
		std::string opponent_name = opponent.get_name();
		std::cout << name << " battles " << opponent_name << '\n';

		if ((self_army == 0 && opponent_army != 0) || (self_army != 0 && opponent_army == 0))
		{
			if (self_army == 0)
			{
				std::cout << "He's dead, " << opponent_name;
			}

			if (opponent_army == 0)
			{
				std::cout << "He's dead, " << name;
			}
			return;
		}

		if (self_army == 0 && opponent_army == 0)
		{
			std::cout << "Oh, NO! They're both dead! Yuck!" << '\n';
			return;
		}

		if (self_army == opponent_army)
		{
			std::cout << "Mutual Annihilation: " << name << " and "
								<< opponent_name << " die at each other's hands" << '\n';
			kill();
			opponent.kill();
			set_strength(0);
			opponent.set_strength(0);
			return;
		}

		if (self_army > opponent_army)
		{
			std::cout << name << " defeats " << opponent_name << '\n';
			double reduction_ratio = 1 - (opponent_army / self_army);
			set_strength(reduction_ratio);
			opponent.set_strength(0);
			opponent.kill();
			return;
		}

		if (opponent_army > self_army)
		{
			std::cout << opponent_name << " defeats " << name << '\n';
			double reduction_ratio = 1 - (self_army / opponent_army);
			set_strength(0);
			opponent.set_strength(reduction_ratio);
			kill();
		}
	}
}
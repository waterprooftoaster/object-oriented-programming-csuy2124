// Noble.cpp
// Implementation of the abstract Noble class
// Andy Wu
// cw4483

#include "Noble.h"

namespace WarriorCraft
{

	std::string Noble::get_name() const { return name; }

	bool Noble::is_dead() const { return dead; }

	void Noble::kill() { dead = true; }

	double Noble::get_strength() const { return 0; }

	// battle
	void Noble::battle(Noble &opponent)
	{
		const double opponent_strength = opponent.get_strength();
		const double self_strength = get_strength();

		std::cout << name << " battles " << opponent.name << std::endl;

		if (dead && opponent.dead)
		{
			std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
			return;
		}
		if (dead)
		{
			opponent.speak();
			std::cout << "He's dead " << opponent.name << std::endl;
			return;
		}
		if (opponent.dead)
		{
			speak();
			std::cout << "He's dead " << name << std::endl;
			return;
		}

		speak();
		opponent.speak();

		if (self_strength == opponent_strength)
		{
			std::cout << "Mutual Annihilation: " << name << " and " << opponent.name
								<< " die at each other's hands" << std::endl;
			kill();
			opponent.kill();
			set_strength(0);
			opponent.set_strength(0);
			return;
		}

		if (self_strength > opponent_strength)
		{
			std::cout << name << " defeats " << opponent.name << std::endl;
			const double reduction_ratio = 1 - (opponent_strength / self_strength);
			set_strength(reduction_ratio);
			opponent.set_strength(0);
			opponent.kill();
			return;
		}

		if (opponent_strength > self_strength)
		{
			std::cout << opponent.name << " defeats " << name << std::endl;
			const double reduction_ratio = 1 - (self_strength / opponent_strength);
			set_strength(0);
			opponent.set_strength(reduction_ratio);
			kill();
		}
	} // battle

}

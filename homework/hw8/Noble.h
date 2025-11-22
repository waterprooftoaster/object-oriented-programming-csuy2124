// Noble.h
// Abstract base class for nobles in the game. Noble is a pure abstract class
// and does not hold an army. Derived classes like Lord will have armies.

#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <iostream>

namespace WarriorCraft
{
	class Protector;

	class Noble
	{
		bool dead = false;
		std::string name;

		// friends
		friend std::ostream &operator<<(std::ostream &os, const Noble &noble);

	public:
		virtual ~Noble() = default;

		// constructor
		explicit Noble(const std::string &noble_name) : name(noble_name) {}

		// method prototype
		virtual std::string get_name() const;

		virtual double get_strength() const;

		virtual bool set_strength(double reduction_ratio) = 0;

		virtual void battle(Noble &opponent);

		virtual void kill();

		virtual bool is_dead() const;

		virtual void speak() const = 0;
	}; // class Noble
}

#endif

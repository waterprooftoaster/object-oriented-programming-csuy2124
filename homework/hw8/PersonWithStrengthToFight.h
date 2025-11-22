// PersonWithStrengthToFight.h
// A type of Noble that has personal fighting strength and no army

#ifndef PERSONWITHSTRENGTHTOFIGHT_H
#define PERSONWITHSTRENGTHTOFIGHT_H

#include "Noble.h"

namespace WarriorCraft
{
	class PersonWithStrengthToFight : public Noble
	{
		double strength;

		friend std::ostream &operator<<(
				std::ostream &os,
				const PersonWithStrengthToFight &person);

	public:
		// constructor
		explicit PersonWithStrengthToFight(
				const std::string &noble_name,
				const int &personwithstrengthtofight_strength)
				: Noble(noble_name), strength(personwithstrengthtofight_strength) {}

		void speak() const override;

		double get_strength() const override;

		bool set_strength(double reduction_ratio) override;
	};
}

#endif

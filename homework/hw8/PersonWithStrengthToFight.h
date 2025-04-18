#ifndef PERSONWITHSTRENGTHTOFIGHT_H
#define PERSONWITHSTRENGTHTOFIGHT_H


#include "Noble.h"

namespace WarriorCraft {

class PersonWithStrengthToFight : public Noble{
int strength;

friend std::ostream& operator <<(std::ostream &os,
								const PersonWithStrengthToFight& person);

public:
	//constructor
	explicit PersonWithStrengthToFight(const std::string& noble_name,
		const int& personwithstrengthtofight_strength)
	: Noble(noble_name), strength(personwithstrengthtofight_strength) {}

	void speak() const override;
};

}

#endif

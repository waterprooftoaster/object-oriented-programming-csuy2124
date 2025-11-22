// Lord.h

#ifndef LORD_H
#define LORD_H

#include "Noble.h"
#include <vector>
#include <iostream>

namespace WarriorCraft
{
	class Protector;

	class Lord : public Noble
	{
		std::vector<Protector *> protectors;

		friend std::ostream &operator<<(std::ostream &os, const Lord &lord);

	public:
		// constructor
		explicit Lord(const std::string &noble_name) : Noble(noble_name) {}

		// destructor
		~Lord() = default;

		// methods
		bool hires(Protector &protector);

		bool fires(Protector &protector);

		bool remove_protector(Protector *protector);

		double get_strength() const override;

		bool set_strength(double reduction_ratio) override;

		void speak() const override;
	};

}

#endif
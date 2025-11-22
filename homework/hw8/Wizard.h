// Wizard.h

#ifndef WIZARD_H
#define WIZARD_H

#include "Protector.h"

namespace WarriorCraft
{
	class Wizard : public Protector
	{
		std::string sound = "POOF!";

	public:
		Wizard(const std::string &protector_name, const double &protector_strength)
				: Protector(protector_name, protector_strength) {}

		void speak() const override;
	};
}
#endif

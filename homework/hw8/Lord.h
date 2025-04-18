#ifndef LORD_H
#define LORD_H

#include "Noble.h"

namespace WarriorCraft {

class Lord : public Noble{
public:
	//constructor
	explicit Lord(const std::string& noble_name) : Noble(noble_name) {}
};

}

#endif
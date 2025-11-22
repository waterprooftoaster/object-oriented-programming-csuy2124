// Swordsman.cpp
// Implementation of the Swordsman class
// Andy Wu
// cw4483

#include "Swordsman.h"
#include "Noble.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{
  void Swordsman::speak() const
  {
    cout << sound << "  " << get_name() << " says: Take that in the name of my lord, " << get_employer()->get_name() << endl;
  }
}

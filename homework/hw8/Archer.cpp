// Archer.cpp
// Implementation of the Archer class
// Andy Wu
// cw4483

#include "Archer.h"
#include "Noble.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{
  void Archer::speak() const
  {
    cout << sound << "  " << get_name() << " says: Take that in the name of my lord, " << get_employer()->get_name() << endl;
  }
}

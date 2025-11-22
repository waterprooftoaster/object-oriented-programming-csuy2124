// Wizard.cpp
// Implementation of the Wizard class
// Andy Wu
// cw4483

#include "Wizard.h"
#include "Noble.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{
  void Wizard::speak() const
  {
    cout << sound << endl;
  }
}

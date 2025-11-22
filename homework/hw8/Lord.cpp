// Lord.cpp
// Implementation of the Lord class with army management functionality
// Andy Wu
// cw4483

#include "Lord.h"
#include "Protector.h"
#include <iostream>

using namespace std;

namespace WarriorCraft
{

  // output operator overloader
  ostream &operator<<(ostream &os, const Lord &lord)
  {
    os << lord.get_name() << " has an army of size: " << lord.protectors.size() << endl;
    for (size_t i = 0; i < lord.protectors.size(); i++)
    {
      os << *lord.protectors[i] << endl;
    }
    return os;
  }

  // hire
  bool Lord::hires(Protector &protector)
  {
    // do not hire if Protector is already hired or lord is dead
    if (protector.get_employer() != nullptr || is_dead() == true)
    {
      cout << get_name() << " failed to hire " << protector.get_name() << endl;
      return false;
    }

    Protector *protectorptr = &protector;
    // allow Protector to know their boss
    if (!protectorptr->set_employer(this))
    {
      return false;
    }
    protectors.push_back(protectorptr);
    return true;
  } // hire

  // fire
  bool Lord::fires(Protector &protector)
  {
    if (!remove_protector(&protector))
    {
      cout << get_name() << " failed to fire " << protector.get_name() << endl;
      return false;
    }

    cout << protector.get_name() << ", you don't work for me anymore ! -- "
         << get_name() << "." << endl;
    return true;
  } // fire

  // remove_protector
  bool Lord::remove_protector(Protector *protector)
  {
    if (is_dead() == true || protectors.size() == 0)
    {
      cout << get_name() << "failed to remove" << protector->get_name() << endl;
      return false;
    }
    for (size_t i = 0; i < protectors.size(); i++)
    {
      if (protectors[i] == protector)
      {
        protectors[i]->set_employer(nullptr);
        for (size_t j = i + 1; j < protectors.size(); j++)
        {
          protectors[j - 1] = protectors[j];
        }
        protectors.pop_back();
        return true;
      }
    }
    cout << "Protector not found" << endl;
    return false;
  } // remove_Protector

  // get_army_strength
  double Lord::get_strength() const
  {
    double army_strength = 0;
    for (size_t i = 0; i < protectors.size(); i++)
    {
      army_strength += protectors[i]->get_strength();
    }
    return army_strength;
  } // get_army_strength

  // set_strength
  bool Lord::set_strength(double reduction_ratio)
  {
    for (size_t i = 0; i < protectors.size(); i++)
    {
      if (!protectors[i]->set_strength(reduction_ratio))
      {
        return false;
      }
    }
    return true;
  } // set_strength

  // speak
  void Lord::speak() const
  {
    for (size_t i = 0; i < protectors.size(); i++)
    {
      protectors[i]->speak();
    }
  } // speak

}

//
// Created by waterprooftoaster on 2/20/2025.
/* Andy Wu
    Spring 2025
    hw4
 */
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...

class Warrior{
public:
    //constructor
    Warrior(const string& warrior_name, double warrior_strength)
    : name(warrior_name), strength(warrior_strength) {}

    //methods
    bool get_employment_status() const {return hired;}

    double get_strength() const {return strength;}

    string get_name() const { return name;}

    void set_employment_status(bool status) {hired = status;}

    void set_strength(double reduction_ratio) {strength = strength * reduction_ratio;}

private:
    friend ostream &operator << (ostream &os, const Warrior& warrior);

    bool hired = false;
    double strength;
    string name;
};

class Noble{
public:
    //constructor
    Noble(string noble_name) : name(noble_name) {}

    //methods
    string get_name() const {return name;}

    void kill() {dead = true;}

    void hire(Warrior& warrior){
        // do not hire if warrior is already hired or noble is dead
        if(warrior.get_employment_status() == true || dead == true) {
            cout << name << " failed to hire " << warrior.get_name() << endl;
        }

        else {
            Warrior* warriorptr = &warrior;
            warriors.emplace_back(warriorptr);
            warrior.set_employment_status(true);
            size++;
        }
    }

    void fire(Warrior& warrior){
        if (dead == true) {
            cout << name << " failed to fire " << warrior.get_name() << endl;
        }

        else {
            cout << warrior.get_name() << ", you don't work for me any more! -- "
                 << name << endl;

            for (size_t i = 0; i < warriors.size(); ++i) {
                if (warriors[i]->get_name() == warrior.get_name()) {
                    warriors[i] = nullptr; //dereference
                }
            }
            size--;
        }
    }

    double get_army_strength() const {
        double army_strength = 0;
        for (Warrior* curr_warrior : warriors) {
            army_strength += curr_warrior->get_strength();
        }
        return army_strength;
    }

    void set_strength(double reduction_ratio) {
        for (Warrior* curr_warrior : warriors) {
            curr_warrior->set_strength(reduction_ratio);
        }
    }

    void battle(Noble& opponent){
        double opponent_army = opponent.get_army_strength();
        double self_army = get_army_strength();
        string opponent_name = opponent.get_name();

        cout << name << " battles " << opponent_name << endl;

        if ((self_army == 0 && opponent_army != 0)
            || (self_army != 0 && opponent_army == 0)) {
            if (self_army == 0) {
                cout << "He's dead, " << opponent_name << endl;
            }

            if (opponent_army == 0) {
                cout << "He's dead, " << name << endl;
            }

            return; //prevents further checks
            }

        if (self_army == 0 && opponent_army == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;

            return; //prevents further checks
        }

        if (self_army == opponent_army) {
            cout << "Mutual Annihilation: " << name << " and "
                    << opponent_name << " die at each other's hands" << endl;
            kill();
            opponent.kill();
            set_strength(0);
            opponent.set_strength(0);


            return; //prevents further checks
        }

        if (self_army > opponent_army) {
            cout << name << " defeats " << opponent_name << endl;
            double reduction_ratio = self_army / opponent_army;
            set_strength(reduction_ratio);
            opponent.set_strength(0);
            opponent.kill();

            return; //prevents further checks
        }

        if (opponent_army > self_army) {
            cout << opponent_name << " defeats " << name << endl;
            double reduction_ratio = opponent_army / self_army;
            set_strength(0);
            opponent.set_strength(reduction_ratio);;
            kill();
        }
    }

private:
    friend ostream &operator << (ostream &os, const Noble& noble);

    vector<Warrior*> warriors;
    bool dead = false;
    string name;
    int size = 0;
};

ostream &operator << (ostream &os, const Noble& noble){
    os << noble.name << "  has an army of " << noble.size << endl;
    for (Warrior* curr_warrior : noble.warriors) {
        os << *curr_warrior << endl;
    }
    return os;
}

ostream &operator << (ostream &os, const Warrior& warrior){
    os << warrior.name << ": " << warrior.strength << endl;
    return os;
}


int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

} // main

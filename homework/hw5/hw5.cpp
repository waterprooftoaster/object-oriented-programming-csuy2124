/*
    hw05
    cw4483
    Andy Wu
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
classes
 */
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

    void set_strength(double reduction_ratio) {
      strength = strength * reduction_ratio;
    }

private:
    //friends
    friend ostream &operator << (ostream &os, const Warrior& warrior);

    //fields
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

    bool hire(Warrior& warrior){
        // do not hire if warrior is already hired or noble is dead
        if(warrior.get_employment_status() == true || dead == true) {
            cout << name << " failed to hire " << warrior.get_name() << endl;
            return false;
        }

        Warrior* warriorptr = &warrior;
        warriors.emplace_back(warriorptr);
        warrior.set_employment_status(true);
        return true;

    }

    bool fire(Warrior& warrior){
        if (dead == true) {
            cout << name << " failed to fire " << warrior.get_name() << endl;
            return false;
        }

        cout << warrior.get_name() << ", you don't work for me any more! -- "
             << name << endl;

        for (size_t i = 0; i < warriors.size(); ++i) {
            if (warriors[i]->get_name() == warrior.get_name()) {
                warriors[i] = nullptr; //dereference
                warriors.erase(warriors.begin() + i); //remove index
            }
        }
        warrior.set_employment_status(false);
        return true;
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
    //friends
    friend ostream &operator << (ostream &os, const Noble& noble);

    //fields
    vector<Warrior*> warriors;
    bool dead = false;
    string name;
};

/*
output overloaders
 */
ostream &operator << (ostream &os, const Noble& noble){
    os << noble.name << "  has an army of " << noble.warriors.size() << endl;
    for (Warrior* curr_warrior : noble.warriors) {
        os << *curr_warrior << endl;
    }
    return os;
}

ostream &operator << (ostream &os, const Warrior& warrior){
    os << warrior.name << ": " << warrior.strength << endl;
    return os;
}

/*
function headers
 */
void open_file(ifstream& file);
Warrior* search_warrior(const string& name, const vector<Warrior*>& warriors);
Noble* search_nobles(const string& name, const vector<Noble*>& nobles);
void deleteptrs(vector<Noble*>& nobles, vector<Warrior*>& warriors);

/*
functions
 */
void open_file(ifstream& file) {
    file.clear();
    file.open("nobleWarriors.txt");

    if (!file) {
        cerr << "failed to open nobleWarriors.txt";
        exit(1);
    }
}

Warrior* search_warriors(const string& name, const vector<Warrior*>& warriors) {
    for (Warrior* curr_warrior : warriors) {
        if (curr_warrior->get_name() == name) {
            return curr_warrior;
        }
    }
    return nullptr;
}

Noble* search_nobles(const string& name, const vector<Noble*>& nobles) {
    for (Noble* curr_noble : nobles) {
        if (curr_noble->get_name() == name) {
            return curr_noble;
        }
    }
    return nullptr;
}

void deleteptrs(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* curr_noble : nobles) {
        delete curr_noble;
        curr_noble = nullptr;
    }

    for (Warrior* curr_warrior : warriors) {
        delete curr_warrior;
        curr_warrior = nullptr;
    }
}

/*
main
 */
int main() {
    ifstream noble_warrior_file;
    open_file(noble_warrior_file);

    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    string token;

    while (noble_warrior_file >> token) {
        if (token == "Noble") {
            string noble_name;
            noble_warrior_file >> noble_name;

            if (search_nobles(noble_name, nobles)
                && nobles.size() > 0) {
                cout << "noble " << noble_name << " already exists" << endl;
            }

            else {
                nobles.emplace_back(new Noble(noble_name));
            }
        }

        if (token == "Warrior") {
            string warrior_name;
            int warrior_strength;
            noble_warrior_file >> warrior_name >> warrior_strength;

            if (search_warriors(warrior_name, warriors)
                && warriors.size() > 0) {
                cout << "warrior " << warrior_name << " already exists" << endl;
            }

            else {
                warriors.emplace_back(new Warrior(warrior_name
                                                  , warrior_strength));
            }
        }

        if (token == "Hire") {
            string noble_name, warrior_name;
            noble_warrior_file >> noble_name >> warrior_name;

            Noble* noble = search_nobles(noble_name, nobles);
            Warrior* warrior = search_warriors(warrior_name, warriors);

            if (!warrior) {
                cout << "Attempting to hire using unknown warrior: "
                     << warrior_name << endl;
            }

            if (!noble) {
                cout << "Attempting to hire using unknown noble: "
                     << noble_name << endl;
            }


            if (warrior == nullptr || noble == nullptr) {
                continue;
            }

            {noble->hire(*warrior);}

        }

        if (token == "Fire") {
            string noble_name, warrior_name;
            noble_warrior_file >> noble_name >> warrior_name;

            Noble* noble = search_nobles(noble_name, nobles);
            Warrior* warrior = search_warriors(warrior_name, warriors);

            if (warrior == nullptr) {
                cout << "Attempting to fire using unknown warrior: "
                     << warrior_name << endl;
            }

            if (noble == nullptr) {
                cout << "Attempting to fire using unknown noble: "
                     << noble_name << endl;
            }


            if (warrior == nullptr || noble == nullptr) {
                continue;
            }

            {noble->fire(*warrior);}
        }

        if (token == "Status") {
            bool unemployed = false;

            cout << "Status" << endl;
            cout << "======" << endl;
            cout << "Nobles" << endl;

            if (nobles.size() == 0) {cout << "NONE" << endl;}

            else {
                for (Noble* curr_noble : nobles) {
                    cout << *curr_noble << endl;
                }
            }

            cout << "Unemployed Warriors:" << endl;
            for (Warrior* curr_warrior : warriors) {

                if (curr_warrior->get_employment_status() == false) {
                    cout << *curr_warrior << endl;
                    unemployed = true;
                }
            }

            if (unemployed == false) { cout << "NONE" << endl; }
        }

        if (token == "Battle") {
            string noble_name, opponent_name;
            noble_warrior_file >> noble_name >> opponent_name;

            Noble* noble = search_nobles(noble_name, nobles);
            Noble* opponent = search_nobles(opponent_name, nobles);

            if (noble == nullptr || opponent == nullptr) {
                cout << "Attempting to battle using unknown noble(s)" << endl;
            }

            else {noble->battle(*opponent);}
        }

        if (token == "Clear") {
            deleteptrs(nobles, warriors);
            nobles.clear();
            warriors.clear();
        }
    }
}

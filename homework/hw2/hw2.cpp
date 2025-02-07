/*
Andy Wu
cw4483
Spring 2025
hw02
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

void open_file(ifstream &file);

Warrior create_warrior(const string &name, int strength);

void battle(Warrior &warrior1, Warrior &warrior2);

void display_warriors(const vector<Warrior> &warriors);

Warrior search_warrior(const string &name, const vector<Warrior>& warriors);

void modify_warrior(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior> &warriors);

void open_file(ifstream &file) {
    file.open("warriors.txt");

    if (!file) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}

Warrior create_warrior(const string &name, int strength) {
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    return warrior;
}

void display_warriors(const vector<Warrior>& warriors) {
    cout << "there are: " << warriors.size() << " warriors" << endl;
    for (const Warrior &curr: warriors) {
        cout << "Warrior: " << curr.name << ", "
                << "strength: " << curr.strength << endl;
    }
}

Warrior search_warrior(const string &name, const vector<Warrior>& warriors) {
    for (Warrior curr: warriors) {
        if (curr.name == name) {
            return curr;
        }
    }
}

void modify_warrior(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior> &warriors) {
    for (Warrior& curr : warriors) {
        if (curr.name == warrior1.name) {
            curr = warrior1;
        }
        if (curr.name == warrior2.name) {
            curr = warrior2;
        }
    }
}

void battle(Warrior& warrior1, Warrior& warrior2) {

    cout << warrior1.name << " battles " << warrior2.name << endl;

    if ((warrior1.strength == 0 && warrior2.strength != 0)
      ||(warrior2.strength == 0 && warrior1.strength != 0)) {
        if (warrior1.strength == 0) {
            cout << "He's dead, " << warrior2.name << endl;
            return;
        }

        if (warrior2.strength == 0) {
            cout << "He's dead, " << warrior1.name << endl;
            return;
        }
    }

    if (warrior1.strength == 0 && warrior2.strength == 0) {
         cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }

    if (warrior1.strength == warrior2.strength){
        cout << "Mutual Annihilation: " << warrior1.name << " and "
             << warrior2.name << " die at each other's hands" << endl;
        warrior1.strength = warrior2.strength = 0;
    }

    if (warrior1.strength > warrior2.strength) {
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
    }

    if (warrior2.strength > warrior1.strength) {
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
    }
}

int main() {
    vector<Warrior> warriors;
    ifstream warrior_file;
    open_file(warrior_file);

    string command;
    while (warrior_file >> command) {
        if (command == "Warrior") {
            int strength;
            string name;
            warrior_file >> name >> strength;
            Warrior warrior = create_warrior(name, strength);
            warriors.push_back(warrior);
        }

        if (command == "Battle") {
            string warrior1_name, warrior2_name;
            warrior_file >> warrior1_name >> warrior2_name;
            Warrior warrior1 = search_warrior(warrior1_name, warriors);
            Warrior warrior2 = search_warrior(warrior2_name, warriors);
            //cout << "main read " << warrior1.name << " should be fighting "
            //     << warrior2.name << endl; // debug
            battle(warrior1, warrior2);
            modify_warrior(warrior1, warrior2, warriors);
        }

        if (command == "Status") {
            display_warriors(warriors);
        }
    }
}

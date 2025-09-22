/*
Andy Wu
cw4483
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

// opens file with error message
void open_file(ifstream &file);

// searches for the correct warriors to battle
// avoids use of pointers by returning the actual vector element
Warrior& find_warrior(vector<Warrior>& warriors, const string& name);

// applies one battle between two warriors found in find_warrior
void battle(Warrior &warrior1, Warrior &warrior2);

// prints a summary of all warriors and their strengths.
void display_warriors(const vector<Warrior> &warriors);

int main() {
    vector<Warrior> warriors;
    ifstream warrior_file;
    open_file(warrior_file);
    string command;

    // read file by command and process accordingly
    while (warrior_file >> command) {
        if (command == "Warrior") {
            int strength;
            string name;
            warrior_file >> name >> strength;
            Warrior warrior{name, strength};
            warriors.push_back(warrior);
        }
        if (command == "Battle") {
            string warrior1_name, warrior2_name;
            warrior_file >> warrior1_name >> warrior2_name;
            // directly pass into func to avoid copying in main
            battle(find_warrior(warriors, warrior1_name), 
                   find_warrior(warriors, warrior2_name)
            );
        }
        if (command == "Status") {
            display_warriors(warriors);
        }
    }
    warrior_file.close();
} //main

void display_warriors(const vector<Warrior>& warriors) {
    cout << "there are: " << warriors.size() << " warriors" << endl;
    for (const Warrior &curr: warriors) {
        cout << "Warrior: " << curr.name << ", "
                << "strength: " << curr.strength << endl;
    }
}

Warrior& find_warrior(vector<Warrior>& warriors, const string& name) {
    for (Warrior &curr : warriors) {
        if (curr.name == name) {
            return curr; // reference to actual vector element
        }
    }
    cerr << "warrior not found" << endl;
}

void battle(Warrior& warrior1, Warrior& warrior2) {

    cout << warrior1.name << " battles " << warrior2.name << endl;

    if ((warrior1.strength == 0 ^ warrior2.strength == 0)) {
        if (warrior1.strength == 0) {
            cout << "He's dead, " << warrior2.name << endl;
        }
        if (warrior2.strength == 0) {
            cout << "He's dead, " << warrior1.name << endl;
        }
    }
    if (warrior1.strength == warrior2.strength){
        if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else {
        cout << "Mutual Annihilation: " << warrior1.name << " and "
            << warrior2.name << " die at each other's `hands" << endl;
        warrior1.strength = warrior2.strength = 0;
        }
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

void open_file(ifstream &file) {
    file.open("warriors.txt");

    if (!file) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
}

//testtest
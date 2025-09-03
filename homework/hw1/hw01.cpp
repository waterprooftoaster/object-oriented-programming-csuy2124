/*
Andy Wu
cw4483
hw01
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//open file
void open_file(ifstream &ifs);

// moves chr by however many steps 
char decrypt_char(char &chr, int step);

// for loop calls decrypt_char to decrypt sequence of chrs
void decrypt_string(string &input_str, int step);

int main() {
    // open file
    ifstream encrypted;
    open_file(encrypted);

    string line;
    vector<string> lines;
    int step;
    // get step
    encrypted >> step;  

    // gobble up
    getline(encrypted, line);

    // read each line as a vector
    while (getline(encrypted, line)) {
        lines.push_back(line); 
    }
    encrypted.close();

    // now reverse the vector 
    for (size_t i = 0; i < lines.size(); i++) {
        string curr_line = lines[lines.size() - i - 1];
        // decrypt each line
        decrypt_string(curr_line, step);
        cout << curr_line << endl;
    }
}

void open_file(ifstream &ifs){
    ifs.open("encrypted.txt");
    if(!ifs){
        cerr << "could not open file" << endl;
    }
}

char decrypt_char(char &chr, int step) {
    // check if upper case and decrypts if so
    if (chr <= 'Z' && chr >= 'A') {
        chr -= step;
        if (chr < 'A') {
            chr += 26; 
        }
        if (chr > 'Z') {
            chr -= 26;
        }
    }
    return chr;
}

void decrypt_string(string &input_str, int step) {
    for (char& chr : input_str) {
        chr = decrypt_char(chr, step);
    }
}
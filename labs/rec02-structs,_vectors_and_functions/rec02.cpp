/*
  rec02.cpp
  spring 2025
  Andy Wu
  cw4483
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Hydrocarbon{
  int H, C;
  vector<string> names;

  Hydrocarbon(int num_of_C, int num_of_H, vector<string> hydrocarbon_names) : 
  C(num_of_C), H(num_of_H), names(hydrocarbon_names){}

  void display() const{
    cout << "C" << C << "H" << H;
    for (const string& name : names){
      cout << " " << name;
    }
    cout << endl;
  }

  void add_name(const string &name) {
    names.push_back(name);
  }
};


//function headers
void open_file(ifstream &ifs);
Hydrocarbon create_hydrocarbon(const string &name, int C, int H);
vector<Hydrocarbon> read_hydrocarbs(ifstream &ifs);
void print_hydrocarbs(const vector<Hydrocarbon> &hydrocarbons);

//main
int main(){
  ifstream hydrocarb_stream;
  vector<Hydrocarbon> hydrocarbs = read_hydrocarbs(hydrocarb_stream);
  print_hydrocarbs(hydrocarbs);
}

void open_file(ifstream &ifs){
    ifs.open("hydrocarbs.txt");

    if(!ifs){
      cerr << "could not open file" << endl;
      exit(1);
    }
}

Hydrocarbon create_hydrocarbon(const string &name, int C, int H){
  //push name into new vector to match struct type
  vector<string> names;
  names.push_back(name);

  //create new hydocarb
  Hydrocarbon new_hydrocarbon(C, H, names);
  return new_hydrocarbon;
}

vector<Hydrocarbon> read_hydrocarbs(ifstream &ifs){
  open_file (ifs);

  int H, C;
  string name;
  char ignore;
  vector<Hydrocarbon> hydrocarbons;

  while (ifs >> name >> ignore >> C >> ignore >> H){

    for (Hydrocarbon curr : hydrocarbons){
      if (C == curr.C && H == curr.H){
        curr.add_name(name);

      } else {
        Hydrocarbon new_hydrocarbon = create_hydrocarbon(name, C, H);
        hydrocarbons.push_back(new_hydrocarbon);
      }
    }
  }
  return hydrocarbons;
}

void sort_hydrocarbs(){
  //sort
}

void print_hydrocarbs(const vector<Hydrocarbon> &hydrocarbons){
  for (Hydrocarbon curr : hydrocarbons){
    curr.display();
  }
}
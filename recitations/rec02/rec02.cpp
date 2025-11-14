/*
  rec02.cpp
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
  int C;
  int H;
  vector<string> names;
};

//function headers
void open_file(ifstream &ifs);
void read_hydrocarbs(ifstream &ifs, vector<Hydrocarbon>& hydrocarbons);
void create_hydrocarbon(vector<Hydrocarbon>& hydrocarbons, 
                        const string &name, int C, int H);
size_t find_hydrocarb(const vector<Hydrocarbon>& hydrocarbons, int C, int H);
void sort_hydrocarbs(vector<Hydrocarbon>& hydrocarbons);
void print_hydrocarbs(const vector<Hydrocarbon>& hydrocarbons);
void display(const Hydrocarbon& hydrocarbon);

//main
int main(){
  ifstream hydrocarb_stream;
  open_file(hydrocarb_stream);
  vector<Hydrocarbon> hydrocarbons;
  read_hydrocarbs(hydrocarb_stream, hydrocarbons);
  sort_hydrocarbs(hydrocarbons);
  print_hydrocarbs(hydrocarbons);
}

void open_file(ifstream &ifs){
  do {
    ifs.open("hydrocarbs.txt");
    if (!ifs) {
      cerr << "could not open file" << endl;
    }
  } while (!ifs);
}

void read_hydrocarbs(ifstream &ifs, vector<Hydrocarbon>& hydrocarbons) {
  int H, C;
  string name;
  char ignore;

  while(ifs >> name >> ignore >> C >> ignore >> H){
      create_hydrocarbon(hydrocarbons, name, C, H);
  }
  ifs.close();
}

// add vector as parameter
void create_hydrocarbon(vector<Hydrocarbon>& hydrocarbons, 
                        const string &name, int C, int H){
    //push name into new vector to match struct type
  size_t index = find_hydrocarb(hydrocarbons, C, H);

  if (index < hydrocarbons.size()) {
    hydrocarbons[index].names.push_back(name);
  }
  else {
    //create new hydocarb
    Hydrocarbon new_hydrocarbon{C, H, {name}};
    hydrocarbons.push_back(new_hydrocarbon);
  }
}

size_t find_hydrocarb(const vector<Hydrocarbon>& hydrocarbons, int C, int H){
  for (size_t i = 0; i < hydrocarbons.size(); i++){
    if (hydrocarbons[i].C == C && hydrocarbons[i].H == H){
      return i;
    }
  }
  return hydrocarbons.size();
}

void sort_hydrocarbs(vector<Hydrocarbon>& hydrocarbons){
  //bubble sort
  size_t n = hydrocarbons.size();

  for (size_t i = 0; i < n - 1; i++){
    for (size_t j = 0; j < n - i - 1; j++){
      if (hydrocarbons[j].C > hydrocarbons[j+1].C){
        swap(hydrocarbons[j], hydrocarbons[j+1]);
      }

      //if num of C is equal, sort based on H
      if (hydrocarbons[j].C == hydrocarbons[j+1].C){
        if(hydrocarbons[j].H > hydrocarbons[j+1].H){
          swap(hydrocarbons[j], hydrocarbons[j+1]);
        }
      }
    }
  }
}

void print_hydrocarbs(const vector<Hydrocarbon> &hydrocarbons){
  for (const Hydrocarbon curr : hydrocarbons){
    display(curr);
  }
}

void display(const Hydrocarbon& hydrocarbon){
  cout << "C" << hydrocarbon.C << "H" << hydrocarbon.H;
  for (const string name : hydrocarbon.names){
    cout << name << ", ";
  }
}
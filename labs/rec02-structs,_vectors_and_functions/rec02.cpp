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
  int C, H;
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
Hydrocarbon create_hydrocarbon(const string& name, int C, int H);
vector<Hydrocarbon> read_hydrocarbs(ifstream& ifs);
void combine_hydrocarbons(vector<Hydrocarbon>& hydrocarbs);
void print_hydrocarbs(const vector<Hydrocarbon>& hydrocarbons);
void sort_hydrocarbs(vector<Hydrocarbon>& hydrocarbs);

//main
int main(){
  ifstream hydrocarb_stream;
  vector<Hydrocarbon> hydrocarbs = read_hydrocarbs(hydrocarb_stream);
  combine_hydrocarbons(hydrocarbs);
  sort_hydrocarbs(hydrocarbs);
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
  open_file(ifs);

  int H, C;
  string name;
  char ignore;
  vector<Hydrocarbon> hydrocarbons;

  while(ifs >> name >> ignore >> C >> ignore >> H){
    Hydrocarbon new_hydrocarbon = create_hydrocarbon(name, C, H);
    hydrocarbons.push_back(new_hydrocarbon);
  }

  return hydrocarbons;
}

void combine_hydrocarbons(vector<Hydrocarbon>& hydrocarbs){
  //x = curr index, i = index for searching
  for(size_t x = 0; x < hydrocarbs.size(); x++){
    for(size_t i = 0; i < hydrocarbs.size(); i++){

      //add name if same formula
      if (hydrocarbs[i].C == hydrocarbs[x].C && hydrocarbs[i].H == hydrocarbs[x].H && i != x){
        hydrocarbs[x].add_name((hydrocarbs[i].names)[0]);

        //remove duplicate index
        size_t remove = i;
        hydrocarbs.erase(hydrocarbs.begin() + remove);
      }
    }
  }
}

void sort_hydrocarbs(vector<Hydrocarbon>& hydrocarbs){
  //bubble sort
  size_t n = hydrocarbs.size();

  for (size_t i = 0; i < n - 1; i++){

    for (size_t j = 0; j < n - i - 1; j++){

      if (hydrocarbs[j].C > hydrocarbs[j+1].C){
        swap(hydrocarbs[j], hydrocarbs[j+1]);
      }

      //if num of C is equal, sort based on H
      if (hydrocarbs[j].C == hydrocarbs[j+1].C){

        if(hydrocarbs[j].H > hydrocarbs[j+1].H){
          swap(hydrocarbs[j], hydrocarbs[j+1]);
        }
      }
    }
  }
}

void print_hydrocarbs(const vector<Hydrocarbon> &hydrocarbons){
  for (Hydrocarbon curr : hydrocarbons){
    curr.display();
  }
}
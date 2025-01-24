/*
  rec01.cpp
  fall 2024
 Andy Wu
 cw4483
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    
    //std::cout << "hello world" << std::endl;

    // Task 2  Printing hello ...  Using "using namespace"
    
    cout << "hello world" << endl;
    
    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    //cout << " diplaying uninitialized variable x: " << x << endl;
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    
    cout << "size of y " << sizeof(y) << '\n'
         << "sze of z " << sizeof(z) << '\n'
         << "size of pie " << sizeof(pie) << endl;
    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    //x = "felix";

    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y > 10 || y < 20){
        cout << "y is between 10 and 20" << endl;
    } else {
        cout << "y is not between 10 and 20" << endl;
    }

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive
    
    // First with a for loop
    for (int i = 10; i <= 20; i++){
        cout << i;
        
        if (i == 20){
            cout << "\n" << endl;
        }
    }
    
    
    
    // Then with a while loop
    int j = 10;
    
    while (j <= 20){
        cout << j;
        j++;
        
        if (j > 20){
            cout << "\n" << endl;
        }
    }

   
    
    // Finally with a do-while loop
    int k = 10;
    
    do {
        cout << k;
        k++;
        
        if (k > 20){
            cout << "\n" << endl;
        }

    } while (k <= 20);
    
  
    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    
    do {
        ifs.open("text.txt");
    } while (!ifs);
    
    // Task 9  Looping, reading file word by "word".
    string word;
    
    while (ifs >> word){
        cout << word << " ";
    }
    
    if (ifs.eof()){
        cout << "\n" << endl;
    }

    ifs.close();
    
    // Task 10 Open a file of integers, read it in, and display the sum.
    ifs.open("integers.txt");
    
    int integer;
    int sum = 0;
    
    while (ifs >> integer){
        sum += integer;
    }
    
    cout << sum;
    
    if (ifs.eof()){
        cout << "\n" << endl;
    }
    
    ifs.close();
    
    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifs.open("mixed.txt");
    
    string token;
    int sum11 = 0;
    
    while (ifs >> token){
        stringstream ss(token);
        int integer11;
        
        if (ss >> integer11){
            sum11 += integer11;
        } else {
            //skip
        }
    }
    
    cout << sum11;
    
    if (ifs.eof()){
        cout << "\n" << endl;
    }
    
    ifs.close();
   
    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> evens;
    
    for (int x = 10; x <= 100; x += 2){
        evens.push_back(x);
    }
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t y = 0; y < evens.size(); y++){
        cout << evens[y];
    }
    
    cout << endl;
    
    //         b) using a "ranged for"
    for (int z: evens){
        cout << z;
    }
    
    cout << endl;
    
    //         c) using indices again but backwards
    for (size_t  num = evens.size(); num > 0; num++){
        cout << evens[num];
    }

    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> primes  = {2, 3, 5, 7, 11, 13, 17, 19};
    
    for (int prime : primes){
        cout << prime;
    }
    out << endl;
    
} // main



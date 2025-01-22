#include <iostream> //#include imports library. defines cout, cin
using namespace std;

//extra credit: Bjame Stroustrup created C++

int main(){ //every program needs a main function

    cout << "Hello CS2124!\n"; //every statement ends in ;
    // << is the output operator
    // cout is the "stream", will be defined later
    // ''denotes char, "" denotes str

    cout << "another way to end line" << endl;
    // /n skips line, endl ends the stream

    int x = 5;
    cout << "x:" << x << endl; 
    //x is undefined, but it'll run. value differ between machines
    //do not do this, always initialize
    //memory of variables in a function is destroyed when program leaves the function
    
    return 0; 
} // every block ends in }



#include <iostream>
#include <vector>
#include <string>   

using namespace std;

//part 1a 
void print2(int val1,int val2)
{
    cout << "Value 1: " << val1 << endl;
    cout << "Value 2: " << val2 << endl;
}

//part 1b
int alter(int val)
{
    return val*2+5;
}

//part 1d
void printodd()
{
    cout << "Odd numbers between 0 and 20: ";
    for(int i=1;i<20;i = i+2){
        cout << i << " ";
    }
    cout << endl;
}

//part 1e
void prrintrandarray()
{
    srand(time(0)); 
    cout << "Random array values : ";
    int mynums[5] = {0,0,0,0,0};
    for(int i: mynums){
        i = rand() % 100;
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    cout << "part 1a" << endl;
    print2(2,7);
    cout << "part 1b" << endl;
    cout << alter(5) << endl;
    cout << "part 1c" << endl;
    //part 1c
    string food = "bread";
    string* ptr = &food;
    cout << *ptr << endl;
    *ptr = "toast";
    cout << *ptr << endl;
    cout << "part 1d" << endl;
    printodd();
    cout << "part 1e" << endl;
    prrintrandarray();
}
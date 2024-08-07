#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

//part 1f
void splitstring(){
    string str = "this has spaces in it";
    string s;
    
    stringstream ss(str);
    vector<string> v;
    while (getline(ss, s, ' ')) {
        v.push_back(s);
    }

    cout << "list of words:" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}

//part 1g
class Tester
{
    int startpoint;
    int multiplier;
    int endpoint;
    void DoCalc()
    {
        endpoint = startpoint * multiplier;
    }
    public:
        string name;
        Tester( string namein,int start,int multi)
        {
            name = namein;
            startpoint = start;
            multiplier = multi;
            DoCalc();
        }
        void SetStart(int start)
        {
            startpoint = start;
            DoCalc();
        }
        int GetEnd(){return endpoint;}
};

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
    cout << "part 1f" << endl;
    splitstring();
    cout << "part 1g" << endl;
    Tester tester = Tester("Tester",5,7);
    cout << "Name: " << tester.name << ", Enpoint: " << tester.GetEnd() << endl;
    tester.name = "Tester Changed";
    tester.SetStart(20);
    cout << "Name: " << tester.name << ", Enpoint: " << tester.GetEnd() << endl;
}
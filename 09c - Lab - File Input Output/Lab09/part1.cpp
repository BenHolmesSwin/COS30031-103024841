// Lab09part1.cpp

#include <iostream>
#include <fstream>
#include <string>

#include "part1.h"

using namespace std;

class MyValues {
	public:
		MyValues(int idIn, char typeIn, float countIn) { //constructor for part a.3
			id = idIn;
			type = typeIn;
			count = countIn;
		}
		int id;
		char type;
		float count;
};

void printMyValues(MyValues values) { // part a.4
	cout << "The Values of class id: " << values.id << endl;
	cout << "Type: " << values.type << endl;
	cout << "Count: " << values.count << endl;
}

void writeToFileTxt(MyValues values) {
	ofstream myfile;
	myfile.open("partb.txt");
	myfile << values.id << endl;
	myfile << values.type << endl;
	myfile << values.count << endl;
	myfile.close();
}

MyValues readFromFileTxt(string file) {
	ifstream myfile;
	int idIn;
	char typeIn;
	float countIn;
	string line; //each ,ine will be stored in this temporarily
	myfile.open(file);
	myfile >> line;
	idIn = stoi(line);//converting string to int
	myfile >> line;
	typeIn = line[0];//grabing first char in string as only one char
	myfile >> line;
	countIn = stof(line);//converting string to float
	myfile.close();
	auto values = MyValues(idIn, typeIn, countIn);
	return values;
}

int part1main()
{
	//part a
	cout << "Part A" << endl;
	auto values = MyValues(1, 'D', 5.78);
	printMyValues(values);
	cout << endl;

	//part b
	cout << "Part B" << endl;
	auto valuesB = MyValues(2, 'F', 6.1);
	writeToFileTxt(valuesB);
	auto valuesBOutput = readFromFileTxt("partb.txt");
	printMyValues(valuesBOutput);
	cout << endl;

	//part c
	cout << "Part C" << endl;
	int intIn = 3;
	char charIn = 'R';
	int int2In = 102;

	//writing
	ofstream outfile;
	outfile.open("partc.bin", ofstream::binary);
	outfile.write((char*)&intIn, sizeof intIn);
	outfile.write((char*)&charIn, sizeof charIn);
	outfile.write((char*)&int2In, sizeof int2In);
	outfile.close();

	//reading
	ifstream infile;
	int intOut;
	char charOut;
	int int2Out;
	string line; //each line will be stored in this temporarily
	infile.open("partc.bin", ifstream::binary);
	infile.read((char*)&intOut, sizeof intIn);
	//idIn = stoi(line);//converting string to int
	infile.read((char*)&charOut, sizeof charIn);
	//typeIn = line[0];//grabing first char in string as only one char
	infile.read((char*)&int2Out, sizeof int2In);
	//countIn = stof(line);//converting string to float
	infile.close();

	//printing
	cout << "First value: " << intOut << endl;
	cout << "Second value: " << charOut << endl;
	cout << "Third value: " << int2Out << endl;

	cout << endl;




	return 0;
}



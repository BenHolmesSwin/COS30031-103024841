#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "part2.h"

using namespace std;

vector<string> split(string& s, const string& delimiter) {// split tokens
	vector<string> tokens;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	tokens.push_back(s);

	return tokens;
}

int part2main()
{
	ifstream myfile;
	myfile.open("test2.txt");
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line[0] != '#' && line.length() != 0) {
				string delimiter = ":";
				auto tokens = split(line, delimiter);
				if (tokens.size() == 3) { // checking tokens
					for (string token : tokens) {
						cout << token << endl;
					}
				}
			}
		}
		myfile.close();
	}

	return 0;
}
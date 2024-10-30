#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Data {
    int loops;
    int time;
    float loopsPerSec;
    int numBoxes;
};

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

int main(){
    fstream infile;
    ofstream outfile;
    infile.open("results.txt");
    outfile.open("fomatedResults.txt");
    
    while(!infile.eof()){
        Data outData;
        for(int i = 0;i < 4; i++){
            string line;
            getline(infile, line);
            auto tokens = split(line, ": \t");
            switch(i){
                case 0:
                    outData.loops = stoi(tokens[2]);
                break;
                case 1:
                    outData.time = stoi(tokens[1]) /1000;
                break;
                case 2:
                    outData.loopsPerSec = stoi(tokens[1]);
                break;
                case 3:
                    outData.numBoxes = stoi(tokens[1]);
                break;
            }
                
        }
        outfile << outData.loops << "," << outData.time << "," << outData.loopsPerSec << "," << outData.numBoxes << endl;
    }
}
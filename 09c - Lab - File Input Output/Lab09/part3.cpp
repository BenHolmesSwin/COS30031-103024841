#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"
#include "part3.h"

using namespace std;
using json = nlohmann::json;

int part3main() {
	ifstream myfile("test3.json");
	json data = json::parse(myfile);
	cout << data.dump(4) << endl;
	return 0;
}
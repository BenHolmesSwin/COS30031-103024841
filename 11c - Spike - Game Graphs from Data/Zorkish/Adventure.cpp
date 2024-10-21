#include <fstream>
#include <iostream>

#include "json.hpp"
#include "Location.h"
#include "Adventure.h"

using namespace std;
using json = nlohmann::json;

Adventure::Adventure(const char* fileName)
{
	json jsonData;
	string s = fileName;
	ifstream file(s);
	if (!file.is_open()) {
		cout << "Error opening file: " << fileName << endl;
		return;
	}

	try {
		file >> jsonData;
	}
	catch (const json::parse_error& e) {
		cout << "Parse error at byte " << e.byte << ": " << e.what() << endl;
	}
	file.close();
	Start(jsonData);
}

void Adventure::Start(json data){

	data.at("locations").get_to(graph);

	//for testing output currently
	for (location::Location l : graph) {
		if (l.id == "castle") {
			current = l;
		}
	}
}

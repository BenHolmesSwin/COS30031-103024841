#pragma once

#include <string>
#include <vector>

using namespace std;

namespace location {
	struct Location
	{
		string id;
		string name;
		string description;
		vector<string> connections;
	};

}
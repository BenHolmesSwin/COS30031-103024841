#pragma once

#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

namespace path {
	class Path {
	public:
		string findLoc(string loc);
		string locactionId1;
		string locactionId2;
	};

	void from_json(const json& j, Path& p);
}
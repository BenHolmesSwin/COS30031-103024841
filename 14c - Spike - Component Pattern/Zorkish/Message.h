#pragma once

#include <string>

using namespace std;

struct Message {
	string from;
	string to;
	string type;
	void* data;
	string message;
};
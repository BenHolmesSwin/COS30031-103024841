#pragma once

#include <string>

using namespace std;

struct Message {
	string from; //where message is from
	string to; //where message is to
	string type; //the type of message, open, use, health, sucess, failure
	string additional; //additional info, used for double move, such as target of use and health change (converted to string and back)
	string message; //message info, used for console output and testing purposes
	bool operator==(const Message& rhs) const {
		return type == rhs.type && to == rhs.to && from == rhs.from && message == rhs.message && additional == rhs.additional;
	}
};


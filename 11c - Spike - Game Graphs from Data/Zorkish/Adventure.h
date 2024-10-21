#pragma once

#include "Location.h"
#include "json.hpp"

class Adventure
{
public:
	Adventure(const char* fileName);
	location::Location current;
	void Start(json data);
private:

};
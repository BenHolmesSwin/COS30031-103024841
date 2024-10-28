#pragma once

#include <vector>
#include "Entity.h"

class Adventure;
class Component;

class ComponentManager {
public:
	void createAdventureComponents(Adventure& adventure);
};
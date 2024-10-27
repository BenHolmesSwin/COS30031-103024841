#pragma once


using namespace std;
#include "Entity.h"



class Component {
public:
	virtual ~Component(){}
	virtual Message execute(entity::Entity& entity,Message message) = 0;
};


class OpenComponent : public Component { //changes open state dependent on message and locked or not
	Message execute(entity::Entity& entity, Message message) override;
};

class UseComponent : public Component { //gets either heal or attack components value and sends message to target entity
	Message execute(entity::Entity& entity, Message message) override;
};

class HealthComponent : public Component {//changes health value dependent on message input
	Message execute(entity::Entity& entity, Message message) override;
};

class AttackComponent : public Component {
	int value = -5; //preset value for attack component atm
	Message execute(entity::Entity& entity, Message message) override;
};

class HealComponent : public Component {
	int value = 2; //preset value for heal component atm
	Message execute(entity::Entity& entity, Message message) override;
};
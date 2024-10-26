#pragma once


using namespace std;
#include "Entity.h"



class Component {
public:
	virtual ~Component(){}
	virtual int check() = 0;
	virtual void execute(entity::Entity& entity,Message message) = 0;
};


class OpenComponent : public Component {
	int check() override;
	void execute(entity::Entity& entity, Message message) override;
};

class UseComponent : public Component {
	int check() override;
	void execute(entity::Entity& entity, Message message) override;
};

class HealthComponent : public Component {
	int check() override;
	void execute(entity::Entity& entity, Message message) override;
};

class AttackComponent : public Component {
	int value = -5;
	int check() override;
	void execute(entity::Entity& entity, Message message) override;
};

class HealComponent : public Component {
	int value = 2;
	int check()override;
	void execute(entity::Entity& entity, Message message) override;
};
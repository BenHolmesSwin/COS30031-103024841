#pragma once


using namespace std;
#include "Entity.h"

class Component {
public:
	virtual ~Component(){}
	virtual bool check(entity::Entity& entity) = 0;
	virtual int check(entity::Entity& entity, string in) = 0;
	virtual bool execute(entity::Entity& entity) = 0;
	virtual bool execute(entity::Entity& entity,string in) = 0;
	virtual bool execute(entity::Entity& entitySelf,entity::Entity entityTarget) = 0;
};


class OpenComponent : public Component {
	bool check(entity::Entity& entity) override;
	bool execute(entity::Entity& entity) override;
	bool execute(entity::Entity& entity, string in) override;
};

class UseComponent : public Component {
	bool check(entity::Entity& entity) override;
	bool execute(entity::Entity& entitySelf, entity::Entity entityTarget) override;
};

class HealthComponent : public Component {
	int check(entity::Entity& entity, string in)override;
	bool execute(entity::Entity& entity) override;
};
#pragma once


class Component {
public:
	virtual ~Component(){}
	virtual void update(Entity& entity) = 0;
};


class OpenComponent : Component {
	void update(Entity& entity);
};

class UseComponent : Component {
	void update(Entity& entity);
};

class HealthComponent : Component {
	void update(Entity& entity);
};
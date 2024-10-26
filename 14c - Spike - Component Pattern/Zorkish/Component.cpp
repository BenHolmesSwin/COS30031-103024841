

#include "Component.h"
#include "Message.h"



void OpenComponent::execute(entity::Entity& entity, Message message) {
		entity.open = true;
		entity.locked = false;
}


int HealComponent::check() {
	return value;
}

int AttackComponent::check() {
	return value;
}
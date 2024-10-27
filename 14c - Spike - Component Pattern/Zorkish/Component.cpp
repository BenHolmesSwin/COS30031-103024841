

#include "Component.h"
#include "Message.h"
#include "Entity.h"


Message OpenComponent::execute(entity::Entity& entity, Message message) {
	Message msgResult;
	if (entity.open) {
		msgResult.type = "sucess";
		msgResult.message = entity.name + " is already open!";
	}
	else if (entity.locked) {
		if (message.additional == "key") {
			entity.open = true;
			entity.locked = false;
			msgResult.type = "sucess";
			msgResult.message = entity.name + " has been opened with key";
		}
		else {
			msgResult.type = "failure";
			msgResult.message = entity.name + " needs key in inventory to open! (use WITH)";
		}
	}
	else {
		entity.open = true;
		msgResult.type = "sucess";
		msgResult.message = entity.name + " has been opened!";
	}
	return msgResult;
}

int OpenComponent::check() {
	return 0;
}


int HealComponent::check() {
	return value;
}

int AttackComponent::check() {
	return value;
}

#include <string>

#include "Component.h"
#include "Message.h"
#include "Entity.h"

using namespace std;

Message OpenComponent::execute(entity::Entity& entity, Message message) {
	Message msgResult;
	msgResult.to = "output";
	msgResult.from = entity.name;
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

Message UseComponent::execute(entity::Entity& entity, Message message) {
	Message msgResult;
	msgResult.type = "health"; // all covered by health
	msgResult.to = message.additional;
	msgResult.from = entity.name;
	if (entity.components.count("heal")) { //checking if component heal
		msgResult = entity.components["heal"]->execute(entity, msgResult);  // changes msgResult additional to "[int]" (currently 2)
		msgResult.message = entity.name + " used to heal " + msgResult.to;
	}
	else if (entity.components.count("attack")) { //checking if component attack
		msgResult = entity.components["attack"]->execute(entity, msgResult); // changes msgResult additional to "-[int]" (currently -5)
		msgResult.message = entity.name + " used to attack " + msgResult.to;
	}
	else {
		msgResult.type = "failure";
		msgResult.message = entity.name + " has no use (heal or attack ability)";
	}
	return msgResult;
}

Message HealthComponent::execute(entity::Entity& entity, Message message) {
	Message msgResult;
	msgResult.to = "output";
	msgResult.from = entity.name;
	try {
		if (entity.health > 0) {
			int value = stoi(message.additional);
			entity.health += value;
			msgResult.type = "sucess";
			string change;
			if (value > 0) { // changes output message by 
				change = " was healed with ";
			}
			else {
				change = " was attacked with ";
			}
			msgResult.message = entity.name + change + message.from + " health is now " + to_string(entity.health) + " (" + message.additional + ")";
			if (entity.health <= 0) {//this is after the change, which can be negative, only activates after the change
				entity.description += " |DEAD!|";
			}
		}
		else {
			msgResult.type = "failure";
			msgResult.message = entity.name + " is dead, cannot use " + message.from + " on it";
		}
		return msgResult;
	}
	catch (exception& e) {
		msgResult.type = "failure";
		msgResult.message = entity.name + " somehow a non number was passed into health component execute";
		return msgResult;
	}
}

Message HealComponent::execute(entity::Entity& entity, Message message) { //changes the additional to value as a string
	message.additional = to_string(value);
	return message;
}

Message AttackComponent::execute(entity::Entity& entity, Message message) { //changes the additional to value as a string
	message.additional = to_string(value);
	return message;
}
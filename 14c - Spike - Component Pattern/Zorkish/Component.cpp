

#include "Component.h"

bool OpenComponent::check(entity::Entity& entity) {
	return entity.open;
}

bool OpenComponent::execute(entity::Entity& entity) {
	if (entity.locked) {
		return false;
	}
	else {
		entity.open = true;
		return true;
	}
}

bool OpenComponent::execute(entity::Entity& entity,string in) {
	if (in == "key") {
		entity.open = true;
		entity.locked = false;
		return true;
	}else{
		return false;
	}
}
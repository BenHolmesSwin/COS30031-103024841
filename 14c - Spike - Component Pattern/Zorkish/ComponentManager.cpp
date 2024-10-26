

#include "ComponentManager.h"
#include "Adventure.h"
#include "Component.h"
#include "Entity.h"


void addComponentsToEntity(entity::Entity& entity) {
	for (auto& comp : entity.componentsList) {
		if (comp == "open") {
			entity.components[comp] = new OpenComponent();
		}
	}
}

void ComponentManager::createAdventureComponents(Adventure& adventure) {
	for (auto& item : adventure.player.inventory) {
		addComponentsToEntity(item.second);
	}
	for (auto& loc : adventure.graph) {
		for (auto& item : loc.second.contents) {
			addComponentsToEntity(item.second);
		}
	}
}

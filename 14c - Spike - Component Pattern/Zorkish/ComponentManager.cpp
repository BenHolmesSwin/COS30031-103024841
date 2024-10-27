

#include "ComponentManager.h"
#include "Adventure.h"
#include "Component.h"
#include "Entity.h"


void addComponentsToEntity(entity::Entity& entity) {
	for (auto& comp : entity.componentsList) {
		if (comp == "open") {
			entity.componentAdd(comp, new OpenComponent());
		}else if (comp == "use") {
			entity.componentAdd(comp, new UseComponent());
		}else if (comp == "heal") {
			entity.componentAdd(comp, new HealComponent());
		}else if (comp == "attack") {
			entity.componentAdd(comp, new AttackComponent());
		}else if (comp == "health") {
			entity.componentAdd(comp, new HealthComponent());
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


#include "MessageBoard.h"
#include "Message.h"
#include "Adventure.h"

using namespace std;

void MessageBoard::addMessage(Message message) {
	messages.push_back(message);
}

void MessageBoard::doMessages(Adventure& adventure) {
	for (Message message : messages) {
		if (adventure.graph[adventure.current].contents.count(message.to)) {
			adventure.graph[adventure.current].contents[message.to].recieveMessage(message);
		}
		else if (adventure.player.inventory.count(message.to)) {
			adventure.player.inventory[message.to].recieveMessage(message);
		}
	}
}

bool MessageBoard::areThereMessages() {
	if (messages.empty()) {
		return false;
	}
	return true;
}
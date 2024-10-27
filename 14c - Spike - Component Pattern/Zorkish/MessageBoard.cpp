
#include <iostream>


#include "Message.h"
#include "Adventure.h"
#include "Player.h"
#include "MessageBoard.h"

using namespace std;

void MessageBoard::addMessage(Message message) {
	messages.push_back(message);
}

void MessageBoard::doMessages(Adventure& adventure) {
	for (Message message : messages) {
		if (message.type == "sucess" || message.type == "failure") {//check this first as some sucess/failure messages can have message.to's
			cout << message.message << endl;
		}else if (message.to == "player") {//checking if it is to player, this is for Put
			adventure.player.recieveMessage(message, *this);
		}else if (adventure.graph[adventure.current].contents.count(message.to)) {//checking if in location
			adventure.graph[adventure.current].contents[message.to].recieveMessage(message, *this);
		}
		else if (adventure.player.inventory.count(message.to)) {//checking if in inventory
			adventure.player.inventory[message.to].recieveMessage(message, *this);
		}
		messages.erase(remove(begin(messages),end(messages),message));//this erases the message from the vector
	}
}

bool MessageBoard::areThereMessages() {
	if (messages.empty()) {
		return false;
	}
	return true;
}
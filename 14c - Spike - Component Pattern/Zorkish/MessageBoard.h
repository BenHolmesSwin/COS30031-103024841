#pragma once

#include <vector>
#include "Message.h"

using namespace std;

class Adventure;

class MessageBoard {
public:
	void addMessage(Message message);
	void doMessages(Adventure& adventure);
	bool areThereMessages();
private:
	vector<Message> messages;
};
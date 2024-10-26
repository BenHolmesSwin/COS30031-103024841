
#include "MessageBoard.h"
#include "Message.h"
#include "Adventure.h"

using namespace std;

void MessageBoard::addMessage(Message message) {

}

void MessageBoard::doMessages(Adventure& adventure) {

}

bool MessageBoard::areThereMessages() {
	if (messages.empty()) {
		return false;
	}
	return true;
}
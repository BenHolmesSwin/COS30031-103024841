
#include "SDLcollision.h"
#include "square.h"


bool squareCollision(Square selfSquare, Square otherSquare) {
	//if bottom of selfSquare is outside top of otherSquare
	if (selfSquare.mPosY + selfSquare.squareH <= otherSquare.mPosY) {
		return false;
	}

	if (selfSquare.mPosY >= otherSquare.mPosY + otherSquare.squareH) {
		return false;
	}

	if (selfSquare.mPosX + selfSquare.squareW <= otherSquare.mPosX) {
		return false;
	}

	if (selfSquare.mPosX >= otherSquare.mPosX + otherSquare.squareW) {
		return false;
	}

	return true;
}
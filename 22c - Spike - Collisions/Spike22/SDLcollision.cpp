
#include <cmath>

#include "SDLcollision.h"
#include "square.h"
#include "circle.h"


bool boxOnBox(Square a, Square b) {
	//if bottom of a is less than top of b
	if (a.mPosY + a.squareH <= b.mPosY) {
		return false;
	}
	//if top of a is greater than bottom of b
	if (a.mPosY >= b.mPosY + b.squareH) {
		return false;
	}
	//if right of a is less than left of b
	if (a.mPosX + a.squareW <= b.mPosX) {
		return false;
	}
	//if left of a is greater than right of b
	if (a.mPosX >= b.mPosX + b.squareW) {
		return false;
	}

	return true;
}

bool circleOnCircle(Circle a, Circle b) {
	//the overlap distance square (to avoid sqrt)
	int overlapDistance = pow((a.radius + b.radius),2);
	int distance = pow((a.centY - b.centY), 2) + pow((a.centX - b.centX), 2);

	return distance < overlapDistance;
}
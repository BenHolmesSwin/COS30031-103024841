
#include <cmath>

#include "SDLcollision.h"
#include "square.h"
#include "circle.h"


bool squareCollision(Square a, Square b) {
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

bool circleCollision(Circle a, Circle b) {
	//the overlap distance square (to avoid sqrt)
	int overlapDistance = (a.radius + b.radius) ^ 2;

	int xDist, yDist;
	//checking which x is greater to produce positive value
	if (a.centX < b.centX) {
		xDist = (b.centX - a.centX) ^ 2;
	}
	else {
		xDist = (a.centX - b.centX) ^ 2;
	}
	//checking which y is greater to prodduce positive value
	if (a.centY < b.centY) {
		yDist = (b.centY - a.centY) ^ 2;
	}
	else {
		yDist = (a.centY - b.centY) ^ 2;
	}
	int distance = xDist + yDist;

	return distance < overlapDistance;
}
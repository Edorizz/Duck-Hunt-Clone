#include "Polygon.h"
#include <iostream>

void Polygon::AddVertex(Point vertex) {
	vertices.push_back(vertex);
	mSides = vertices.size();
	if (vertices.size() > 0) {
		mIsCircle = false;
	}
}

bool Polygon::IsInside(Point point) {
	if (mIsCircle) {
		int deltaX = point.x  + mPosX - (mPosX + d2CenterX);
		int deltaY = point.y  + mPosY - (mPosY + d2CenterY);
		return ((deltaX * deltaX) + (deltaY * deltaY) <= (radius * radius));
	}
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].PosX = mPosX + vertices[i].x;
		vertices[i].PosY = mPosY + vertices[i].y;
	}
	bool c = false;
	int i, j;
	for (i = 0, j = GetSides() - 1; i < GetSides(); j = i++) {
		if (((GetVertex(i)->PosY > point.y) != (GetVertex(j)->PosY > point.y)) &&
			(point.x < (GetVertex(j)->PosX - GetVertex(i)->PosX) * (point.y - GetVertex(i)->PosY) / (GetVertex(j)->PosY - GetVertex(i)->PosY) + GetVertex(i)->PosX)) {
			c = !c;
		}
	}
	return c;
}
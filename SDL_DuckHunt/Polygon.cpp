#include "Polygon.h"

void Polygon::AddVertex(Point vertex) { // Adds a vertex (position relative to polygon's position)
	vertex.x += mPosX;
	vertex.y += mPosY;
	vertices.push_back(vertex);
	mSides = vertices.size();
	if (vertices.size() > 0) {
		mIsCircle = false;
	}
}

bool Polygon::IsInside(Point point) {
	bool c = false;
	if (mIsCircle) {
		int deltaX = point.x - mPosX + radius;
		int deltaY = point.y - mPosY + radius;
		return deltaX * deltaX + deltaY * deltaY < radius * radius;
	}
	 
	int i, j;
	for (i = 0, j = GetSides() - 1; i < GetSides(); j = i++) {
		if (((GetVertex(i)->y > point.y) != (GetVertex(j)->y > point.y)) &&
			(point.x < (GetVertex(j)->x - GetVertex(i)->x) * (point.y - GetVertex(i)->y) / (GetVertex(j)->y - GetVertex(i)->y) + GetVertex(i)->x)) {
			c = !c;
		}
	}
	return c;
}
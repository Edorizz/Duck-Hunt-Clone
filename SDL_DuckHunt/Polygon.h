#pragma once
#include <vector>

struct Point {
	int x, y;
};

class Polygon {
public:
	Polygon() { mIsCircle = true; }
	void AddVertex(Point vertex); // Adds a vertex (position relative to polygon's position)
	bool IsInside(Point point);
	// SETTERS
	void SetPosition(int x, int y) { mPosX = x; mPosY = y; }
	void SetRadius(int x) { radius = x; }
	// GETTERS
	int GetSides() { return mSides; }
	int GetPosX() { return mPosX; }
	int GetPosY() { return mPosY; }
	bool IsCircle() { return mIsCircle; }
	Point* GetVertex(int i) { return &vertices[i]; }
private:
	std::vector<Point>vertices; // Vertices vector
	bool mIsCircle;
	int radius;
	int mPosX, mPosY; // Top left coordinate
	int mSides; // Number of sides
};

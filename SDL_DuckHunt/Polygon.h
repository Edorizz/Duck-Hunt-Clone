#pragma once
#include <vector>

struct Point {
	int x, y;
};

class Polygon {
public:
	Polygon() { mIsCircle = true; }
	void AddVertex(Point vertex); // Adds a vertex (position relative to polygon's position)
	bool IsInside(Point point); // Checks if a point(x, y) is inside the polygon
	// GETTERS
	int GetSides() { return mSides; }
	int GetPosX() { return mPosX; }
	int GetPosY() { return mPosY; }
	int GetRadius() { return radius; }
	bool IsCircle() { return mIsCircle; }
	Point* GetVertex(int i) { return &vertices[i]; }
	// SETTERS
	void SetPosition(int x, int y) { mPosX = x; mPosY = y; }
	void SetPosX(int x) { mPosX = x; }
	void UpdatePosX(int vel) { mPosX += vel; }
	void SetPosY(int y) { mPosY = y; }
	void UpdatePosY(int vel) { mPosY += vel; }
	void SetD2CenterX(int x) { d2CenterX = x; }
	void SetD2CenterY(int y) { d2CenterY = y; }
	void SetRadius(int x) { radius = x; mIsCircle = true; }
private:
	std::vector<Point>vertices; // The polygon's vertices
	bool mIsCircle; // Is this a circle?...
	int radius; // ...If it is, this is the radius, else, it's just 0
	int mPosX, mPosY; // Top left coordinate
	int d2CenterX, d2CenterY; // Distance to center (For circles)
	int mSides; // Number of sides
};

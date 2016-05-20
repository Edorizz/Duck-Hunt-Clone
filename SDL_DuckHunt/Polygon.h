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
	void SetRadius(int x) { radius = x; mIsCircle = true; }
private:
	std::vector<Point>vertices; // Vertices vector
	bool mIsCircle;
	int radius;
	int mPosX, mPosY; // Top left coordinate
	int mSides; // Number of sides
};

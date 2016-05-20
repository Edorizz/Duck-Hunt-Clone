#pragma once
#include "Polygon.h"
#include "LTexture.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

class Object {
public:
	Object(LTexture *texture, int renderingType);
	void Update();
	void Render(); // Renders the object at the polygon's position
	void Render(int x, int y); // Renders the object at a given position
	// GETTERS
	Polygon* GetPolygon() { return &mPolygon; }
	LTexture* GetTexture() { return mTexture; }
	int GetVelX() { return velX; }
	int GetVelY() { return velY; }
	// SETTERS
	void SetVel(int x, int y) { velX = x; velY = y; }
	void SetVelX(int x) { velX = x; }
	void SetVelY(int y) { velY = y; }
private:
	Polygon mPolygon;
	LTexture *mTexture;
	int velX, velY;
	int mRenderingType;
};
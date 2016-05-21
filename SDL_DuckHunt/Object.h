#pragma once
#include "Polygon.h"
#include "LTexture.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

class Object {
public:
	Object(LTexture *texture, int renderingType);
	void Update(); // Updates position, if ball is out of bounds it bounces back
	bool HandleEvent(SDL_Event *e); // Returns true if we interacted with the ball
	void CalculateAngle(); // Calculates angle, duhh...
	void Render(); // Renders the object at the polygon's position
	void Render(int x, int y); // Renders the object at a given position
	// GETTERS
	Polygon* GetPolygon() { return &mPolygon; }
	LTexture* GetTexture() { return mTexture; }
	int GetVelX() { return mVelX; }
	int GetVelY() { return mVelY; }
	// SETTERS
	void SetVel(int x, int y) { mVelX = x; mVelY = y; }
	void SetVelX(int x) { mVelX = x; }
	void SetVelY(int y) { mVelY = y; }
private:
	Polygon mPolygon;
	LTexture *mTexture;
	int mVelX, mVelY;
	double mAngle;
	int mRenderingType;
};
#pragma once
#include <vector>
#include "Polygon.h"
#include "LTexture.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int FLOOR_HEIGHT;

enum States {
	FLYING, SHOT, FALLING, FLEEING
};

enum BirdTextures {
	_BIRD, _BIRD_2, _BIRD_3, _BIRD_SHOT, _BIRD_FALLING, _BIRD_FALLING_2
};

class Object {
public:
	Object(std::vector<LTexture*> textures, int renderingType, double multiplier = 1);
	void Update(); // Updates position, if ball is out of bounds it bounces back
	void UpdateFlying();
	void UpdateShot();
	void UpdateFalling();
	void HandleEvent(SDL_Event *e); // Returns true if we interacted with the ball
	void CalculateAngle(); // Calculates angle, duhh...
	void Render(); // Renders the object at the polygon's position
	void Render(int x, int y); // Renders the object at a given position
	// GETTERS
	Polygon* GetPolygon() { return &mPolygon; }
	LTexture* GetTexture() { return mTexture; }
	int GetVelX() { return mVelX; }
	int GetVelY() { return mVelY; }
	int GetState() { return mState; }
	bool IsDead() { return mIsDead; }
	// SETTERS
	void SetVel(int x, int y) { mVelX = x; mVelY = y; }
	void SetVelX(int x) { mVelX = x; }
	void SetVelY(int y) { mVelY = y; }
private:
	Polygon mPolygon;
	std::vector<LTexture*> mTextures;
	LTexture *mTexture;
	int mVelX, mVelY;
	int mFallingVel = 5;
	int mRenderingType;
	int timer = 3;
	int mShotTimer = 20;
	bool mSwap = false;
	bool mIsDead = false;
	double mScalingMultiplier;
	double mAngle = 99999;
	int mAngleDiff = 0;
	States mState = FLYING;
	SDL_RendererFlip mFlipType = SDL_FLIP_NONE;
};
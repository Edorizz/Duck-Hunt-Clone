#pragma once
#include "Polygon.h"
#include "LTexture.h"

class Object {
public:
	Object(LTexture *texture, int renderingType);
	void Render(); // Renders the object at the polygon's position
	void Render(int x, int y); // Renders the object at a given position
	// GETTERS
	LTexture* GetTexture() { return mTexture; }
	Polygon* GetPolygon() { return &mPolygon; }
private:
	Polygon mPolygon;
	LTexture *mTexture;
	int mRenderingType;
};
#pragma once
#include "Polygon.h"
#include "LTexture.h"

class Object {
public:
	Object(LTexture *texture, int renderingType);
	Polygon mPolygon;
private:
	int mRenderingType;
	LTexture *mTexture;
};
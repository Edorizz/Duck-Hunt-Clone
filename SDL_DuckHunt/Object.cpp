#include "Object.h"

Object::Object(LTexture *texure, int renderingType) {
	mRenderingType = renderingType;
	mTexture = texure;
}

void Object::Render() {
	mTexture->Render(mPolygon.GetPosX(), mPolygon.GetPosY());
}

void Object::Render(int x, int y) {
	mTexture->Render(x, y);
}
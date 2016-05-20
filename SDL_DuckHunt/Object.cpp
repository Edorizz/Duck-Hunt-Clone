#include "Object.h"

Object::Object(LTexture *texure, int renderingType) {
	mRenderingType = renderingType;
	mTexture = texure;
	velX = 0;
	velY = 0;
}

void Object::Update() {
	if (GetPolygon()->GetPosX() < 0 || GetPolygon()->GetPosX() + GetTexture()->GetWidth() > SCREEN_WIDTH) {
		SetVelX(GetVelX() * -1);
	}
	if (GetPolygon()->GetPosY() < 0 || GetPolygon()->GetPosY() + GetTexture()->GetHeight() > SCREEN_HEIGHT) {
		SetVelY(GetVelY() * -1);
	}
	mPolygon.UpdatePosX(velX);
	mPolygon.UpdatePosY(velY);
}

void Object::Render() {
	mTexture->Render(mPolygon.GetPosX(), mPolygon.GetPosY());
}

void Object::Render(int x, int y) {
	mTexture->Render(x, y);
}
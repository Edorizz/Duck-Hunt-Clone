#include "Object.h"
#include <cmath>

Object::Object(LTexture *texure, int renderingType) {
	mRenderingType = renderingType;
	mTexture = texure;
	mVelX = 0;
	mVelY = 0;
	mPolygon.SetD2CenterX(texure->GetWidth() / 2);
	mPolygon.SetD2CenterY(texure->GetHeight() / 2);
}

void Object::Update() {
	if (GetPolygon()->GetPosX() < 0 || GetPolygon()->GetPosX() + GetTexture()->GetWidth() > SCREEN_WIDTH) {
		SetVelX(GetVelX() * -1);
		CalculateAngle();
	}
	if (GetPolygon()->GetPosY() < 0 || GetPolygon()->GetPosY() + GetTexture()->GetHeight() > SCREEN_HEIGHT) {
		SetVelY(GetVelY() * -1);
		CalculateAngle();
	}
	mPolygon.UpdatePosX(mVelX);
	mPolygon.UpdatePosY(mVelY);
}

bool Object::HandleEvent(SDL_Event *e) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (GetPolygon()->IsInside(Point{ mouseX, mouseY }) && e->type == SDL_MOUSEBUTTONDOWN) {
		return true;
	}
	return false;
}

void Object::CalculateAngle() {
	mAngle = atan2(mVelY, mVelX) * 57.29;
}

void Object::Render() {
	mTexture->Render(mPolygon.GetPosX(), mPolygon.GetPosY(), mAngle);
}

void Object::Render(int x, int y) {
	mTexture->Render(x, y, mAngle);
}
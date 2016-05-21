#include "Object.h"
#include <cmath>
#include <algorithm>

Object::Object(std::vector<LTexture*> textures, int renderingType, double multiplier) {
	mTextures = textures;
	mRenderingType = renderingType;
	mTexture = textures[0];
	mVelX = 0;
	mVelY = 0;
	mPolygon.SetD2CenterX(textures[0]->GetWidth() / 2);
	mPolygon.SetD2CenterY(textures[0]->GetHeight() / 2);
	mScalingMultiplier = multiplier;
}

void Object::Update() {
	if (timer <= 0) {
		if (mSwap) {
			std::swap(mTextures[1], mTextures[2]);
		}
		std::swap(mTextures[0], mTextures[1]);
		mTexture = mTextures[0];
		timer = 3;
		mSwap = !mSwap;
	}
	if (mAngle == 99999) {
		CalculateAngle();
	}
	if (GetPolygon()->GetPosX() < 0 || GetPolygon()->GetPosX() + GetTexture()->GetWidth() * mScalingMultiplier > SCREEN_WIDTH) {
		SetVelX(GetVelX() * -1);
		CalculateAngle();
	}
	if (GetPolygon()->GetPosY() < 0 || GetPolygon()->GetPosY() + GetTexture()->GetHeight() * mScalingMultiplier > FLOOR_HEIGHT) {
		SetVelY(GetVelY() * -1);
		CalculateAngle();
	}
	mPolygon.UpdatePosX(mVelX);
	mPolygon.UpdatePosY(mVelY);
	timer--;
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
	mAngle = atan2((float)mVelY, (float)abs(mVelX)) * 57.29;
	if (mVelX < 0) {
		mFlipType = SDL_FLIP_HORIZONTAL;
		mAngleDiff = mAngle * 2;
	} else {
		mFlipType = SDL_FLIP_NONE;
		mAngleDiff = 0;
	}
}

void Object::Render() {
	mTexture->Render(mPolygon.GetPosX(), mPolygon.GetPosY(), mAngle - mAngleDiff, mScalingMultiplier, mFlipType);
}

void Object::Render(int x, int y) {
	mTexture->Render(x, y, mAngle, mScalingMultiplier, mFlipType);
}
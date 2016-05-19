#include "Object.h"

Object::Object(LTexture *texure, int renderingType) {
	mRenderingType = renderingType;
	mTexture = texure;
}
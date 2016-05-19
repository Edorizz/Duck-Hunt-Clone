#include "LTexture.h"
#include <iostream>

extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	Free();
}

bool LTexture::LoadFromFile(std::string path, bool colorKey) {
	Free();
	bool success = true;
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		std::cout << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
	} else {
		if (colorKey) {
			SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		}
		texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (texture == NULL) {
			std::cout << "Unable to create texture from " << path << "! SDL_Error: " << SDL_GetError() << std::endl;
		} else {
			mWidth = surface->w;
			mHeight = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	mTexture = texture;
	return mTexture != NULL;
}

bool LTexture::LoadFromText(std::string text, SDL_Color color) {
	Free();
	bool success = true;
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if (surface == NULL) {
		std::cout << "Unable to render text " << text << "! TTF Error: " << TTF_GetError() << std::endl;
	} else {
		texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (texture == NULL) {
			std::cout << "Unable to create texture from " << text << "! SDL_Error: " << SDL_GetError() << std::endl;
		} else {
			mWidth = surface->w;
			mHeight = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	mTexture = texture;
	return mTexture != NULL;
}

void LTexture::Free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::Render(int x, int y, SDL_Rect *blockRect) {
	if (blockRect == NULL) {
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };
		SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
	} else {
		SDL_Rect pos;
		pos.x = x;
		pos.y = y;
		pos.w = blockRect->w;
		pos.h = blockRect->h;
		SDL_RenderCopy(gRenderer, mTexture, blockRect, &pos);
	}
}
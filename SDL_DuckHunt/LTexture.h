#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class LTexture {
public:
	LTexture(); // Initializes variables
	~LTexture(); // Deallocates memory
	bool LoadFromFile(std::string path, bool colorKey = false); // Loads image at specified path, can color key cyan
	bool LoadFromText(std::string text, SDL_Color color); // loads image out of a text string
	void Free(); // Deallocates texture
	void Render(int x, int y, SDL_Rect *blockRect = nullptr); // Renders texture at given point
	// GETTERS
	int GetWidth() { return  mWidth; };
	int GetHeight() { return mHeight; };

private:
	// The actual hardware texture
	SDL_Texture* mTexture;
	// Image dimensions
	int mWidth;
	int mHeight;
};
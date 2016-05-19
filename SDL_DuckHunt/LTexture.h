#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class LTexture {
public:
	//Initializes variables
	LTexture();
	//Deallocates memory
	~LTexture();
	//Loads image at specified path
	bool LoadFromFile(std::string path, bool colorKey = false);
	bool LoadFromText(std::string text, SDL_Color color);
	//Deallocates texture
	void Free();
	//Renders texture at given point
	void Render(int x, int y, SDL_Rect *blockRect = nullptr);
	//Gets image dimensions
	int GetWidth() { return  mWidth; };
	int GetHeight() { return mHeight; };

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};
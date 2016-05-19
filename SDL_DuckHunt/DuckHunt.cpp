#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "LTexture.h"
#include "Object.h"

enum Textures {
	DOT, TRIANGLE, MAX_TEXTURES
};

// Screen dimension
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

// Globals
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
LTexture gTextures[MAX_TEXTURES];
TTF_Font *gFont = nullptr;
SDL_Event e;

// Prototypes
bool Init();
bool LoadMedia();
void BallBounceLoop();

int main(int args, char *argv[]) {
	if (Init() && LoadMedia()) {
		bool isGameDone = false;
		Object triangle(&gTextures[TRIANGLE], 1);
		triangle.mPolygon.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		triangle.mPolygon.AddVertex(Point{ 0, gTextures[TRIANGLE].GetHeight() });
		triangle.mPolygon.AddVertex(Point{ gTextures[TRIANGLE].GetWidth() / 2, 0 });
		triangle.mPolygon.AddVertex(Point{ gTextures[TRIANGLE].GetWidth(), gTextures[TRIANGLE].GetHeight() });
		int mouseX, mouseY;
		while (!isGameDone) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					isGameDone = true;
				} 
			}
			SDL_GetMouseState(&mouseX, &mouseY);
			std::cout << mouseX << ", " << mouseY << std::endl;
			if (triangle.mPolygon.IsInside(Point{ mouseX, mouseY })) {
				std::cout << "Inside!\n";
			}
			SDL_RenderClear(gRenderer);
			gTextures[TRIANGLE].Render(triangle.mPolygon.GetPosX(), triangle.mPolygon.GetPosY());
			SDL_RenderPresent(gRenderer);
		}
	}

	return 0;
}

void BallBounceLoop() {
	bool isGameDone = false;
	int mouseX, mouseY;
	int dotX = SCREEN_WIDTH / 2, dotY = SCREEN_HEIGHT / 2;
	int dotVelX = 1, dotVelY = 1;
	int speed = 1;
	while (!isGameDone) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				isGameDone = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_d:
					speed++;
					break;
				case SDLK_a:
					speed--;
					break;
				case SDLK_SPACE:
					dotVelX = (rand() % 5 + 1);
					dotVelY = (rand() % 5 + 1);
				default:
					break;
				}
			}
		}
		dotX += dotVelX * speed;
		dotY += dotVelY * speed;

		if (dotX + gTextures[DOT].GetWidth() >= SCREEN_WIDTH) {
			dotVelX = -1;
		} else if (dotX <= 0) {
			dotVelX = 1;
		}
		if (dotY + gTextures[DOT].GetHeight() >= SCREEN_HEIGHT) {
			dotVelY = -1;
		} else if (dotY <= 0) {
			dotVelY = 1;
		}
		SDL_GetMouseState(&mouseX, &mouseY);
		int deltaX = mouseX - (dotX + gTextures[DOT].GetWidth() / 2);
		int deltaY = mouseY - (dotY + gTextures[DOT].GetHeight() / 2);
		if ((deltaX * deltaX + deltaY * deltaY) <= gTextures[DOT].GetWidth() / 2 * gTextures[DOT].GetWidth() / 2) {
			std::cout << "Inside circle!\n";
		}
		SDL_RenderClear(gRenderer);
		gTextures[DOT].Render(dotX, dotY);
		SDL_RenderPresent(gRenderer);
	}
}

bool Init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not initialize SDL! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
		gWindow = SDL_CreateWindow("Let's hunt some ducks!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr) {
			std::cout << "Could not create window! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr) {
				std::cout << "Could not create renderer! SDL_Error: " << SDL_GetError() << std::endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "Could not initialize SDL_IMG! IMG_Error: " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

bool LoadMedia() {
	bool success = true;
	if (!gTextures[DOT].LoadFromFile("Resources/dot.png", true)) {
		std::cout << "Could not load image!\n";
		success = false;
	}
	if (!gTextures[TRIANGLE].LoadFromFile("Resources/triangle.png")) {
		std::cout << "Could not load image!\n";
		success = false;
	}
	return success;
}

void Close() {
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	for (int i = 0; i < MAX_TEXTURES; i++) {
		gTextures[i].Free();
	}
}
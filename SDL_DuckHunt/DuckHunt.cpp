#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "LTexture.h"
#include "Object.h"

enum Textures {
	DOT, TRIANGLE, MAX_TEXTURES
};

// Screen dimension
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

int maxVel = 8;

// Globals
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
LTexture gTextures[MAX_TEXTURES];
TTF_Font *gFont = nullptr;
SDL_Event e;

std::mt19937 randomGenerator(time(0));
std::uniform_int_distribution<int> random(-maxVel,maxVel);

// Objects
Object *ball = nullptr;

// Prototypes
bool Init();
bool LoadMedia();
Object* NewBall();
int RandomPositiveOrNegative(int x);
void SetRandomVelocity(Object* obj);

int main(int args, char *argv[]) {
	if (Init() && LoadMedia()) {
		bool isGameDone = false;
		ball = NewBall();
		while (!isGameDone) {
			while (SDL_PollEvent(&e)) { // The main event handler
				if (e.type == SDL_QUIT) {
					isGameDone = true;
				}
				if (ball->HandleEvent(&e)) {
					delete ball;
					ball = NewBall();
				}
			}
			// Updating
			ball->Update();
			// Rendering
			SDL_RenderClear(gRenderer);
			ball->Render();
			SDL_RenderPresent(gRenderer);
		}
	}

	return 0;
}


// OBJECT HELPER FUNCTIONS
Object* NewBall() {
	Object *obj = new Object(&gTextures[DOT], 1);
	obj->GetPolygon()->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	obj->GetPolygon()->SetRadius(obj->GetTexture()->GetWidth());
	SetRandomVelocity(obj);
	return obj;
}


void SetRandomVelocity(Object* obj) {
	int velX = random(randomGenerator);
	int velY = RandomPositiveOrNegative(maxVel - abs(velX));
	obj->SetVel(velX, velY);
}


// MATH FUNCTIONS
int RandomPositiveOrNegative(int x) {
	int rand = random(randomGenerator);
	if (rand < 0) {
		return x * -1;
	}
	return x;
}


// GAME HELPER FUNCTIONS



// MAIN FUNCTIONS
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
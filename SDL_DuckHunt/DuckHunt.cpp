#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <random>
#include <ctime>
#include "LTexture.h"
#include "Object.h"

typedef std::vector<Object*> Objects;

enum Textures {
	DOT, TRIANGLE, BIRD, BIRD_2, BACKGROUND, MAX_TEXTURES
};

// Screen dimension
const int SCREEN_HEIGHT = 560;
const int SCREEN_WIDTH = 640;
const int FLOOR_HEIGHT = 478;

// Globals
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
LTexture gTextures[MAX_TEXTURES];
std::vector<LTexture*> gBirdTextures(2);
TTF_Font *gFont = nullptr;
SDL_Event e;

// Game variables
int maxVel = 10;
int ballCount = 2;

// Random Number Generation
std::mt19937 randomGenerator(time(0));
std::uniform_int_distribution<int> randomVelocity(-maxVel + 1, maxVel - 1);
std::uniform_int_distribution<int> randomPosX(0 + 100, SCREEN_WIDTH - 100);
std::uniform_int_distribution<int> random(0, 100);

// Objects
Objects balls;

// Prototypes
bool Init();
bool LoadMedia();
Object* NewBall();
int RandomPositiveOrNegative(int x);
void SetRandomVelocity(Object* obj);
void HandleObjects(Objects &objects, SDL_Event *e);
void CreateObjects(Objects &objects);
void UpdateObjects(Objects &objects);
void RenderAll();

int main(int args, char *argv[]) {
	if (Init() && LoadMedia()) {
		bool isGameDone = false;
		CreateObjects(balls);
		while (!isGameDone) {
			if (balls.size() == 0) {
				CreateObjects(balls);
			}
			while (SDL_PollEvent(&e)) { // The main event handler
				if (e.type == SDL_QUIT) {
					isGameDone = true;
				}
				HandleObjects(balls, &e);
			}
			UpdateObjects(balls);
			RenderAll();
		}
	}
	return 0;
}


// OBJECT HELPER FUNCTIONS
Object* NewBall() {
	Object *obj = new Object(gBirdTextures, 1, 2.4);
	obj->GetPolygon()->SetRadius(obj->GetTexture()->GetWidth() * 1.5);
	obj->GetPolygon()->SetPosition(randomPosX(randomGenerator), FLOOR_HEIGHT - obj->GetPolygon()->GetRadius() * 1.5);
	SetRandomVelocity(obj);
	return obj;
}


void SetRandomVelocity(Object* obj) {
	int velX = randomVelocity(randomGenerator);
	int velY = RandomPositiveOrNegative(maxVel - abs(velX));
	obj->SetVel(velX, velY);
}


// MATH FUNCTIONS
int RandomPositiveOrNegative(int x) {
	int rand = randomVelocity(randomGenerator);
	if (rand < 0) {
		return x * -1;
	}
	return x;
}


// GAME HELPER FUNCTIONS
void CreateObjects(Objects &objects) {
	for (int i = 0; i < ballCount; i++) {
		objects.push_back(NewBall());
	}
}

void HandleObjects(Objects &objects, SDL_Event *e) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->HandleEvent(e)) {
			delete objects[i];
			objects[i] = objects[objects.size() - 1];
			objects.pop_back();
		}
	}
}

void UpdateObjects(Objects &objects) {
	for (int i = 0; i < objects.size(); i++) {
		int rand = random(randomGenerator);
		if (rand < 7 && SCREEN_HEIGHT - objects[i]->GetPolygon()->GetPosX() > 100
			&& SCREEN_HEIGHT - objects[i]->GetPolygon()->GetPosX() < 500
			&& FLOOR_HEIGHT - objects[i]->GetPolygon()->GetPosY() > 100
			&& FLOOR_HEIGHT - objects[i]->GetPolygon()->GetPosY() < 300) {
			SetRandomVelocity(objects[i]);
			objects[i]->CalculateAngle();
		}
		objects[i]->Update();
	}
}

void RenderAll() {
	SDL_RenderClear(gRenderer);
	for (int i = 0; i < balls.size(); i++) {
		balls[i]->Render();
	}
	gTextures[BACKGROUND].Render(0, 0, 0, 2.5, SDL_FLIP_NONE);
	SDL_RenderPresent(gRenderer);
}


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
				SDL_SetRenderDrawColor(gRenderer, 0x64, 0xB0, 0xFF, 0xFF);

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
	if (!gTextures[BIRD].LoadFromFile("Resources/bird.png", true)) {
		std::cout << "Could not load image!\n";
		success = false;
	}
	if (!gTextures[BIRD_2].LoadFromFile("Resources/bird2.png", true)) {
		std::cout << "Could not load image!\n";
		success = false;
	}
	if (!gTextures[BACKGROUND].LoadFromFile("Resources/background.png", true)) {
		std::cout << "Could not load image!\n";
		success = false;
	}
	gBirdTextures[0] = &gTextures[BIRD];
	gBirdTextures[1] = &gTextures[BIRD_2];
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
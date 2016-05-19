#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "LTexture.h"

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

struct Point {
	int x, y;
};

class Polygon {
public:
	void AddVertex(Point vertex) { // Adds a vertex (position relative to polygon's position)
		vertex.x += mPosX;
		vertex.y += mPosY;
		vertices.push_back(vertex);
		mSides = vertices.size();
	}
	// SETTERS
	void SetPosition(int x, int y) { mPosX = x; mPosY = y; }
	// GETTERS
	int GetSides() { return mSides; }
	int GetPosX() { return mPosX; }
	int GetPosY() { return mPosY; }
	Point* GetVertex(int i) { return &vertices[i]; }
private:
	std::vector<Point>vertices; // Vertices vector
	int mPosX, mPosY; // Top left coordinate
	int mSides; // Number of sides
};

int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy) {
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

bool IsInside(Polygon polygon, Point point) {
	int i, j;
	bool c = false;
	for (i = 0, j = polygon.GetSides() - 1; i < polygon.GetSides(); j = i++) {
		if (((polygon.GetVertex(i)->y > point.y) != (polygon.GetVertex(j)->y > point.y)) &&
			(point.x < (polygon.GetVertex(j)->x - polygon.GetVertex(i)->x) * (point.y - polygon.GetVertex(i)->y) / (polygon.GetVertex(j)->y - polygon.GetVertex(i)->y) + polygon.GetVertex(i)->x)) {
			c = !c;
		}
	}
	return c;
}

int main(int args, char *argv[]) {
	if (Init() && LoadMedia()) {
		bool isGameDone = false;
		Polygon trianglePoly;
		trianglePoly.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		trianglePoly.AddVertex(Point{ 0, gTextures[TRIANGLE].GetHeight() });
		trianglePoly.AddVertex(Point{ gTextures[TRIANGLE].GetWidth() / 2, 0 });
		trianglePoly.AddVertex(Point{ gTextures[TRIANGLE].GetWidth(), gTextures[TRIANGLE].GetHeight() });
		int mouseX, mouseY;
		while (!isGameDone) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					isGameDone = true;
				} 
			}
			SDL_GetMouseState(&mouseX, &mouseY);
			std::cout << mouseX << ", " << mouseY << std::endl;
			if (IsInside(trianglePoly, Point{ mouseX, mouseY })) {
				std::cout << "Inside!\n";
			}
			SDL_RenderClear(gRenderer);
			gTextures[TRIANGLE].Render(trianglePoly.GetPosX(), trianglePoly.GetPosY());
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
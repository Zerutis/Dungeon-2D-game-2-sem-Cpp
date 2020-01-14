#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include "tile.h"
#include "mapp.h"

const int size = 50;

// Klasë realizuojanti tekstûros funkcionalumà
class Image {
	SDL_Texture* swordsman;
	SDL_Texture* archer;
	SDL_Texture* mage;
	SDL_Texture* bullet;
	SDL_Texture* super_bullet;
	SDL_Texture* cannon;
	SDL_Texture* cannon_shot;
	SDL_Texture* apple;
	SDL_Texture* orange;
	SDL_Texture* sword;
	SDL_Texture* shield;
	SDL_Texture* gameOver;
	Tile* map;

public:
	Image();
	~Image();

	void draw(SDL_Renderer* ren, SDL_Texture* texture, SDL_Rect* srect, SDL_Rect* drect) const;
	static SDL_Texture* loadBMP(SDL_Renderer* ren, const std::string& filename);

	friend class Game;
};

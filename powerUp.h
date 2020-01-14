#pragma once
#include <SDL.h>
#include "coordinate.h"

class PowerUp {
	SDL_Texture* icon;
	Coordinate<int> my;
public:
	PowerUp() : icon(nullptr), my() { }
	PowerUp(const int x, const int y, SDL_Texture* pic) : icon(pic), my(x, y) { }
	~PowerUp() { SDL_DestroyTexture(icon); }

	const Coordinate<int> getPos() const { return { my.xpos, my.ypos }; }

	void draw(SDL_Renderer* ren) {
		SDL_Rect power = { my.xpos, my.ypos, 8, 8 };
		SDL_RenderCopy(ren, icon, NULL, &power);
	}
};
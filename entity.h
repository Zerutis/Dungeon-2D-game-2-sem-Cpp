#pragma once
#include "mapp.h"
#include <SDL.h>
#include <vector>

class Entity {
	std::vector<Entity> entities;
public:
	virtual void draw(SDL_Renderer* ren) const = 0;
	virtual void move(const Mapp& collide) { };
};
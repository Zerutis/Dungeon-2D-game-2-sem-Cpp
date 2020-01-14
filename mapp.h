#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include "image.h"
#include "InputFiles.h"
#include "coordinate.h"
#include "vec2D.h"

const int TILE_SIZE = 32;
const int Map_Tile_Width = 25;
const int Map_Tile_Height = 20;


//--------------------------------------------------------------
class Mapp{
	std::vector<Tile> tileMap;
	SDL_Texture* tileset;
	int **map;
	Coordinate<int> start, finish;

public:
	Mapp();
	Mapp(const std::string mapfile);
	Mapp(const Mapp& oldOne);
	~Mapp();
	void loadMap(const std::string filename, SDL_Renderer* ren);
	void drawMap(SDL_Renderer* ren) const;

	const int getStartX() const { return start.xpos; }
	const int getStartY() const { return start.ypos; }
	const int getFinishX() const { return finish.xpos; }
	const int getFinishY() const { return finish.ypos; }


	bool moveable (const int x, const int y) const;

	bool isFinish (const vec2D<int> ) const;
	
};

//--------------------------------------------------------------


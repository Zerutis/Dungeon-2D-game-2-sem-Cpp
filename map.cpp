#include "map.h"
#include <iostream>
#include <fstream>

using namespace std;

void Tile::setSource(int x, int y, int h, int w) {
	src_x = x;
	src_y = y;
	src_h = h;
	src_w = w;
}

void Tile::setDest(int x, int y, int h, int w) {
	dest_x = x;
	dest_y = y;
	dest_h = h;
	dest_w = w;
}


void Tile::setImage(const std::string filename, SDL_Renderer* ren) {
	tex = Image::loadBMP(ren, filename);
}

//----------------------------------------------------------------------
Map::Map() : tileset(nullptr) {
	map = new int*[Map_Tile_Height];
	for (int i = 0; i < Map_Tile_Height; i++) {
		map[i] = new int[Map_Tile_Width];
	}
	ifstream fd("level1.txt");
	for (int i = 0; i < Map_Tile_Height; i++) {
		for (int j = 0; j < Map_Tile_Width; j++) {
			fd >> map[i][j];
			fd.ignore();
		}
	}
	fd >> start.xpos >> start.ypos;
	fd >> finish.xpos >> finish.ypos;
	fd.close();
}

Map::Map(const std::string mapfile) : tileset(nullptr) {
	map = new int* [Map_Tile_Height];
	for (int i = 0; i < Map_Tile_Height; i++) {
		map[i] = new int[Map_Tile_Width];
	}
	ifstream fd(mapfile);
	for (int i = 0; i < Map_Tile_Height; i++) {
		for (int j = 0; j < Map_Tile_Width; j++) {
			fd >> map[i][j];
			fd.ignore();
		}
	}
	fd >> start.xpos >> start.ypos;
	fd >> finish.xpos >> finish.ypos;
	fd.close();
}

Map::Map(const Map& oldOne) : tileset(nullptr) {
	map = new int* [Map_Tile_Height];
	for (int i = 0; i < Map_Tile_Height; i++) {
		map[i] = new int[Map_Tile_Width];
	}
	ifstream fd("level2.txt");
	for (int i = 0; i < Map_Tile_Height; i++) {
		for (int j = 0; j < Map_Tile_Width; j++) {
			fd >> map[i][j];
			fd.ignore();
		}
	}
	fd >> start.xpos >> start.ypos;
	fd >> finish.xpos >> finish.ypos;
	fd.close();
}

Map::~Map() {
	for(int i=0; i<Map_Tile_Height; ++i)
		delete[] map[i];
	delete map;
}

void Map::loadMap(const std::string filename, SDL_Renderer* ren) {
	int current, row = Map_Tile_Height, collum = Map_Tile_Width;
	ifstream fd(filename);
	if (!fd.is_open()) {
		return;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < collum; j++) {
			if (fd.eof()) {
				return;
			}
			fd >> current;
			fd.ignore();
			Tile temp;
			temp.setImage("tileset.bmp", ren);
			temp.setSource((current - 1) * 32, 0, 32, 32);
			temp.setDest((j * TILE_SIZE), (i * TILE_SIZE), TILE_SIZE, TILE_SIZE);
			tileMap.push_back(temp);
		}
	}
	fd.close();
}

void Map::drawMap(SDL_Renderer* ren) const {
	for (size_t i = 0; i < tileMap.size(); i++) {
		SDL_Rect dest = tileMap[i].getDest();
		SDL_Rect src = tileMap[i].getSource();

		SDL_RenderCopyEx(ren, tileMap[i].getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
	}
}


bool Map::moveable (const int x, const int y) const  {
	int i = (y+16) / 32; // þemyn
	int j = (x+16) / 32; // deðinën
	//cout << map[i][j] << endl;
	int tileX = j * 32, tileY = i * 32;
	if (map[i][j] == 26) {
		return true;
	} else if (map[i][j] == 27) {
		if(x < tileX + 5)
			return true;
	} else if (map[i][j] == 21) {
		if(y > tileY - 10)
	 		return true;
	} else if (map[i][j] == 25) {
		if(x > tileX + 5)
			return true;
	} else if (map[i][j] == 31) {
		if(y > tileY - 16)
			return true;
	} else if (map[i][j] == 20) {
		if (x > tileX + 5 && y > tileY - 16)
			return true;
	}

	if (map[i][j] == 30) {
		if (x > tileX + 8 && y > tileY - 16)
			return true;
	} else if (map[i][j] == 29) {
		if ((x < tileX + 8) && (y > tileY-10))
			return true;
	} else if (map[i][j] == 24) {
		if ((x < tileX + 8) || (y > tileY +10))
			return true;
	} else if (map[i][j] == 28) {
		if ((x > tileX - 5) || (y > tileY + 10))
			return true;
	} else if (map[i][j] == 23) {
		if ((x > tileX - 5) || (y > tileY - 10))
			return true;
	}
	return false;
}

bool Map::isFinish(const vec2D<int> hero_pos) const {
	if ((hero_pos.my_x == finish.xpos) && ((hero_pos.my_y > finish.ypos) || (hero_pos.my_y < finish.ypos + 32.0))) {
		return true;
	}
	else
		return false;
}
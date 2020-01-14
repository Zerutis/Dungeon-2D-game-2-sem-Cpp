#pragma once
#include <SDL.h>
#include <string>

class Tile {
private:
	int src_x, src_y, src_h, src_w;
	int dest_x, dest_y, dest_h, dest_w;
	SDL_Texture* tex;


public:
	Tile() : tex(NULL), src_x(0), src_y(0), src_h(0), src_w(0), dest_x(0), dest_y(0), dest_h(0), dest_w(0) { }
	SDL_Rect getDest() const { return { dest_x, dest_y, dest_h, dest_w }; }
	SDL_Rect getSource() const { return { src_x, src_y, src_h, src_w }; }
	SDL_Texture* getTex() const { return tex; }

	void setSource(int x, int y, int h, int w);
	void setDest(int x, int y, int h, int w);
	void setImage(const std::string filename, SDL_Renderer* ren);

};
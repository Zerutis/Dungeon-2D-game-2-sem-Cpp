#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "entity.h"
#include "bullet.h"


class Objects {
protected:
	int m_x, m_y, m_h, m_w;
public:
	Objects() : m_x(0), m_y(0), m_h(0), m_w(0) { }
	Objects(int x, int y, int h, int w) : m_x(x), m_y(y), m_h(h), m_w(w) {}
	virtual ~Objects() {}
};

class Item : public Objects {
	SDL_Texture* icon;
public:
	Item() : Objects(), icon(nullptr) { }
	Item(int x, int y, int h, int w, SDL_Texture* pic) : Objects(x, y, h, w), icon(pic) { }

	const int getX() const { return m_x; }
	const int getY() const { return m_y; }
	~Item() { SDL_DestroyTexture(icon); }

	void draw(SDL_Renderer* ren);
};

class Artillery : public Objects {
	int direction; // 8-up, 2-down, 4-left, 6-right, 5-everywhere, 0-don`t shoot

public:
	static int timer;
	std::vector<Bullet> shot;
	Artillery() : Objects(), direction(0) { }
	Artillery(int x, int y, int h, int w, int side) : Objects(x, y, h, w), direction(side) { }
	~Artillery() { }

	SDL_Rect getCannonDest() const { return { m_x, m_y, m_h, m_w }; }
	size_t getShotSize() const { return shot.size(); }

	void draw(SDL_Renderer* ren, SDL_Texture* tex) const ;

	void shoot();
	void shotMove (int direction, int i);
	void collision();

	friend class Game;
};


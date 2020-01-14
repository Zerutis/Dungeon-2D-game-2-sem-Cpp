#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <array>
#include "vec2D.h"
#include "entity.h"
#include "coordinate.h"
#include "object.h"
#include "bullet.h"

const int range_limit = 40;

// herojaus galimybës
class Hero : public Entity{
protected:
	vec2D<int> my_coordinate; // þaidëjo koordinatës
	vec2D<int> my_size; // þaidëjo dydis
	int move_speed; // þaidëjo judëjimo greitis
	int b_speed; // kulkos greitis
	int range;
	std::array<Item*, 2> backpack;
	std::vector<Bullet>shotsDest; // kulkos tikslas
	std::vector<Bullet>shots; // kulkø vieta
	std::vector<double> angleX, angleY;
	Bullet mouse;

	SDL_Texture* icon;
	bool upDown = true;

public:
	Hero();
	Hero(int x, int y, int m_speed, int b_sp, int range, SDL_Texture* pic);
	Hero(const Hero& another);
	virtual ~Hero();

	virtual void attack() =0;

	void bullet_move(int i, const Mapp& collide);
	void bullet_delete(int i);

	void move(const Mapp& collide) override { }; // þaidëjo judejimas w,s,a,d klavisais
	void AImove(const Mapp& collide) { }; // mobø judëjimas

	const bool collision (int x, int y, const Mapp& collide) const ;

	template<typename T1, typename T2>
	bool collisionObject(T1& _coordinate, T2& e_coordinate) {
		if (((_coordinate.xpos + 16 > e_coordinate.xpos) && (_coordinate.xpos + 16 < (e_coordinate.xpos + 32))) &&
			((_coordinate.ypos + 16 > e_coordinate.ypos) && (_coordinate.ypos + 16 < (e_coordinate.ypos + 32)))) {
			return true;
		}
		return false;
	}

	
	bool powerup(const Coordinate<int> pos, const std::string type);
	const bool pick(const Bullet mouse_place, const vec2D<int> item_place) const;

	void draw(SDL_Renderer* ren) const override;
	

	friend class Game;
};

//-------------------------------------
class Swordsman : public Hero {
	int item;
public:
	Swordsman() 
		: Hero(32, 32, 1, 8,10, nullptr), item(0) {}
	Swordsman(int xpos, int ypos, int m_speed, int b_speed, int rang, SDL_Texture* pic)
		: Hero(xpos, ypos, m_speed, b_speed,rang, pic), item(0) { }
	~Swordsman() { }

	int incrementItemSize() { 
		if(item < 1)
			return item++; 
		return false;
	}
	int decrementItemSize() { return item--; }
	const int getItemSize() const { return item; }
	void move(const Mapp& collide) override;
	bool enemy_hit (const Bullet& shot, const vec2D<int>& e_coordinate);
	bool weapon();

	void attack() override;
};

class Mage : public Hero {
public:
	Mage()
		: Hero(32, 32, 3, 12,10, nullptr) { }
	Mage(int xpos, int ypos, int m_speed, int b_speed, int rang, SDL_Texture* pic)
		: Hero(xpos, ypos, m_speed, b_speed, rang, pic) { }
	~Mage() { }

	void move(const Mapp& collide) override;
	bool enemy_hit(const Bullet& shot, const vec2D<int>& e_coordinate);
	void attack() override;
};

class Archer : public Hero {
public:
	Archer()
		: Hero(32, 32, 5, 16,10, nullptr) { }
	Archer(int xpos, int ypos, int m_speed, int b_speed, int rang, SDL_Texture* pic)
		: Hero(xpos, ypos, m_speed, b_speed, rang, pic) { }
	~Archer() { }

	void move(const Mapp& collide) override;
	bool enemy_hit(const Bullet& shot, const vec2D<int>& e_coordinate);
	void attack() override;
};

class Enemy : public Hero {
public:
	Enemy()
		: Hero(32, 32, 5, 16,10, nullptr) { }
	Enemy(int xpos, int ypos, int m_speed, int b_speed, int rang, SDL_Texture* pic)
		: Hero(xpos, ypos, m_speed, b_speed, rang, pic) { }
	~Enemy() { }


	void attack() override;
	void move(const Mapp& collide) override;
};
//-------------------------------------


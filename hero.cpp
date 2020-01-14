#include "hero.h"
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

Hero::Hero() : my_size(32, 32), my_coordinate(64, 64), move_speed(4), b_speed(12), range(0), icon(nullptr), backpack{ } { }

Hero::Hero(int x, int y, int m_speed, int b_sp, int rang, SDL_Texture* pic)
	: my_size(32,32), my_coordinate(x,y), move_speed(m_speed), b_speed(b_sp), range(rang), icon(pic), backpack{ } { }

Hero::Hero(const Hero& another) :
	my_size(another.my_size.xpos, another.my_size.ypos),
	my_coordinate(another.my_coordinate.xpos, another.my_coordinate.ypos),
	move_speed(another.move_speed),
	b_speed(another.b_speed),
	range(another.range),
	icon(another.icon),
	backpack(another.backpack),
	mouse(another.mouse) { }

Hero::~Hero() { SDL_DestroyTexture(icon); }

const bool Hero::collision(int x, int y, const Mapp &collide) const {
	if (!collide.moveable(x, y)) {
		return false;
	}
	return true;
}

void Hero::bullet_move(int i, const Mapp& collide) {
	if ((shots[i].ypos == shotsDest[i].ypos) && (shots[i].xpos == shotsDest[i].xpos)) {
		bullet_delete(i);
		return;
	}

	if (!collision(shots[i].xpos, shots[i].ypos, collide)) {
		bullet_delete(i);
		return;
	}
	shots[i].range++;
	if (shots[i].range % range == 0) {
		bullet_delete(i);
		return;
	}

	if ((shots[i].xpos < shotsDest[i].xpos) && (shots[i].ypos < shotsDest[i].ypos)){
		shots[i].xpos += (int)(angleX[i] * b_speed);
		shots[i].ypos += (int)(angleY[i] * b_speed);
	}
	else if ((shots[i].xpos < shotsDest[i].xpos) && (shots[i].ypos > shotsDest[i].ypos)) {
		shots[i].xpos += (int)(angleX[i] * b_speed);
		shots[i].ypos -= (int)(angleY[i] * b_speed);
	}
	else if ((shots[i].xpos > shotsDest[i].xpos) && (shots[i].ypos < shotsDest[i].ypos)) {
		shots[i].xpos -= (int)(angleX[i] * b_speed);
		shots[i].ypos += (int)(angleY[i] * b_speed);
	}
	else if ((shots[i].xpos > shotsDest[i].xpos) && (shots[i].ypos > shotsDest[i].ypos)) {
		shots[i].xpos -= (int)(angleX[i] * b_speed);
		shots[i].ypos -= (int)(angleY[i] * b_speed);
	}
}

void Hero::bullet_delete(int i) {
	shots.erase(shots.begin()+i);
	shotsDest.erase(shotsDest.begin()+i);
}

bool Hero::powerup(const Coordinate<int> pos, const std::string type) {
	if (collisionObject(my_coordinate,pos) && (range < range_limit)) {
		if (type == "apple")
			range += 5;
		else if (type == "orange") {
			my_size.xpos += 16;
			my_size.ypos += 16;
		}
		return true;
	}
	return false;
}

const bool Hero::pick(const Bullet mouse_place, const vec2D<int> item_place) const {
	if ((mouse_place.xpos > item_place.xpos && mouse_place.xpos < item_place.xpos + 24) &&
		(mouse_place.ypos > item_place.ypos && mouse_place.ypos < item_place.ypos + 24)) {
		return true;
	}
	return false;
}

void Hero::draw(SDL_Renderer* ren) const {
	SDL_Rect rect = { my_coordinate.xpos, my_coordinate.ypos, my_size.xpos, my_size.ypos };
	SDL_RenderCopy(ren, icon, NULL, &rect);
}

// Riteris
void Swordsman::attack() {
	Bullet b;
	Bullet mous;
	SDL_GetMouseState(&mous.xpos, &mous.ypos);
	b.xpos = my_coordinate.xpos + 24;
	b.ypos = my_coordinate.ypos + 24;
	double ypos = (double)mous.ypos - b.ypos;
	double xpos = (double)mous.xpos - b.xpos;
	double hypotenuse = sqrt(pow((ypos), 2) + pow((xpos), 2));
	b.range = 0;

	
	angleX.push_back(cos(xpos / hypotenuse));
	angleY.push_back(sin(ypos / hypotenuse));
	shots.push_back(b);
	shotsDest.push_back(mous);
}

void Swordsman::move(const Mapp& collide) {
	const auto* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_D]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += LEFT;
		}
	}
	else if (state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP;
		}
	}
	else if (state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN;
		}
	}
}

bool Swordsman::enemy_hit(const Bullet& shot, const vec2D<int>& e) {
	if (((shot.xpos > e.xpos) && (shot.xpos < e.xpos+32)) &&
		((shot.ypos > e.ypos) && (shot.ypos < e.ypos+32))) {
		return true;
	}
	return false;
}

bool Swordsman::weapon() {
	if (backpack[item] == nullptr) {
		return false;
	}
	for (auto it = backpack.begin(); it != backpack.end(); ++it) {
		if(range < range_limit)
			range += 10;
	}
	return true;
}


//Lankininkas
void Archer::attack() {
	Bullet b;
	Bullet mouse;
	SDL_GetMouseState(&mouse.xpos, &mouse.ypos);
	b.xpos = my_coordinate.xpos + 24;
	b.ypos = my_coordinate.ypos + 24;
	double ypos = (double)mouse.ypos - b.ypos;
	double xpos = (double)mouse.xpos - b.xpos;
	double hypotenuse = sqrt(pow((ypos), 2) + pow((xpos), 2));
	b.range = 0;

	angleX.push_back(cos(xpos / hypotenuse));
	angleY.push_back(sin(ypos / hypotenuse));
	shots.push_back(b);
	shotsDest.push_back(mouse);
}

void Archer::move(const Mapp& collide) {
	const auto* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_D]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += LEFT;
		}
	}
	else if (state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP;
		}
	}
	else if (state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN;
		}
	}
}

bool Archer::enemy_hit(const Bullet& shot, const vec2D<int>& e) {
	if (((shot.xpos > e.xpos) && (shot.xpos < e.xpos + 32)) &&
		((shot.ypos > e.ypos) && (shot.ypos < e.ypos + 32))) {
		return true;
	}
	return false;
}

//Burtininkas
void Mage::attack() {
	Bullet b;
	Bullet mouse;
	SDL_GetMouseState(&mouse.xpos, &mouse.ypos);
	b.xpos = my_coordinate.xpos + 24;
	b.ypos = my_coordinate.ypos + 24;
	double ypos = (double)mouse.ypos - b.ypos;
	double xpos = (double)mouse.xpos - b.xpos;
	double hypotenuse = sqrt(pow((ypos), 2) + pow((xpos), 2));
	b.range = 0;

	angleX.push_back(cos(xpos / hypotenuse));
	angleY.push_back(sin(ypos / hypotenuse));
	shots.push_back(b);
	shotsDest.push_back(mouse);
}

void Mage::move(const Mapp& collide) {
	const auto* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN + LEFT;
		}
	}
	else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP + RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_D]) {
		if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += RIGHT;
		}
	}
	else if (state[SDL_SCANCODE_A]) {
		if (collision(my_coordinate.xpos - move_speed, my_coordinate.ypos, collide)) {
			my_coordinate += LEFT;
		}
	}
	else if (state[SDL_SCANCODE_W]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos - move_speed, collide)) {
			my_coordinate += UP;
		}
	}
	else if (state[SDL_SCANCODE_S]) {
		if (collision(my_coordinate.xpos, my_coordinate.ypos + move_speed, collide)) {
			my_coordinate += DOWN;
		}
	}
}

bool Mage::enemy_hit(const Bullet& shot, const vec2D<int>& e) {
	if (((shot.xpos > e.xpos) && (shot.xpos < e.xpos + 32)) &&
		((shot.ypos > e.ypos) && (shot.ypos < e.ypos + 32))) {
		return true;
	}
	return false;
}

//Mobs - prieðai
void Enemy::attack() {
	Bullet b;
	Bullet mouse;
	SDL_GetMouseState(&mouse.xpos, &mouse.ypos);
	b.xpos = my_coordinate.xpos + 24;
	b.ypos = my_coordinate.ypos + 24;
	double ypos = (double)mouse.ypos - b.ypos;
	double xpos = (double)mouse.xpos - b.xpos;
	double hypotenuse = sqrt(pow((ypos), 2) + pow((xpos), 2));
	b.range = 0;

	angleX.push_back(cos(xpos / hypotenuse));
	angleY.push_back(sin(ypos / hypotenuse));
	shots.push_back(b);
	shotsDest.push_back(mouse);
}

void Enemy::move(const Mapp& collide) {
	if (upDown) {
		if (!collision(my_coordinate.xpos - move_speed, my_coordinate.ypos, collide))
			upDown = false;
		my_coordinate += eLEFT;
	}
	else if (collision(my_coordinate.xpos + move_speed, my_coordinate.ypos, collide)) {
		my_coordinate += eRIGHT;
	}
	else {
		upDown = true;
	}

}
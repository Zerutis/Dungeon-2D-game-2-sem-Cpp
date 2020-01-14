#include "object.h"
#include <iostream>


void Item::draw(SDL_Renderer* ren) {
	SDL_Rect ob_rect = { m_x, m_y, m_h, m_w };
	SDL_RenderCopy(ren, icon, NULL, &ob_rect);
}
int Artillery::timer = 0;

void Artillery::shoot() {
	
	if (timer == 0 || timer % 39 == 0) {
		Bullet cannon{ m_x + 16, m_y + 16 };
		shot.push_back(cannon);
	}
	timer++;
}

void Artillery::shotMove(int direction, int i) {
	switch (direction) {
		case 0:
			std::cout << "reloading" << std::endl;
			break;
		case 2:
			shot[i].ypos += 5;
			break;
		case 4:
			shot[i].xpos -=5;
			break;
		case 6:
			shot[i].xpos += 5;
			break;
		case 8:
			shot[i].ypos -= 5;
			break;
		default:
			break;
		}
}
void Artillery::draw(SDL_Renderer* ren, SDL_Texture* tex) const {
	SDL_Rect ob_rect = getCannonDest();
	SDL_RenderCopy(ren, tex, NULL, &ob_rect);
}


void Artillery::collision() {
	auto it = remove_if(shot.begin(), shot.end(),
		[](Bullet shot) { return ((shot.xpos > 790) || (shot.xpos < 10) || (shot.ypos > 630) || (shot.ypos < 10)); });
	if (it != shot.end())
		shot.erase(it,shot.end());
}

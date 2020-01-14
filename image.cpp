#include "image.h"

using namespace std;

Image::Image() :
	swordsman(nullptr), archer(nullptr), mage(nullptr), bullet(nullptr), super_bullet(nullptr),
	cannon(nullptr), cannon_shot(nullptr), gameOver(nullptr), map(nullptr), orange(nullptr),
	apple(nullptr), sword(nullptr), shield(nullptr) {}
	
Image::~Image() {
	SDL_DestroyTexture(swordsman);
	SDL_DestroyTexture(archer);
	SDL_DestroyTexture(mage);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(super_bullet);
	SDL_DestroyTexture(cannon);
	SDL_DestroyTexture(cannon_shot);  
	SDL_DestroyTexture(apple);
	SDL_DestroyTexture(orange);
	SDL_DestroyTexture(sword);
	SDL_DestroyTexture(shield);
	SDL_DestroyTexture(gameOver);
}

void Image::draw(SDL_Renderer* ren, SDL_Texture* texture, SDL_Rect* srect, SDL_Rect* drect) const {
	SDL_RenderCopy(ren, texture, srect, drect);
}

SDL_Texture* Image::loadBMP(SDL_Renderer* ren, const std::string& filename) {
	SDL_Surface* bmp = SDL_LoadBMP(filename.c_str());
	
	if (bmp) {
		SDL_Texture* temp = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		return temp;
	}
	return NULL;
}
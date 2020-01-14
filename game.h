#pragma once
#include <SDL.h>
#include "image.h"
#include "entity.h"
#include "hero.h"
#include "object.h"
#include "InputFiles.h"
#include <iostream>
#include <string>
#include <map>
#include "powerUp.h"

// Klasë þaidimo operacijoms vykdyti
class Game {           
	SDL_Window* win; 	// Sukuriamas tuðèià langas
	SDL_Renderer* ren; 	// Sukuriamas "pieðëjas", kuris susietas su prieð tai sukurtu langu
	bool isRunning;	// Ar þaidimas dar veikia
	std::vector<Entity*> person;
	std::map<std::string, PowerUp*> power;
	std::array<Item*, 2> item;
	Mapp *grid;
	std::vector<Artillery*> artillery;
	Image* picture;
	Input input;
	static int deaths;

public:
	Game() : win(nullptr), ren(nullptr), isRunning(false), picture(new Image()), grid(new Mapp()), item{} { }
	~Game();

	void init();
	void initImages();
	void initObjects();
	void update();
	const void render() const ;
	void control();
	void changeLevels();
	void freeStorage();

	static int getDeath() { return deaths; }
	static void countDeath() { deaths +=1; }

	bool victory();
	const bool defeat() const;
	const bool restart() const;
	bool running() { return isRunning; }
};



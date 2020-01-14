#include "game.h"
#include "exceptions.h"
#include <algorithm>

using namespace std;

Game::~Game() {
	delete grid;
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

 void Game::init() {
	// Inicijuojamas video rëþimas
	 try {
		 if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			 win = SDL_CreateWindow("Dungeon", 100, 100, 800, 640, SDL_WINDOW_SHOWN);
			 if (win == nullptr) {
				 SDL_Quit();
				 throw init_window_failure("Dungeon");
			 }

			 ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			 if (ren == nullptr) {
				 SDL_DestroyWindow(win);
				 SDL_Quit();
				 throw init_renderer_failure("SDL_CreateRenderer");
			 }
			 isRunning = true;
		 }
	 } 
	 catch (const exception & e) {
		 isRunning = false;
		 cerr << "exception: " << e.what() << endl;
	 }
	 catch (...) {
		 isRunning = false;
	 }
}

 void Game::initImages() {
	 // uþkraunami paveikslëliai
	 try {
		 picture->swordsman = Image::loadBMP(ren, "swordsman.bmp");
		 if (picture->swordsman == nullptr) { throw load_image_failure("swordsman.bmp"); }

		 picture->archer = Image::loadBMP(ren, "archer.bmp");
		 if (picture->archer == nullptr) { throw load_image_failure("archer.bmp"); }

		 picture->mage = Image::loadBMP(ren, "mage.bmp");
		 if (picture->mage == nullptr) { throw load_image_failure("mage.bmp"); }

		 picture->bullet = Image::loadBMP(ren, "bullet.bmp");
		 if (picture->bullet == nullptr) { throw load_image_failure("bullet.bmp"); }

		 picture->super_bullet = Image::loadBMP(ren, "super_bullet.bmp");
		 if (picture->super_bullet == nullptr) { throw load_image_failure("super_bullet.bmp"); }

		 picture->cannon = Image::loadBMP(ren, "cannon.bmp");
		 if (picture->cannon == nullptr) { throw load_image_failure("cannon.bmp"); }

		 picture->cannon_shot = Image::loadBMP(ren, "cannon_shot.bmp");
		 if (picture->cannon_shot == nullptr) { throw load_image_failure("cannon_shot.bmp"); }

		 picture->apple = Image::loadBMP(ren, "apple.bmp");
		 if (picture->apple == nullptr) { throw load_image_failure("apple.bmp"); }

		 picture->orange = Image::loadBMP(ren, "orange.bmp");
		 if (picture->orange == nullptr) { throw load_image_failure("orange.bmp"); }

		 picture->sword = Image::loadBMP(ren, "sword.bmp");
		 if (picture->sword == nullptr) { throw load_image_failure("sword.bmp"); }

		 picture->shield = Image::loadBMP(ren, "shield.bmp");
		 if (picture->shield == nullptr) { throw load_image_failure("shield.bmp"); }

		 picture->gameOver = Image::loadBMP(ren, "game_over.bmp");
		 if (picture->gameOver == nullptr) { throw load_image_failure("game_over.bmp"); }
	 }
	 catch (const exception & e) {
		 isRunning = false;
		 cerr << "exception: " << e.what() << endl;
	 }
	 catch (...) {
		 isRunning = false;
	 }
 }

 void Game::initObjects() {

	 person.push_back(new Swordsman(32, 32, 4, 4,10, picture->swordsman));
	 grid->loadMap(input.mapINFO[input.lvl], ren);

	 power.insert(pair<string, PowerUp*>("apple", new PowerUp(200, 200, picture->apple)));
	 power.insert(pair<string, PowerUp*>("orange", new PowerUp(250, 420, picture->orange)));

	 item[0] = new Item(240, 140, 24, 24, picture->sword);
	 item[1] = new Item(115, 460, 24, 24, picture->shield);

	 string type;
	 int xpos, ypos, move_s, bullet_s, range;
	 int witdh, height, dir;
	 int n, m;
	 ifstream fd(input.objectsINFO[input.lvl]);
	 try{
		 if (fd.is_open() == false) {
			 throw open_file_failure("game_over.bmp"); }
		 // uþkraunami prieðai
		 fd >> n;
		 for (int i = 0; i < n; i++) {
			 fd >> type >> xpos >> ypos >> move_s >> bullet_s >> range;
			 if (type == "swordsman") {
				 person.push_back(new Enemy(xpos, ypos, move_s, bullet_s, range, picture->swordsman));
			 }
			 else if (type == "mage") {
				 person.push_back(new Enemy(xpos, ypos, move_s, bullet_s, range, picture->mage));
			 }
			 else if (type == "archer") {
				 person.push_back(new Enemy(xpos, ypos, move_s, bullet_s, range, picture->archer));
			 }
			 else { throw undefined_character_type(type); }
		 }
		 // uþkraunami pabûklai
		 fd >> m;
		 for (int i = 0; i < m; i++) {
			 fd >> xpos >> ypos >> height >> witdh >> dir;
			 artillery.push_back(new Artillery(xpos, ypos, height, witdh, dir));
		 }
	 }
	 catch (const exception & e) {
		 isRunning = false;
		 cerr << "exception: " << e.what() << endl;
	 }
	 catch (...) {
		 isRunning = false;
	 }

	 input.lvl++;
	 fd.close();
 }

 void Game::control() {
	 SDL_Event event;
	 SDL_PollEvent(&event);
	 const auto state = SDL_GetKeyboardState(NULL);
	 switch (event.type) { //Þaidimo iðëjimo klaviðai
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (state[SDL_SCANCODE_Q]) {
				isRunning = false;
			}
			break;
		default:
			break;
	 }
}

 int Game::deaths = 0;

 void Game::update() {
	render();
	control();

	//artillery move
	for_each(artillery.begin(), artillery.end(), [](Artillery* a) { a->shoot(); } );
	for (size_t i = 0; i < artillery.size(); i++) {
		for (size_t j = 0; j < artillery[i]->shot.size(); j++) {
			artillery[i]->shotMove(4, j);
		}
	}
	for_each(artillery.begin(), artillery.end(), [](Artillery * a) { a->collision(); }); //trinimas
	//person move

	for (const auto& type : person) { type->move(*grid); }

	auto hero = dynamic_cast<Swordsman*>(person[0]);
	//attack - kairiuoju pelës mygtuku
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		hero->attack();
	}
	//powerUp
	for (auto it = power.begin(); it != power.end(); ++it) {
		
		if (hero->powerup(it->second->getPos(),it->first)) {
			power.erase(it);
			break;
		}
	}
	//pick - deðiniuoju pelës mygtuku
	if (SDL_GetMouseState(&hero->mouse.xpos, &hero->mouse.ypos) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		for (const auto& i : item) {
			vec2D<int> thing = {i->getX(), i->getY()};
			if (hero->pick(hero->mouse, thing)) {
				hero->backpack[hero->getItemSize()] = i;
				hero->incrementItemSize();
			}
		}
	}
	if (hero->getItemSize() == 1) {
		hero->decrementItemSize();
		hero->weapon();
	}


	//bullet move
	for (size_t i = 0; i < hero->shots.size(); i++) {
		hero->bullet_move(i, *grid);
	}
	//enemy kill
	for (size_t i = 0; i < hero->shots.size(); i++) {
		for (auto it = person.begin() + 1; it != person.end(); ++it) {
			auto e = dynamic_cast<Enemy*>(*it);
			if (hero->enemy_hit(hero->shots[i], e->my_coordinate)) {
				person.erase(it);
				break;
			}
		}
	}

	if (defeat()) {
		SDL_RenderClear(ren);
		picture->draw(ren, picture->gameOver, NULL, NULL);
		SDL_RenderPresent(ren);
		if (!restart())
			isRunning = false;
		else
			hero->my_coordinate = { grid->getStartX(), grid->getStartY() };  // nustato pradines þaidëjo koordinates
	}

	if (victory()) { changeLevels(); }

	SDL_Delay(1000 / 60);
}

const void Game::render() const {
	SDL_RenderClear(ren); // Iðvalom ekranà

	grid->drawMap(ren); // nupieðia þemëlapá

	// nupieðia patrankas ir jø kulkas
	for (const auto& cannon : artillery) {
		cannon->draw(ren, picture->cannon);
		for (size_t j=0; j < cannon->shot.size(); ++j) {
			SDL_Rect bullet = { cannon->shot[j].xpos,cannon->shot[j].ypos, 8,8 };
			picture->draw(ren, picture->cannon_shot, NULL, &bullet);
		}
	}

	for (const auto& i : item) { i->draw(ren); } // nupieðia daiktus (pvz.: kardas)

	for (auto it = power.begin(); it != power.end(); ++it) { it->second->draw(ren); } // iðpieðia powerup`us

	for (const auto& i : person) { i->draw(ren); } // iðpieðia veikëjus

	// nupieðia þaidëjo kulkas
	auto hero = dynamic_cast<Swordsman*>(person[0]);
	for (size_t i = 0; i < hero->shots.size(); i++) {
		Bullet b = hero->shots[i];
		SDL_Rect bullet = { b.xpos, b.ypos, 4, 4 };
		picture->draw(ren, picture->bullet, NULL, &bullet);
	}

	SDL_RenderPresent(ren); // Atnaujinam vaizdà ekrane
}

bool Game::victory() {
	if (count_if(person.begin(), person.end(), [](Entity * e) { return dynamic_cast<Enemy*>(e); }) != 0) {
		return false;
	}

	auto hero = dynamic_cast<Swordsman*>(person[0]);
	if (grid->isFinish(hero->my_coordinate)) {
		if (input.lvl == 2) {
			isRunning = false;
			return false;
		}
		hero->my_coordinate = { grid->getStartX(), grid->getStartY() };
		return true;
	}
	return false;
}

void Game::changeLevels() {
	freeStorage();
	grid = new Mapp(*grid);
	initObjects();
}

void Game::freeStorage() {
	power.clear();
	artillery.clear();
	person.clear();
}

const bool Game::defeat() const{
	auto itHero = dynamic_cast<Swordsman*>(person[0]);
	for (auto it = person.begin() + 1; it != person.end(); ++it) {
		auto enemy = dynamic_cast<Enemy*>(*it);
		if (itHero->collisionObject(itHero->my_coordinate, enemy->my_coordinate)) {
			Game::countDeath();
			cout << Game::getDeath() << endl;
			return true;
		}
	}
	for (const auto& a : artillery) {
		for (const auto& s :a->shot)
		if(itHero->collisionObject(itHero->my_coordinate, s)) {
			Game::countDeath();
			cout << Game::getDeath() << endl;
			return true;
		}
	}
	return false;
}

const bool Game::restart() const {
	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_r:
					return true;
				}
				case SDLK_q:
					return false;
			}
		}
	}
}
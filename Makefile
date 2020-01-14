CXXFLAGS = -Isdl2/32bit/include -std=c++0x
LXXFLAGS = -Lsdl2/32bit/lib -lmingw32 -lSDL2main -lSDL2

dungeon: main.o game.o image.o hero.o
	g++ main.o game.o image.o -o dungeon $(LXXFLAGS)

main.o: main.cpp 
	g++ main.cpp -c $(CXXFLAGS)

game.o: game.cpp game.h
	g++ game.cpp -c $(CXXFLAGS)

image.o: image.cpp image.h
	g++ image.cpp -c $(CXXFLAGS)

hero.o: hero.cpp hero.h
	g++ hero.cpp -c $(CXXFLAGS)
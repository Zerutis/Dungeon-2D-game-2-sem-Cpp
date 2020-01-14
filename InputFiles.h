#pragma once
#include <fstream>
#include <string>
#include <vector>

class Input {
public:
	std::vector<std::string> mapINFO;
	std::vector<std::string> objectsINFO;
	int lvl = 0;

	Input();
};

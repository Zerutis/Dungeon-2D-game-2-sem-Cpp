#include "InputFiles.h"
#include <iostream>

Input::Input() {
	std::ifstream fd("fileNames.txt");
	std::string map, object;
	for (int i = 0; i < 2 ; i++) {
		fd >> map >> object;
		mapINFO.push_back(map);
		objectsINFO.push_back(object);
	}

}

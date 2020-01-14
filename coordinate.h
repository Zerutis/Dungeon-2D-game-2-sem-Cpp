#pragma once

template <typename T>
class Coordinate {
public:
	T xpos, ypos;
	Coordinate() : xpos(0), ypos(0) { }
	Coordinate(const T& x, const T& y) : xpos(x), ypos(y) { }
};
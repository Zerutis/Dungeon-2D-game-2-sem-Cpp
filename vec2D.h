#pragma once
#include <iostream>
#include <vector>
#include <array>


template <typename T>
class vec2D {
public:
	T xpos, ypos;
	vec2D() : xpos(0), ypos(0) { }
	vec2D(const T& x, const T& y) : xpos(x), ypos(y) { }

	const T& x() const { return xpos; }
	const T& y() const { return ypos; }

	vec2D operator +(const vec2D& other) const { return vec2D(xpos + other.xpos, ypos + other.ypos); }
	vec2D operator +(const T& other) const { return vec2D(xpos + other, ypos + other); }
	vec2D operator *(const T & scale) const { return vec2D(xpos * scale, ypos * scale); }

	vec2D& operator += (const vec2D & other) {
		xpos += other.xpos;
		ypos += other.ypos;
		return *this;
	}

	vec2D& operator *= (const T & scale) {
		xpos *= scale;
		ypos *= scale;
		return *this;
	}

	bool operator == (const vec2D & other) const {
		return xpos == other.xpos && ypos == other.ypos;
	}

	bool operator != (const vec2D & other) const {
		return xpos != other.xpos || ypos != other.ypos;
	}
	
	bool operator >(const vec2D & other) const {
		return xpos > other.xpos || ypos > other.ypos;
	}
	bool operator < (const vec2D& other) const {
		return xpos < other.xpos || ypos < other.ypos;
	}

	static vec2D LEFT() { return vec2D(-1, 0); }
};

const vec2D<int> LEFT(-4, 0);
const vec2D<int> RIGHT(4, 0);
const vec2D<int> UP(0, -4);
const vec2D<int> DOWN(0, 4);

const vec2D<int> eLEFT(-2, 0);
const vec2D<int> eRIGHT(2, 0);
const vec2D<int> eUP(0, -2);
const vec2D<int> eDOWN(0, 2);


#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

using namespace sf;

class Block {
public:
	RectangleShape *shape;
	bool del = false;
	Config config;

	Block(float x, float y);

	~Block();
};


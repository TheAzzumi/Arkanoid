#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

using namespace sf;

class Racket {
public:
	Vector2f speed;
	RectangleShape *shape;
	Config config;

	Racket(float x, float y);

	~Racket();

	void update();
};


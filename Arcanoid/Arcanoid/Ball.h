#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

using namespace sf;

class Ball {
public:
	CircleShape *shape;
	Config config;
	Vector2f speed = { -config.speedBall, -config.speedBall };
	bool flag = false;

	Ball(float x, float y);

	~Ball();

	void update();
};

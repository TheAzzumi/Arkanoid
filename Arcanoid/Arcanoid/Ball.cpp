#include "Ball.h"

Ball::Ball(float x, float y) {
	shape = new CircleShape();
	shape->setPosition(x, y);
	shape->setRadius(5);
	shape->setFillColor(Color::Green);
	shape->setOrigin(10, 10);
}

Ball::~Ball() {
	delete shape;
}

void Ball::update() {
	shape->move(speed);

	// отскоки мячика от стен

	if ((shape->getPosition().x - shape->getRadius()) < 0) {
		speed.x = config.speedBall;
	}
	if ((shape->getPosition().x + shape->getRadius()) > 495) {
		speed.x = -config.speedBall;
	}
	if ((shape->getPosition().y - shape->getRadius()) < 0) {
		speed.y = config.speedBall;
	}
	if ((shape->getPosition().y + shape->getRadius()) > 450) {
		//speed.y = -config.speedBall; // для тестирования
		flag = true; // для игры
	}
}

#include "Racket.h"

Racket::Racket(float x, float y) {
	shape = new RectangleShape();
	shape->setPosition(x, y);
	shape->setSize(Vector2f(config.widthRacket, config.heigthRacket));
	shape->setFillColor(Color::Red);
	shape->setOrigin(config.widthRacket / 2, config.heigthRacket / 2);
}

Racket::~Racket() {
	delete shape;
}

void Racket::update() {
	shape->move(speed);

	// проверка положения ракетки, чтобы она не уходила за экран
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && (shape->getPosition().x - (config.widthRacket / 2 + 5)) > 0) {
		speed.x = -config.racketSpeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && (shape->getPosition().x + (config.widthRacket / 2 + 5)) < 495) {
		speed.x = config.racketSpeed;
	}
	else {
		speed.x = 0;
	}
}

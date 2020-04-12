#include "Block.h"

Block::Block(float x, float y) {
	shape = new RectangleShape();
	shape->setSize(Vector2f(config.widthBlock, config.heightBlock));
	shape->setPosition(x, y);
	shape->setFillColor(Color::Blue);
	shape->setOrigin(config.widthBlock / 2, config.heightBlock / 2);
}

Block::~Block() {
	delete shape;
}

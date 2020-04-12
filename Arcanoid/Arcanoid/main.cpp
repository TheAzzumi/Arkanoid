#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


float speedBall = 8;
float racketSpeed = 10;
float widthBlock = 45;
float heightBlock = 15;
float widthRacket = 90;
float heigthRacket = 10;

class Block {
public:
	RectangleShape *shape;
	bool del = false;
	Block(float x, float y) {
		shape = new RectangleShape();
		shape->setSize(Vector2f(widthBlock, heightBlock));
		shape->setPosition(x, y);
		shape->setFillColor(Color::Blue);
		shape->setOrigin(widthBlock / 2, heightBlock / 2);
	}

	~Block() {
		delete shape;
	}
};

class Ball {
public:
	CircleShape *shape;
	Vector2f speed = { -speedBall, -speedBall };
	bool flag = false;

	Ball(float x, float y) {
		shape = new CircleShape();
		shape->setPosition(x, y);
		shape->setRadius(5);
		shape->setFillColor(Color::Green);
		shape->setOrigin(10, 10);
	}

	~Ball() {
		delete shape;
	}

	void update() {
		shape->move(speed);

		// ������� ������ �� ����

		if ((shape->getPosition().x - shape->getRadius()) < 0) {
			speed.x = speedBall;
		}
		if ((shape->getPosition().x + shape->getRadius()) > 495) {
			speed.x = -speedBall;
		}
		if ((shape->getPosition().y - shape->getRadius()) < 0) {
			speed.y = speedBall;
		}
		if ((shape->getPosition().y + shape->getRadius()) > 450) {
			speed.y = -speedBall; // ��� ������������
			//flag = true; // ��� ����
		}
	}
};

class Racket{
public:
	Vector2f speed;
	RectangleShape *shape;

	Racket(float x, float y) {
		shape = new RectangleShape();
		shape->setPosition(x, y);
		shape->setSize(Vector2f(widthRacket, heigthRacket));
		shape->setFillColor(Color::Red);
		shape->setOrigin(widthRacket / 2, heigthRacket / 2);
	}

	~Racket() {
		delete shape;
	}

	void update() {
		shape->move(speed);

		// �������� ��������� �������, ����� ��� �� ������� �� �����
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && (shape->getPosition().x - (widthRacket / 2 + 5)) > 0) {
			speed.x = -racketSpeed;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && (shape->getPosition().x + (widthRacket / 2 + 5)) < 495) {
			speed.x = racketSpeed;
		}
		else {
			speed.x = 0;
		}
	}
};

int main() {
	Ball ball(247.5, 425);
	Racket racket(247.5, 430);
	vector<Block*> block;

	bool flagKey = false;
	float diffX;
	float diffY;
	int kolBlocks;
	int level = 1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if (j % 2 == 0) {
				if (level == 1) block.push_back(new Block((i + 0.5) * (widthBlock + 5), (j + 0.5) * (heightBlock + 5))); // ������������ ��������� ��� ������
			}
		}
	}

	kolBlocks = block.size();

	RenderWindow window(VideoMode(495, 450), "Arkanoid | Level 1", Style::Close);
	window.setFramerateLimit(60);
	
	while (window.isOpen())
	{
		window.clear(Color::Black);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) flagKey = true;

		if (flagKey) ball.update();
		racket.update();

		// ������� ������ �� �������
		// ��������� ��������� 
		if ((racket.shape->getPosition().x + (racket.shape->getSize().x / 2.f)) >= (ball.shape->getPosition().x - (ball.shape->getRadius())) // ��.���� ������� � �.���� ���
			&& (racket.shape->getPosition().x - (racket.shape->getSize().x / 2.f)) <= (ball.shape->getPosition().x + (ball.shape->getRadius())) // �.���� ������� � ��.���� ���
			&& (racket.shape->getPosition().y - (racket.shape->getSize().y / 2.f)) <= (ball.shape->getPosition().y + (ball.shape->getRadius()))) { // �.���� ���� � �.���� ���
			
			ball.speed.y = -speedBall;
			if (ball.shape->getPosition().x < racket.shape->getPosition().x) { // ����������� ������� ������� ������ �� �������
				ball.speed.x = -speedBall;
			}
			else {
				ball.speed.x = speedBall;
			}
		}
		window.draw(*ball.shape);
		if (ball.flag) { // ��� ����� ����
			//window.close();
			//cout << "You lose!" << endl;
		}
		window.draw(*racket.shape);
		
		// ��������� ������
		for (int i = 0; i < block.size(); i++) {
			if (!block[i]->del) window.draw(*block[i]->shape);
		}
		
		// ������� ������ �� ������
		for (int i = 0; i < block.size(); i++) {
			// ��������� ��������� 
			if ((block[i]->shape->getPosition().x + (block[i]->shape->getSize().x / 2.f)) >= (ball.shape->getPosition().x - (ball.shape->getRadius())) // ��.���� ���� � �.���� ���
				&& (block[i]->shape->getPosition().x - (block[i]->shape->getSize().x / 2.f)) <= (ball.shape->getPosition().x + (ball.shape->getRadius())) // �.���� ���� � ��.���� ���
				&& (block[i]->shape->getPosition().y + (block[i]->shape->getSize().y / 2.f)) >= (ball.shape->getPosition().y - (ball.shape->getRadius())) // �.���� ���� � �.���� ���
				&& (block[i]->shape->getPosition().y - (block[i]->shape->getSize().y / 2.f)) <= (ball.shape->getPosition().y + (ball.shape->getRadius())) // �.���� ���� � �.���� ���
				&& !block[i]->del) { // ������ �� ����
				block[i]->del = true;
				kolBlocks--;

				// ����������� ������� ������������ �� X � ������ ������� ���������
				if (abs((ball.shape->getPosition().x + (ball.shape->getRadius())) - (block[i]->shape->getPosition().x - (block[i]->shape->getSize().x / 2))) // ��������� �����
					< abs((block[i]->shape->getPosition().x + (block[i]->shape->getSize().x / 2)) - (ball.shape->getPosition().x - (ball.shape->getRadius())))) { // ��������� ������
					diffX = abs((ball.shape->getPosition().x + (ball.shape->getRadius())) - (block[i]->shape->getPosition().x - (block[i]->shape->getSize().x / 2)));
				}
				else {
					diffX = abs((block[i]->shape->getPosition().x + (block[i]->shape->getSize().x / 2)) - (ball.shape->getPosition().x - (ball.shape->getRadius())));
				}
				 
				// ����������� ������� ������������ �� Y � ������ ������� ���������
				if (abs((ball.shape->getPosition().y + (ball.shape->getRadius())) - (block[i]->shape->getPosition().y - (block[i]->shape->getSize().y / 2))) // ��������� ������
					< abs((block[i]->shape->getPosition().y + (block[i]->shape->getSize().y / 2)) - (ball.shape->getPosition().y - (ball.shape->getRadius())))) { // ��������� �����
					diffY = abs((ball.shape->getPosition().y + (ball.shape->getRadius())) - (block[i]->shape->getPosition().y - (block[i]->shape->getSize().y / 2)));
				}
				else {
					diffY = abs((block[i]->shape->getPosition().y + (block[i]->shape->getSize().y / 2)) - (ball.shape->getPosition().y - (ball.shape->getRadius())));
				}
				
				// ������������ ������� ������������ X ��� Y ��� ��������� ������ ������
				if (diffX < diffY) {
					if (abs((ball.shape->getPosition().x + (ball.shape->getRadius())) - (block[i]->shape->getPosition().x - (block[i]->shape->getSize().x / 2))) // ��������� ����� 
						< abs((block[i]->shape->getPosition().x + (block[i]->shape->getSize().x / 2)) - (ball.shape->getPosition().x - (ball.shape->getRadius())))) { // ��������� ������
						ball.speed.x = -speedBall; // ������ �����
					}
					else {
						ball.speed.x = speedBall; // ������ ������
					}
				}
				else {
					if (abs((ball.shape->getPosition().y + (ball.shape->getRadius())) - (block[i]->shape->getPosition().y - (block[i]->shape->getSize().y / 2))) // ��������� ������
						< abs((block[i]->shape->getPosition().y + (block[i]->shape->getSize().y / 2)) - (ball.shape->getPosition().y - (ball.shape->getRadius())))) { // ��������� �����
						ball.speed.y = -speedBall; // ������ �����
					}
					else {
						ball.speed.y = speedBall; // ������ ����
					}
				}
			}
		}
		
		// ������

		if (kolBlocks == 0 && level == 1) {
			block.clear();
			flagKey = false;
			window.setTitle("Arkanoid | Level 2");
			ball.shape->setPosition(247.5, 425);
			racket.shape->setPosition(247.5, 430);
			level++;

			if (Keyboard::isKeyPressed(Keyboard::Key::Space)) flagKey = true;

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 5; j++) {
					if (i % 2 == 0 && j % 2 == 0) {
						if (level == 2) block.push_back(new Block((i + 0.5) * (widthBlock + 5), (j + 0.5) * (heightBlock + 5)));
					}
				}
			}
			kolBlocks = block.size();
		}
		else if (kolBlocks == 0 && level == 2) {
			block.clear();
			flagKey = false;
			window.setTitle("Arkanoid | Level 3");
			ball.shape->setPosition(247.5, 425);
			racket.shape->setPosition(247.5, 430);
			level++;

			if (Keyboard::isKeyPressed(Keyboard::Key::Space)) flagKey = true;

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 5; j++) {
					if (level == 3) block.push_back(new Block((i + 0.5) * (widthBlock + 5), (j + 0.5) * (heightBlock + 5)));
				}
			}
			kolBlocks = block.size();
		}
		else if (kolBlocks == 0 && level == 3) {
			window.close();
			cout << "You win!!" << endl;
		}
		window.display();
	}

	cin.get();
	return 0;
}
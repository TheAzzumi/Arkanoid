#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "Block.h"
#include "Ball.h"
#include "Racket.h"


using namespace std;
using namespace sf;


int main() {
	Ball ball(247.5, 425);
	Racket racket(247.5, 430);
	vector<Block*> block;
	Config config;

	bool flagKey = false;
	float diffX;
	float diffY;
	int kolBlocks;
	int level = 1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if (j % 2 == 0) {
				if (level == 1) block.push_back(new Block((i + 0.5) * (config.widthBlock + 5), (j + 0.5) * (config.heightBlock + 5))); // ������������ ��������� ��� ������
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
			
			ball.speed.y = -config.speedBall;
			if (ball.shape->getPosition().x < racket.shape->getPosition().x) { // ����������� ������� ������� ������ �� �������
				ball.speed.x = -config.speedBall;
			}
			else {
				ball.speed.x = config.speedBall;
			}
		}
		window.draw(*ball.shape);
		if (ball.flag) { // ��� ����� ����
			window.close();
			cout << "You lose!" << endl;
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
						ball.speed.x = -config.speedBall; // ������ �����
					}
					else {
						ball.speed.x = config.speedBall; // ������ ������
					}
				}
				else {
					if (abs((ball.shape->getPosition().y + (ball.shape->getRadius())) - (block[i]->shape->getPosition().y - (block[i]->shape->getSize().y / 2))) // ��������� ������
						< abs((block[i]->shape->getPosition().y + (block[i]->shape->getSize().y / 2)) - (ball.shape->getPosition().y - (ball.shape->getRadius())))) { // ��������� �����
						ball.speed.y = -config.speedBall; // ������ �����
					}
					else {
						ball.speed.y = config.speedBall; // ������ ����
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
						if (level == 2) block.push_back(new Block((i + 0.5) * (config.widthBlock + 5), (j + 0.5) * (config.heightBlock + 5)));
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
					if (level == 3) block.push_back(new Block((i + 0.5) * (config.widthBlock + 5), (j + 0.5) * (config.heightBlock + 5)));
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
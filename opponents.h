#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Opponents
{
public:
	sf::Sprite spriteo;
	float x, y;
	float speed = 0;
	float angle = 0;
	int n = 0;
	int checkpoints[8][2] = { 600 , 1500,
							 1100, 700,
							 6600, 700,
							 7200, 1500,
							 7000, 4700,
							 6300, 5100,
							 1100, 5100,
							 600, 4400 };
	void move()
	{
		x += sin(angle) * speed;
		y -= cos(angle) * speed;
	}

	void findcheckpoint()
	{
		float tx = checkpoints[n][0];
		float ty = checkpoints[n][1];
		float beta = angle - atan2(tx - x, -ty + y);

		if (sin(beta) < 0) angle += 0.005*speed; 
		else angle -= 0.005*speed;

		if ((x - tx)*(x - tx) + (y - ty)*(y - ty) < 200 * 200)
		{
				std::cout << "Zmiana checkpointu " << "tx: " << checkpoints[n][0] << " " << "ty: " << checkpoints[n][1] << std::endl;
				n = (n+1)%8;
				std::cout << "n: " << n << std::endl;
		}
	}
};

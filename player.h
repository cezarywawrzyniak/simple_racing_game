#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class  Player
{
protected:
	sf::Texture car1;
	sf::Texture car2;
	sf::Texture car3;
public:
	int chosencar = 1;
	float x, y;
	float speed = 0, angle = 0;
	float vmax = 20.0;
	float acc = 0.5, brake = 0.7, dec = 0.3;
	float turnSpeed = 0.08;
	sf::Sprite playercar;
	 Player();
	~ Player();
	void setcords(float cordx, float cordy)
	{
		x = cordx;
		y = cordy;
	}
	void loadtextures(std::string img1, std::string img2, std::string img3)
	{
		car1.loadFromFile(img1);
		car1.setSmooth(true);
		car2.loadFromFile(img2);
		car2.setSmooth(true);
		car3.loadFromFile(img3);
		car3.setSmooth(true);
	}

	void setsprite()
	{
		playercar.setTexture(car1); 
	}
	void setorigin()
	{
		playercar.setOrigin(50, 100);
	}

	void drawplayer(sf::RenderWindow &window, float cordx, float cordy, float cordangle)
	{
		playercar.setPosition(cordx, cordy);
		playercar.setRotation(cordangle);
		window.draw(playercar);
	}

	void choosecar()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) Player::chosencar = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) Player::chosencar = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) Player::chosencar = 3;
	}

	void changecar()
	{
		if (Player::chosencar == 1)
		{
			playercar.setTexture(car1);
			Player::vmax = 20.0;
			Player::acc = 0.5, brake = 0.7, dec = 0.3;
			Player::turnSpeed = 0.08;
		}
		if (Player::chosencar == 2)
		{
			playercar.setTexture(car2);
			Player::vmax = 15.0;
			Player::acc = 0.3, brake = 0.5, dec = 0.4;
			Player::turnSpeed = 0.10;
		}
		if (Player::chosencar == 3)
		{
			playercar.setTexture(car3);
			Player::vmax = 30.0;
			Player::acc = 0.9, brake = 0.9, dec = 0.5;
			Player::turnSpeed = 0.05;
		}
	}
	void move()
	{
		x += sin(angle / 1.5) * speed;
		y -= cos(angle / 1.5) * speed;
	}

	void drive(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
	{
		//przyspieszanie
		if (sf::Keyboard::isKeyPressed(up) && Player::speed < Player::vmax)
		{
			if (Player::speed < 0) Player::speed += Player::brake;
			else Player::speed += Player::acc;
		}
		//hamowanie hamulcem
		if ((sf::Keyboard::isKeyPressed(down)) && Player::speed > -Player::vmax)
		{
			if (Player::speed > 0) Player::speed -= Player::brake;
			else Player::speed -= Player::acc;
		}
		//hamowanie silnikiem
		if (!(sf::Keyboard::isKeyPressed(up)) && !(sf::Keyboard::isKeyPressed(down)))
		{
			if (Player::speed - Player::dec > 0) Player::speed -= Player::dec;
			else if (Player::speed + Player::dec < 0) Player::speed += Player::dec;
			else Player::speed = 0;
		}
		//skret w prawo
		if ((sf::Keyboard::isKeyPressed(right)) && Player::speed != 0)Player::angle += Player::turnSpeed * Player::speed / Player::vmax;
		//skret w lewo
		if ((sf::Keyboard::isKeyPressed(left)) && Player::speed != 0) Player::angle -= Player::turnSpeed * Player::speed / Player::vmax;
	}

	void ongrass(sf::Sprite grass)
	{
		if (Player::chosencar == 1)
		{
			if (Player::playercar.getGlobalBounds().intersects(grass.getGlobalBounds()))
			{
				if (Player::speed > 10) Player::speed -= 1.5;
				else if (Player::speed < -10) Player::speed += 1.5;
			}
		}
		else if (Player::chosencar == 2)
		{
			if (Player::playercar.getGlobalBounds().intersects(grass.getGlobalBounds()))
			{
				if (Player::speed > 12.5) Player::speed -= 1;
				else if (Player::speed < -12.5) Player::speed += 1;
			}
		}
		else if (Player::chosencar == 3)
		{
			if (Player::playercar.getGlobalBounds().intersects(grass.getGlobalBounds()))
			{
				if (Player::speed > 5) Player::speed -= 2;
				if (Player::speed < -5) Player::speed += 2;

			}
		}
	}

	void onsand(sf::Sprite sand)
	{
		if (Player::chosencar == 1)
		{
			if (Player::playercar.getGlobalBounds().intersects(sand.getGlobalBounds()))
			{
				if (Player::speed > 10) 
				{
					Player::speed -= 2;
					Player::angle / 2;
				}
				else if (Player::speed < -10)
				{
					Player::speed += 2;
					Player::angle / 2;
				}
			}
		}
		else if (Player::chosencar == 2)
		{
			if (Player::playercar.getGlobalBounds().intersects(sand.getGlobalBounds()))
			{
				if (Player::speed > 12.5)
				{
					Player::speed -= 1.5;
					Player::angle / 1.25;
				}
				else if (Player::speed < -12.5)
				{
					Player::speed += 1.5;
					Player::angle / 1.25;
				}
			}
		}
		else if (Player::chosencar == 3)
		{
			if (Player::playercar.getGlobalBounds().intersects(sand.getGlobalBounds()))
			{
				if (Player::speed > 5)
				{
					Player::speed -= 2.5;
					Player::angle / 3;
				}
				else if (Player::speed < -5)
				{
					Player::speed += 2.5;
					Player::angle / 3;
				}
			}

		}
	}

	void hittires(sf::Sprite tires)
	{
		if (Player::playercar.getGlobalBounds().intersects(tires.getGlobalBounds()))
		{
			
			Player::speed = -(Player::speed);
		}
	}
	
	void stand(float cordx, float cordy)
	{
		if (x > cordx && x < cordx + 467 && y > cordy && y < cordy + 678)
		{	
			if (speed >= 7.5)
			{
				speed = 0.0000000000000000000000000000000000000000000000000000001;
				if (x < cordx + 233 && y > cordy && y < cordy + 678) x = x - 12.5;
				if (x > cordx + 233 && y > cordy && y < cordy + 678) x = x + 12.5;
				if (y < cordy + 339 && x > cordx && x < cordx + 467) y = y - 12.5;
				if (y > cordy + 339 && x > cordx && x < cordx + 467) y = y + 12.5;
			}
			else if (2.5 <= speed < 7.5 )
			{
				speed = 0.0000000000000000000000000000000000000000000000000000001;
				if (x < cordx + 233 && y > cordy && y < cordy + 678) x = x - 7.5;
				if (x > cordx + 233 && y > cordy && y < cordy + 678) x = x + 7.5;
				if (y < cordy + 339 && x > cordx && x < cordx + 467) y = y - 7.5;
				if (y > cordy + 339 && x > cordx && x < cordx + 467) y = y + 7.5;
			}
			else if (1 <= speed < 2.5)
			{
				speed = 0.0000000000000000000000000000000000000000000000000000001;
				if (x < cordx + 233 && y > cordy && y < cordy + 678) x = x - 2.5;
				if (x > cordx + 233 && y > cordy && y < cordy + 678) x = x + 2.5;
				if (y < cordy + 339 && x > cordx && x < cordx + 467) y = y - 2.5;
				if (y > cordy + 339 && x > cordx && x < cordx + 467) y = y + 2.5;
			}
			else if (speed < 1)
			{
				speed = 0.0000000000000000000000000000000000000000000000000000001;
				if (x < cordx + 233 && y > cordy && y < cordy + 678) x = x - 1;
				if (x > cordx + 233 && y > cordy && y < cordy + 678) x = x + 1;
				if (y < cordy + 339 && x > cordx && x < cordx + 467) y = y - 1;
				if (y > cordy + 339 && x > cordx && x < cordx + 467) y = y + 1;
			}

		}
	
	}
};

 Player:: Player()
{
	 std::cout << "Stworzono gracza" << std::endl;
}

 Player::~ Player()
{
}



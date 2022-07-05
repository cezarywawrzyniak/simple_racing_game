#pragma once
#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>

class Finishline
{
private:
	sf::Texture line;
	sf::Texture checkpoint;

	sf::Texture zerothree;
	sf::Texture onethree;
	sf::Texture twothree;
	sf::Texture threethree;

	sf::Texture finishtext;

	int lcollision = 0;
	int ltmp = 0;
	int ccollision = 0;
	int ctmp = 0;
	
	int checkcntr = 1;
public:
	Finishline();
	~Finishline();
	int lapcntr = 0;

	sf::Sprite sLine;
	sf::Sprite sCheckpoint;

	sf::Sprite sLapcntr03;
	sf::Sprite sLapcntr13;
	sf::Sprite sLapcntr23;
	sf::Sprite sLapcntr33;

	sf::Sprite sFinishtext;

	sf::Time start;
	sf::Time lap1;
	sf::Time lap2;
	sf::Time lap3;
	float finaltime = 99999;

	std::string stringlap1;
	std::string stringlap2;
	std::string stringlap3;
	std::string stringfullrace;

	void loadtextures(std::string finishline, std::string chckpnt, std::string img0, std::string img1, std::string img2, std::string img3, std::string imge)
	{
		line.loadFromFile(finishline);
		line.setSmooth(true);

		checkpoint.loadFromFile(chckpnt);
		checkpoint.setSmooth(true);

		zerothree.loadFromFile(img0);
		zerothree.setSmooth(true);
		onethree.loadFromFile(img1);
		onethree.setSmooth(true);
		twothree.loadFromFile(img2);
		twothree.setSmooth(true);
		threethree.loadFromFile(img3);
		threethree.setSmooth(true);

		finishtext.loadFromFile(imge);
		finishtext.setSmooth(true);
	}
	void setsprites(float xl, float yl, float xc, float yc, float xlap, float ylap)
	{
		sLine.setTexture(line);
		sLine.setPosition(xl, yl);
		sCheckpoint.setTexture(checkpoint);
		sCheckpoint.setPosition(xc, yc);

		sLapcntr03.setTexture(zerothree);
		sLapcntr03.setPosition(xlap, ylap);
		sLapcntr13.setTexture(onethree);
		sLapcntr13.setPosition(xlap, ylap);
		sLapcntr23.setTexture(twothree);
		sLapcntr23.setPosition(xlap, ylap);
		sLapcntr33.setTexture(threethree);
		sLapcntr33.setPosition(xlap, ylap);

		sFinishtext.setTexture(finishtext);
	}
	void drawsprite(sf::RenderWindow &window)
	{
		window.draw(sLine);
		window.draw(sCheckpoint);
	}
	void checkpointcounter(sf::Sprite car)
	{
		if (car.getGlobalBounds().intersects(sCheckpoint.getGlobalBounds()))
		{
			ccollision = 1;
			ctmp = 1;
		}
		else if (!car.getGlobalBounds().intersects(sCheckpoint.getGlobalBounds()))
		{
			ctmp = 0;
		}

		if (ctmp != ccollision)
		{
			if(checkcntr == 1 ) checkcntr++;
			else
			{
				if (checkcntr == lapcntr) checkcntr++;
			}
			std::cout << "Przejazd przez checkpoint po raz: " << checkcntr-1 << std::endl;
			ccollision = ctmp;
		}
	}
	void lapcounter(sf::Sprite car)
	{
		if (car.getGlobalBounds().intersects(sLine.getGlobalBounds()))
		{
			lcollision = 1;
			ltmp = 1;
		}
		else if (!car.getGlobalBounds().intersects(sLine.getGlobalBounds()))
		{
			ltmp = 0;
		}

		if (ltmp != lcollision)
		{
			if (lapcntr < checkcntr)
			{
				lapcntr++;
			}
			std::cout << "Przejazd przez mete, okrazenie: " << lapcntr << std::endl;
			lcollision = ltmp;
		}
		
	}
	void changelapcounter(sf::RenderWindow &window)
	{
		switch (lapcntr)
		{
		default:
			window.draw(sLapcntr03);
			break;
		case 1:
			window.draw(sLapcntr13);
			break;
		case 2:
			window.draw(sLapcntr23);
			break;
		case 3:
			window.draw(sLapcntr33);
			break;
		}
	}
	void end(sf::RenderWindow &window)
	{
		if (lapcntr >= 4)
		{
			finaltime = lap3.asSeconds() - start.asSeconds();
			window.draw(sFinishtext);
		}
	}

	void gettime(sf::Clock clock)
	{
		if (lapcntr == 0)
		{
			start = clock.getElapsedTime();
		}
		if (lapcntr == 1)
		{
			lap1 = clock.getElapsedTime();
			stringlap1 = std::to_string(lap1.asSeconds() - start.asSeconds());
			//std::cout << stringlap1 << std::endl;
			
		}
		if (lapcntr == 2)
		{
			lap2 = clock.getElapsedTime();
			stringlap2 = std::to_string(lap2.asSeconds() - lap1.asSeconds());
			//std::cout << "Pierwsze: " << lap1.asSeconds() - start.asSeconds() << std::endl;
			//std::cout << lap2.asSeconds() - lap1.asSeconds() << std::endl;
		}
		if (lapcntr == 3)
		{
			lap3 = clock.getElapsedTime();
			stringlap3 = std::to_string(lap3.asSeconds() - lap2.asSeconds());
			//std::cout << "Pierwsze: " << lap1.asSeconds() - start.asSeconds() << std::endl;
			//std::cout << "Drugie: " << lap2.asSeconds() - lap1.asSeconds() << std::endl;
			//std::cout << lap3.asSeconds() - lap2.asSeconds() << std::endl;
		}
		if (lapcntr == 4)
		{
			stringfullrace = std::to_string(lap3.asSeconds() - start.asSeconds());
			//std::cout << "Pierwsze: " << lap1.asSeconds() - start.asSeconds() << std::endl;
			//std::cout << "Drugie: " << lap2.asSeconds() - lap1.asSeconds() << std::endl;
			//std::cout << "Trzecie: " << lap3.asSeconds() - lap2.asSeconds() << std::endl;
			//std::cout << "Caly: " << stringfullrace << std::endl;
		}
	}


};
Finishline::Finishline()
{
	std::cout << "Stworzono linie" << std::endl;
}
Finishline::~Finishline()
{

}
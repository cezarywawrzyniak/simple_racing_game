#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle
{
protected:
	sf::Texture textureO;
public:
	float x;
	float y;
	Obstacle();
	~Obstacle();
	sf::Sprite sSprite;
	void loadtexture(std::string img)
	{
		textureO.loadFromFile(img);
		textureO.setSmooth(true);
		
	}
	void setsprite(float cordx, float cordy)
	{
		sSprite.setTexture(textureO);
		sSprite.setPosition(cordx, cordy);
		x = cordx;
		y = cordy;
	}
	void drawsprite(sf::RenderWindow &window)
	{
		window.draw(sSprite);
	}

};

class Grass : public Obstacle
{	
};
class Sand : public Obstacle
{
};
class Tires : public Obstacle
{
};
class Stand : public Obstacle
{
};
Obstacle::Obstacle()
{
	std::cout << "Stworzono przeszkode" << std::endl;
}
Obstacle::~Obstacle()
{
}

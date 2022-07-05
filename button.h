#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
protected:
	sf::Texture textureb;
public:
	float x;
	float y;
	Button();
	~Button();
	sf::Sprite sSprite;
	void loadtexture(std::string img)
	{
		textureb.loadFromFile(img);
		textureb.setSmooth(true);

	}
	void setsprite(float cordx, float cordy)
	{
		sSprite.setTexture(textureb);
		sSprite.setPosition(cordx, cordy);
		x = cordx;
		y = cordy;
	}
	void drawsprite(sf::RenderWindow &window)
	{
		window.draw(sSprite);
	}

};

Button::Button()
{
	std::cout << "Stworzono przycisk" << std::endl;
}
Button::~Button()
{
}
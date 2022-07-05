#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
protected:
	sf::Texture texture1;
	sf::Texture texture2;
public:
	float x;
	float y;
	Button();
	~Button();
	sf::Sprite sSprite;
	void loadtexture1(std::string img)
	{
		texture1.loadFromFile(img);
		texture1.setSmooth(true);

	}
	void loadtexture2(std::string img)
	{
		texture2.loadFromFile(img);
		texture2.setSmooth(true);

	}
	void setsprite(float cordx, float cordy)
	{
		sSprite.setTexture(texture1);
		sSprite.setPosition(cordx, cordy);
	}
	void changesprite1()
	{
		sSprite.setTexture(texture1);
	}
	void changesprite2()
	{
		sSprite.setTexture(texture2);
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

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Button {
public:
	Button(sf::Vector2f size);
	virtual ~Button();
	virtual void onClick() = 0;
	virtual void update() {};
	void draw(sf::RenderWindow &window);
	void setText(std::string text1);
	void setFont(sf::Font &font);
	void setBaseColor(sf::Color baseColor1);
	void setHoverColor(sf::Color hoverColor1);
	void setFontSize(unsigned int fontSize);
	void setPosition(sf::Vector2f position);
private:
	sf::RectangleShape shape;
	sf::Color baseColor;
	sf::Color hoverColor;
	sf::Text text;
	void updateTextPosition();
	bool clicked = false;
};
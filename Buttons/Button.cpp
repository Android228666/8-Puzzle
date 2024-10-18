#include "Button.h"
#include "../PuzzleGame.h"

Button::Button(sf::Vector2f size) {
	this->shape = sf::RectangleShape(size);
	PuzzleGame::getInstance().registerButton(this);
}

Button::~Button() {
	PuzzleGame::getInstance().unregisterButton(this);
}

void Button::draw(sf::RenderWindow &window) {
	window.draw(shape);
	window.draw(text);
	update();
	sf::Vector2f mousePosition = (sf::Vector2f)(sf::Mouse::getPosition(window));
	if (shape.getGlobalBounds().contains(mousePosition)) {
		shape.setFillColor(hoverColor);
		text.setFillColor(baseColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (!clicked) {
				clicked = true;
				onClick();
			}
		}
		else {
			clicked = false;
		}
	}
	else {
		shape.setFillColor(baseColor);
		text.setFillColor(hoverColor);
		
	}
}

void Button::setBaseColor(sf::Color baseColor1) {
	baseColor = baseColor1;
}

void Button::setHoverColor(sf::Color hoverColor1) {
	hoverColor = hoverColor1;
}

void Button::setFont(sf::Font &font1) {
	text.setFont(font1);
	updateTextPosition();
}

void Button::setText(std::string text1) {
	text.setString(text1);
	if (text.getFont() != nullptr) {
		updateTextPosition();
	}
}

void Button::setFontSize(unsigned int fontSize) {
	text.setCharacterSize(fontSize);
	if (text.getFont() != nullptr) {
		updateTextPosition();
	}
}

void Button::updateTextPosition() {
	sf::FloatRect localBounds = text.getLocalBounds();
	sf::Vector2f textSize(
		localBounds.width,
		localBounds.height
	);
	sf::Vector2f textPosition(shape.getPosition() + (shape.getSize() - textSize) / 2.0f);
	textPosition.x -= localBounds.left;
	textPosition.y -= localBounds.top;
	text.setPosition(textPosition);
}

void Button::setPosition(sf::Vector2f position) {
	this->shape.setPosition(position);
	updateTextPosition();
}
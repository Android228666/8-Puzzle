#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "../PuzzleGame.h"

class RandomizeButton : public Button {
public:
	RandomizeButton(sf::Vector2f size);
	void onClick() override;
};
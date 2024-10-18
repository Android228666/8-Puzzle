#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "../PuzzleGame.h"

class SetBoardButton : public Button {
public:
	SetBoardButton(sf::Vector2f size);
	void onClick() override;
};
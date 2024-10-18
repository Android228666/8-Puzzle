#pragma once

#include <iostream>
#include "Button.h"
#include "../PuzzleState.h"
#include "../PuzzleGame.h"

class BFSButton : public Button {
public:
	BFSButton(sf::Vector2f size1);
	void onClick() override;
};
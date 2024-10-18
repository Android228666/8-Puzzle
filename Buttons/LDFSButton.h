#pragma once

#include <iostream>
#include "Button.h"
#include "../PuzzleState.h"
#include "../PuzzleGame.h"

class LDFSButton : public Button {
public:
	LDFSButton(sf::Vector2f size1);
	void onClick() override;
};
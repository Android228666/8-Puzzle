#include "RandomizeButton.h"
#include <SFML/Graphics.hpp>
#include <iostream>

RandomizeButton::RandomizeButton(sf::Vector2f size1) : Button(size1) {}

void RandomizeButton::onClick() {
	if (Tile::isBeingSolvedAutomaticallyNow()) {
		return;
	}
	PuzzleGame::getInstance().randomizeTiles();
}
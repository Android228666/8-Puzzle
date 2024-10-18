#include "SetBoardButton.h"
#include <SFML/Graphics.hpp>
#include "../PuzzleGame.h"
#include "Tile.h"
#include <iostream>

SetBoardButton::SetBoardButton(sf::Vector2f size1) : Button(size1) {}

void SetBoardButton::onClick() {
	if (Tile::isBeingSolvedAutomaticallyNow()) {
		return;
	}
	Tile::setLastAssignedValue(1);
	PuzzleGame::getInstance().initializeEmptyTiles();
}
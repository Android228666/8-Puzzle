#pragma once

#include "Buttons/Button.h"
#include "Buttons/Tile.h"
#include <iostream>
#include <random>
#include <optional>

class PuzzleGame {
public:
	void start();
	void initializeEmptyTiles();
	void randomizeTiles();
	void registerButton(Button* button);
	void unregisterButton(Button* button);
	void checkField();
	void moveTiles(const std::vector<int>& sequenceToWin);
	std::array<std::array<int, 3>, 3> getStateMatrix();
	Tile* findTileByIndex(sf::Vector2i index);
	Tile* findTileByValue(int value);
	void showNodesCount(int nodesCount);
	static PuzzleGame& getInstance() {
		if (instance == nullptr) {
			instance = new PuzzleGame;
		}
		return *instance;
	}

private:
	std::optional<sf::Text> nodesCountText;
	static PuzzleGame* instance;
	std::vector<Button*> buttons;
	std::mt19937 randomizer;
	sf::Font font;

	PuzzleGame();
	void initializeTiles();
	void initializeSetBoardButton();
	void initializeRandomizeButton();
	void initializeBFSButton();
	void initializeLDFSButton();
};
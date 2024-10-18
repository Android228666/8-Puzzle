#include "Tile.h"
#include "../GameFieldConstants.h"
#include "../PuzzleGame.h"
#include <iostream>

std::vector<Tile*> Tile::allTiles = std::vector<Tile*>();
int Tile::lastAssignedValue = 1;

Tile::Tile(sf::Vector2f size) : Button(size) {
	allTiles.push_back(this);
}

Tile::~Tile() {
	auto k = std::find(allTiles.begin(), allTiles.end(), this);
	allTiles.erase(k);
}

int Tile::getTileValue() {
	return tileValue;
}

sf::Vector2i Tile::getTileIndex() {
	return tileIndex;
}

void Tile::onClick() {
	if (isBeingSolvedAutomaticallyNow()) {
		return;
	}
	if (!initialized) {
		this->setTileValue(lastAssignedValue);
		this->setText(std::to_string(lastAssignedValue));
		lastAssignedValue++;
		if (lastAssignedValue == 9) {
			for (int i = 0; i < allTiles.size(); i++) {
				if (allTiles[i]->getTileValue() == 0) {
					delete allTiles[i];
					break;
				}
			}
		}
		PuzzleGame::getInstance().checkField();
		return;
	}
	auto freeTileIndex = this->getFreeIndex();
	if (freeTileIndex.has_value()) {
		setTileIndexAndPosition(freeTileIndex.value());
	}

	PuzzleGame::getInstance().checkField();
}

void Tile::setTileValue(int tileValue1) {
	tileValue = tileValue1;
	initialized = true;
}

void Tile::setTileIndex(sf::Vector2i tilePosition1) {
	tileIndex = tilePosition1;
}

bool Tile::isInitialized() {
	return initialized;
}

void Tile::setLastAssignedValue(int lastAssignedValue1) {
	lastAssignedValue = lastAssignedValue1;
}

bool Tile::areAllInitialized() {
	for (int i = 0; i < Tile::allTiles.size(); i++) {
		if (!(allTiles[i]->isInitialized())) {
			return false;
		}
	}
	return true;
}

void Tile::delayMove(int frames) {
	for (int i = 0; i < moveDelayQueue.size(); i++) {
		frames -= moveDelayQueue[i];
	}
	moveDelayQueue.push_back(frames);
}

bool Tile::isBeingSolvedAutomaticallyNow() {
	for (int i = 0; i < allTiles.size(); i++) {
		if (!(allTiles[i]->moveDelayQueue.empty())) {
			return true;
		}
	}

	return false;
}

void Tile::update() {
	if (!moveDelayQueue.empty()) {
		moveDelayQueue.front()--;
		if (moveDelayQueue.front() <= 0) {
			auto freeTilePosition = this->getFreeIndex();
			if (freeTilePosition.has_value()) {
				this->setTileIndexAndPosition(freeTilePosition.value());
			}
			moveDelayQueue.erase(moveDelayQueue.begin());
		}
	}
}

void Tile::setTileIndexAndPosition(sf::Vector2i tileIndex){
	sf::Vector2f tilePosition(
		FIELD_POSITION.x + FIELD_PADDING.x + (TILE_SIZE.x + TILES_GAP.x) * tileIndex.x,
		FIELD_POSITION.y + FIELD_PADDING.x + (TILE_SIZE.y + TILES_GAP.y) * tileIndex.y
	);

	this->setTileIndex(tileIndex);
	this->setPosition(tilePosition);
}


bool Tile::isPositionFree(sf::Vector2i position) {
	if (position.x > 2 || position.x < 0 || position.y > 2 || position.y < 0) {
		return false;
	}

	for (int i = 0; i < allTiles.size(); i++) {
		if (allTiles[i]->tileIndex == position) {
			return false;
		}
	}

	return true;
}

std::optional<sf::Vector2i> Tile::getFreeIndex() {
	sf::Vector2i xRight(this->tileIndex.x + 1, this->tileIndex.y);
	sf::Vector2i xLeft(this->tileIndex.x - 1, this->tileIndex.y);
	sf::Vector2i yTop(this->tileIndex.x, this->tileIndex.y - 1);
	sf::Vector2i yBottom(this->tileIndex.x, this->tileIndex.y + 1);
	if (isPositionFree(xRight)) {
		return xRight;
	}
	else if(isPositionFree(xLeft)) {
		return xLeft;
	}
	else if (isPositionFree(yTop)) {
		return yTop;
	}
	else if (isPositionFree(yBottom)) {
		return yBottom;
	}
	else {
		return std::nullopt;
	}
}
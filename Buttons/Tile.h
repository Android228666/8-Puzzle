#pragma once

#include "Button.h"
#include <optional>
#include <queue>

class Tile: public Button{
public:
	Tile(sf::Vector2f size);
	~Tile();
	int getTileValue();
	sf::Vector2i getTileIndex();
	std::optional<sf::Vector2i> getFreeIndex();
	bool isInitialized();
	void setTileValue(int tileValue1);
	void setTileIndex(sf::Vector2i tilePosition1);
	void setTileIndexAndPosition(sf::Vector2i tileIndex);
	static bool isBeingSolvedAutomaticallyNow();
	static void setLastAssignedValue(int lastAssignedValue1);
	void delayMove(int frames);
	void onClick() override;
	void update() override;
	static bool areAllInitialized();
	static std::vector<Tile*> allTiles;
private:
	std::vector<int> moveDelayQueue;
	int tileValue = 0;
	sf::Vector2i tileIndex;
	static int lastAssignedValue;
	bool initialized = false;
	bool isPositionFree(sf::Vector2i position);
};
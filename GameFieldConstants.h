#pragma once
#include <SFML/Graphics.hpp>
const sf::Color BACKGROUND_COLOR(20, 20, 20, 255);
const sf::Vector2f FIELD_SIZE(500, 500);
const sf::Vector2f FIELD_PADDING(15, 15);
const sf::Vector2f TILES_GAP(15, 15);
const sf::Vector2f FIELD_POSITION(50, 50);
const sf::Vector2f TILE_SIZE = (FIELD_SIZE - 2.0f * FIELD_PADDING - 2.0f * TILES_GAP) / 3.0f;

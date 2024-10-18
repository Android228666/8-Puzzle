#include <SFML/Graphics.hpp>
#include "PuzzleGame.h"
#include "Buttons/Button.h"
#include "Buttons/Tile.h"
#include "Buttons/RandomizeButton.h"
#include "Buttons/SetBoardButton.h"
#include "Buttons/BFSButton.h"
#include "Buttons/LDFSButton.h"
#include "PuzzleState.h"
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <windows.h>
#include "GameFieldConstants.h"
#include "Resourses.h"

PuzzleGame* PuzzleGame::instance = nullptr;
PuzzleGame::PuzzleGame(): randomizer(time(NULL)) {}

void PuzzleGame::registerButton(Button* button) {
    buttons.push_back(button);
}

void PuzzleGame::unregisterButton(Button* button) {
    auto iter = std::find(buttons.begin(), buttons.end(), button);
    buttons.erase(iter);
}

bool isGoalState() {
    for (int i = 0; i < Tile::allTiles.size(); i++) {
        sf::Vector2i tileIndex = Tile::allTiles[i]->getTileIndex();

        if (Tile::allTiles[i]->getTileValue() - 1 != tileIndex.x + 3 * tileIndex.y) {
            return false;
        }

        if (!Tile::allTiles[i]->isInitialized()) {
            return false;
        }
    }
    return true;
}

bool isSolvable() {
    int inversions = 0;
    for (int i = 0; i < Tile::allTiles.size(); i++) {
        for (int j = 0; j < Tile::allTiles.size(); j++) {
            if (i != j) {
                Tile* a = Tile::allTiles[i];
                Tile* b = Tile::allTiles[j];
                int position1 = a->getTileIndex().x + 3 * a->getTileIndex().y;
                int position2 = b->getTileIndex().x + 3 * b->getTileIndex().y;
                if (a->getTileValue() > b->getTileValue() && position1 < position2){
                    inversions++;
                }
            }
        }

        if (!Tile::allTiles[i]->isInitialized()) {
            return true;
        }
    }
    
    return inversions % 2 == 0;
}

void PuzzleGame::checkField() {
    if (!isSolvable()) {
        MessageBox(NULL, "Configuration of tiles created by yourself is unsolvable.", "Bad news!", MB_OK | MB_ICONERROR);
        initializeEmptyTiles();
    }
    else if (isGoalState()) {
        MessageBox(NULL, "                              You won!!!                              ", "Success!", MB_OK | MB_ICONINFORMATION);
    }
}

void PuzzleGame::initializeEmptyTiles() {
    Tile::setLastAssignedValue(1);
    int size = Tile::allTiles.size();
    for (int i = 0; i < size; i++) {
        delete Tile::allTiles[0];
    }
    for (int xi = 0; xi < 3; xi++) {
        for (int yi = 0; yi < 3; yi++) {
            Tile* tile1 = new Tile(TILE_SIZE);
            tile1->setBaseColor(sf::Color(10, 10, 10, 255));
            tile1->setHoverColor(sf::Color(255, 255, 255, 255));
            tile1->setTileIndexAndPosition(sf::Vector2i(xi, yi));
            tile1->setFont(font);
            tile1->setFontSize(110);
        }
    }
}

void PuzzleGame::initializeTiles() {
    int size = Tile::allTiles.size();
    for (int i = 0; i < size; i++) {
        delete Tile::allTiles[0];
    }
    Tile::allTiles.clear();
    for (int xi = 0; xi < 3; xi++) {
        for (int yi = 0; yi < 3; yi++) {
            if ((xi + yi * 3) != 0) {
                Tile* tile1 = new Tile(TILE_SIZE);
                tile1->setBaseColor(sf::Color(10, 10, 10, 255));
                tile1->setHoverColor(sf::Color(255, 255, 255, 255));
                tile1->setTileIndexAndPosition(sf::Vector2i(xi, yi));
                tile1->setTileValue(xi + yi * 3);
                tile1->setFont(font);
                tile1->setText(std::to_string(xi + yi * 3));
                tile1->setFontSize(110);
            }
        }
    }
}

void PuzzleGame::randomizeTiles() {
    do {
        initializeTiles();
        std::array<int, 9>arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        std::shuffle(arr.begin(), arr.end(), randomizer);
        for (int i = 0; i < arr.size() - 1; i++) {
            Tile::allTiles[i]->setTileIndexAndPosition(sf::Vector2i(arr[i] % 3, arr[i] / 3));
        }
    } while (!isSolvable());
}

Tile* PuzzleGame::findTileByValue(int value) {
    for (int i = 0; i < Tile::allTiles.size(); i++) {
        if (Tile::allTiles[i]->getTileValue() == value) {
            return Tile::allTiles[i];
        }
    }
}

Tile* PuzzleGame::findTileByIndex(sf::Vector2i index) {
    for (int i = 0; i < Tile::allTiles.size(); i++) {
        if (Tile::allTiles[i]->getTileIndex() == index) {
            return Tile::allTiles[i];
        }
    }
    return nullptr;
}

std::array<std::array<int, 3>, 3> PuzzleGame::getStateMatrix() {
    std::array<std::array<int, 3>, 3> result;
    Tile* currentTile;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            currentTile = findTileByIndex(sf::Vector2i(y, x));
            if (currentTile != nullptr) {
                result[x][y] = currentTile->getTileValue();
            }
            else {
                result[x][y] = 0;
            }
        }
    }

    return result;
}

void PuzzleGame::moveTiles(const std::vector<int>& sequenceToWin) {
    for (int i = 0; i < sequenceToWin.size(); i++) {
        Tile* tileToMove = findTileByValue(sequenceToWin[i]);
        tileToMove->delayMove(10 * i);
    }
}

void PuzzleGame::showNodesCount(int nodesCount) {
    if (!nodesCountText.has_value()) {
        nodesCountText = sf::Text();
        nodesCountText->setFont(font);
        nodesCountText->setCharacterSize(18);
        nodesCountText->setPosition(sf::Vector2f(690, 575));
        nodesCountText->setColor(sf::Color(255, 255, 255, 255));
    }
    nodesCountText->setString("Nodes counter: " + std::to_string(nodesCount)); 
}

void PuzzleGame::initializeSetBoardButton() {
    sf::Vector2f setBoardButtonSize(280, 80);
    sf::Vector2f setBoardButtonPosition(600, 100);
    SetBoardButton* setBoardButton = new SetBoardButton(setBoardButtonSize);
    setBoardButton->setBaseColor(sf::Color(10, 10, 10, 255));
    setBoardButton->setHoverColor(sf::Color(255, 255, 255, 255));
    setBoardButton->setFont(font);
    setBoardButton->setText("Set board");
    setBoardButton->setFontSize(36);
    setBoardButton->setPosition(setBoardButtonPosition);
}

void PuzzleGame::initializeRandomizeButton() {
    sf::Vector2f randomizeButtonSize(280, 80);
    sf::Vector2f randomizeButtonPosition(600, 190);
    RandomizeButton* randomizeButton = new RandomizeButton(randomizeButtonSize);
    randomizeButton->setBaseColor(sf::Color(10, 10, 10, 255));
    randomizeButton->setHoverColor(sf::Color(255, 255, 255, 255));
    randomizeButton->setFont(font);
    randomizeButton->setText("Randomize");
    randomizeButton->setFontSize(36);
    randomizeButton->setPosition(randomizeButtonPosition);
}

void PuzzleGame::initializeBFSButton() {
    sf::Vector2f bfsButtonSize(280, 80);
    sf::Vector2f bfsButtonPosition(600, 300);
    BFSButton* bfsButton = new BFSButton(bfsButtonSize);
    bfsButton->setBaseColor(sf::Color(10, 10, 10, 255));
    bfsButton->setHoverColor(sf::Color(255, 255, 255, 255));
    bfsButton->setFont(font);
    bfsButton->setText("BFS Algorithm");
    bfsButton->setFontSize(36);
    bfsButton->setPosition(bfsButtonPosition);
}

void PuzzleGame::initializeLDFSButton() {
    sf::Vector2f ldfsButtonSize(280, 80);
    sf::Vector2f ldfsButtonPosition(600, 390);
    LDFSButton* ldfsButton = new LDFSButton(ldfsButtonSize);
    ldfsButton->setBaseColor(sf::Color(10, 10, 10, 255));
    ldfsButton->setHoverColor(sf::Color(255, 255, 255, 255));
    ldfsButton->setFont(font);
    ldfsButton->setText("LDFS Algorithm");
    ldfsButton->setFontSize(36);
    ldfsButton->setPosition(ldfsButtonPosition);
}

void PuzzleGame::start() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "8-Puzzle", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setIcon(ICON_WIDTH, ICON_HEIGHT, ICON);

    sf::RectangleShape gameField(FIELD_SIZE);
    gameField.setPosition(FIELD_POSITION);
    gameField.setFillColor(sf::Color(80, 80, 80, 255));

    if (!font.loadFromMemory(FONT, sizeof(FONT))) {
        throw std::runtime_error("Failed to load the font!");
    }
    initializeEmptyTiles();

    initializeSetBoardButton();
    initializeRandomizeButton();
    initializeBFSButton();
    initializeLDFSButton();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(BACKGROUND_COLOR);
        window.draw(gameField);
        if (nodesCountText.has_value()) {
            window.draw(nodesCountText.value());
        }
        for (int i = 0; i < buttons.size(); i++) {
            buttons[i]->draw(window);
        }
        window.display();
    }
    for (int i = 0; i < buttons.size(); i++) {
        delete buttons[i];
    }
}
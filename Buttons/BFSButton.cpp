#include "BFSButton.h"
#include "../PuzzleState.h"
#include <windows.h>

BFSButton::BFSButton(sf::Vector2f size1) : Button(size1) {}

void BFSButton::onClick() {
	if (!Tile::areAllInitialized()) {
		MessageBox(NULL, "Not all nodes were setted, you can't play!", "Bad news!", MB_OK | MB_ICONERROR);
	}
	if (Tile::isBeingSolvedAutomaticallyNow()) {
		return;
	}
	PuzzleState bfsBoard(PuzzleGame::getInstance().getStateMatrix());
	bfsBoard.solveByBFS();
	PuzzleGame::getInstance().moveTiles(bfsBoard.getPath());
	bfsBoard.writeInformationAboutSolvePath();
	PuzzleGame::getInstance().showNodesCount(bfsBoard.getNodesCount());

}
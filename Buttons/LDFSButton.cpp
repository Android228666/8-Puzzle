#include "LDFSButton.h"
#include <windows.h>
#include "../PuzzleState.h"

LDFSButton::LDFSButton(sf::Vector2f size1) : Button(size1) {}

void LDFSButton::onClick() {
	if (!Tile::areAllInitialized()) {
		MessageBox(NULL, "Not all nodes were set!", "Bad news!", MB_OK | MB_ICONERROR);
		return;
	}
	if (Tile::isBeingSolvedAutomaticallyNow()) {
		return;
	}
	try {
		PuzzleState ldfsBoard(PuzzleGame::getInstance().getStateMatrix());
		ldfsBoard.solveByLDFS(500);
		PuzzleGame::getInstance().moveTiles(ldfsBoard.getPath());
		ldfsBoard.writeInformationAboutSolvePath();
		PuzzleGame::getInstance().showNodesCount(ldfsBoard.getNodesCount());
	}
	catch (const std::exception& e) {
		MessageBox(NULL, e.what(),"Exception!", MB_OK | MB_ICONERROR);
	}
}
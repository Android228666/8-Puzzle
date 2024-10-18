#include <iostream>
#include "PuzzleGame.h"
#include <windows.h>

int main() {
	try {
		PuzzleGame::getInstance().start();
	}
	catch (const std::exception& e) {
		MessageBox(NULL, e.what(), "Exception!", MB_OK | MB_ICONERROR);
	}
	return 0; 
}
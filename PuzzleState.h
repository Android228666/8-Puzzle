#pragma once
#include <array>
#include <vector>
#include <fstream>

struct BFSNode {
	std::array<std::array<int, 3>, 3> board;
	int zeroRow, zeroCol;
	std::vector<int> path;

	bool operator<(const BFSNode& other) const {
		return board < other.board;
	}
};

struct LDFSNode {
	std::array<std::array<int, 3>, 3> board;
	int zeroRow, zeroCol;
	std::vector<int> path;
	int depth;

	bool operator<(const LDFSNode& other) const {
		return board < other.board;
	}
};

class PuzzleState {
	std::array<std::array<int, 3>, 3> startBoard;
	std::vector<int> path;
	int nodesCount = 0;
public:
	PuzzleState() = default;

	PuzzleState(const std::array<std::array<int, 3>, 3>& b) {
		startBoard = b;
	}

	const std::array<std::array<int, 3>, 3>& getStateBoard() {
		return startBoard;
	}

	const std::vector<int>& getPath() {
		return path;
	}

	void solveByBFS();
	void solveByLDFS(int depthLimit);
	void writeInformationAboutSolvePath();
	int getNodesCount();
};
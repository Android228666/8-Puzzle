#include "PuzzleState.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stack>
#include <set>

template<typename T> bool isGoalState(const T& state) {
	static const std::array<std::array<int, 3>, 3> goalBoard = {
		std::array<int, 3>{1, 2, 3},
		std::array<int, 3>{4, 5, 6},
		std::array<int, 3>{7, 8, 0}
	};
	return state.board == goalBoard;
}

template<typename T> void swapCells(T& state, int newRow, int newCol) {
	int temp = state.board[state.zeroRow][state.zeroCol];
	state.board[state.zeroRow][state.zeroCol] = state.board[newRow][newCol];
	state.board[newRow][newCol] = temp;
	state.zeroRow = newRow;
	state.zeroCol = newCol;
}

std::vector<BFSNode> generateNeighbors(const BFSNode& currentState) {
	static const int r[] = { -1, 0, 1, 0 };
	static const int c[] = { 0, 1, 0, -1 };

	std::vector<BFSNode> neighbors;
	for (int i = 0; i < 4; i++) {
		int newRow = currentState.zeroRow + r[i];
		int newCol = currentState.zeroCol + c[i];

		if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
			BFSNode neighborState = currentState;
			neighborState.path.push_back(neighborState.board[newRow][newCol]);
			swapCells(neighborState, newRow, newCol);
			neighbors.push_back(neighborState);
		}
	}

	return neighbors;
}

std::vector<LDFSNode> generateNeighbors(const LDFSNode& currentState) {
	static const int r[] = { -1, 0, 1, 0 };
	static const int c[] = { 0, 1, 0, -1 };

	std::vector<LDFSNode> neighbors;
	for (int i = 0; i < 4; i++) {
		int newRow = currentState.zeroRow + r[i];
		int newCol = currentState.zeroCol + c[i];

		if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
			LDFSNode neighborState = currentState;
			neighborState.path.push_back(neighborState.board[newRow][newCol]);
			swapCells(neighborState, newRow, newCol);
			neighborState.depth = currentState.depth + 1;
			neighbors.push_back(neighborState);
		}
	}

	return neighbors;
}

void PuzzleState::solveByBFS() {
	int zeroX = 0, zeroY = 0;
	for (int i = 0; i < startBoard.size(); i++) {
		for (int j = 0; j < startBoard.size(); j++) {
			if (startBoard[i][j] == 0) {
				zeroX = i;
				zeroY = j;
			}
		}
	}
	BFSNode startState{startBoard, zeroX, zeroY, {}};

	std::queue<BFSNode> stateQueue;
	std::set<BFSNode> visited;

	stateQueue.push(startState);
	visited.insert(startState);

	while (!stateQueue.empty()) {
		BFSNode currentState = stateQueue.front();
		stateQueue.pop();

		if (isGoalState(currentState)) {
			this->path = currentState.path;
			nodesCount = visited.size();
			return;
		}

		std::vector<BFSNode> neighbors = generateNeighbors(currentState);
		for (const BFSNode& neighbor : neighbors) {
			if (visited.find(neighbor) == visited.end()) {
				stateQueue.push(neighbor);
				visited.insert(neighbor);
			}
		}
	}
}

void PuzzleState::solveByLDFS(int depthLimit) {
	int zeroX, zeroY;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (startBoard[i][j] == 0) {
				zeroX = i;
				zeroY = j;
			}
		}
	}

	LDFSNode startState{ startBoard, zeroX, zeroY, {}, 0};
	std::stack<LDFSNode> stack;
	std::set<LDFSNode> visited;

	stack.push(startState);
	visited.insert(startState);

	while (!stack.empty()) {
		LDFSNode currentState = stack.top();
		stack.pop();

		if (isGoalState(currentState)) {
			this->path = currentState.path;
			nodesCount = visited.size();
			return;
		}

		if (currentState.depth < depthLimit) {
			std::vector<LDFSNode> neighbors = generateNeighbors(currentState);
			for (const LDFSNode& neighbor : neighbors) {
				if (visited.find(neighbor) == visited.end()) {
					stack.push(neighbor);
					visited.insert(neighbor);
				}
			}
		}
	}
	
	throw std::runtime_error("The depth of goal state is greater than depth limit of LDFS algorithm!");
}

int PuzzleState::getNodesCount() {
	return nodesCount;
}

void PuzzleState::writeInformationAboutSolvePath() {
	std::string filename = "Solve_file.txt";
	std::ofstream writeTo(filename);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			writeTo << startBoard[i][j] << " ";
		}
		writeTo << "\n";
	}

	writeTo << "Moves to solve: ";
	for (int i = 0; i < path.size(); i++) {
		writeTo << path[i] << " ";
	}

	writeTo.close();
}
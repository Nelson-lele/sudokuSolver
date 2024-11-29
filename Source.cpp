#include <iostream>
#include <thread>
#include <chrono>


struct Position {
	int row;
	int column;

	Position(int a, int b) : row(a), column(b){}
	Position(){}


	
};

int board[][9] = {
	{7,8,0,4,0,0,1,2,0},
	{6,0,0,0,7,5,0,0,9},
	{0,0,0,6,0,1,0,7,8},
	{0,0,7,0,4,0,2,6,0},
	{0,0,1,0,5,0,9,3,0},
	{9,0,4,0,6,0,0,0,5},
	{0,7,0,3,0,0,0,1,2},
	{1,2,0,0,0,7,4,0,0},
	{0,4,9,2,0,6,0,0,7}
};

void PrintBoard(int bo[][9]) {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i != 0) {
			std::cout << "_______________________\n";
		}
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0) {
				std::cout << " | " ;	
			}
		
			if (j == 0)
				std::cout << bo[i][j] << " ";
			else {
				
				std::cout << bo[i][j] << " ";
			
			}
		}
		std::cout << std::endl;
		
	}

}
Position FindEmptyPosition(int bo[][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (bo[i][j] == 0)
				return Position{ i,j };
		}
	}
	return Position{-1,-1};
}
bool IsValid(int bo[][9], int num, Position& po) {
	// check if no number in a row has appeared more than once
	for (int i = 0; i < 9; i++) {
		if (bo[po.row][i] == num && po.column != i)
			return false;

	}
	// check if no number in a column has appeared more than once
	for (int j = 0; j < 9; j++) {
		if (bo[j][po.column] == num && po.row != j)
			return false;
	}
	// calculate the squares of the board  
	int box_x = po.column / 3;
	int box_y = po.row / 3;
	// check if none of the number in a square appeared twice
	for (int i = box_y*3; i < box_y + 3; i++) {
		for (int j = box_x*3; j < box_x + 3; j++) {
			if (bo[i][j] == num && (i  != po.row && j != po.column))
				return false;
		}
	}
	return true;
}


bool Solve() {
	Position find;
	find = FindEmptyPosition(board);
	int row, col;
	row = find.row;
	col = find.column;
	if (find.column == -1 && find.row == -1) {
		return true;
	}
	
	for (int i = 1; i < 10; i++) {
		
		if (IsValid(board, i, find)) {
			board[row][col] = i;
			
			/*PrintBoard(board);*/
			//
			if (Solve()){
				return true;
			}
			board[row][col] = 0;
		}
	}
	return false;
}

int main() {


	PrintBoard(board);
	Solve();
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "_______________________________\n";
	std::cout << "Solving ..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	PrintBoard(board);
	

	std::cin.get();
}
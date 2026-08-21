#include <iostream>
using namespace std;

#define N 9

// Print the grid
void printGrid(int grid[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cout << grid[r][c] << " ";
            if ((c + 1) % 3 == 0 && c != 8) cout << "| ";
        }
        cout << endl;
        if ((r + 1) % 3 == 0 && r != 8) cout << "------+-------+------" << endl;
    }
}

// Check if placing num at grid[row][col] is valid
bool isValid(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Backtracking solver
bool solve(int grid[N][N]) {
    int row = -1, col = -1;
    bool isEmpty = false;

    for (int r = 0; r < N && !isEmpty; r++) {
        for (int c = 0; c < N && !isEmpty; c++) {
            if (grid[r][c] == 0) {
                row = r;
                col = c;
                isEmpty = true;
            }
        }
    }

    if (!isEmpty) return true;

    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            if (solve(grid))
                return true;

            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Input Sudoku:" << endl;
    printGrid(grid);
    cout << endl;

    if (solve(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
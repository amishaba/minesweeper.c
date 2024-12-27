#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <queue>
using namespace std;

class Minesweeper {
private:
    struct Cell {
        bool isMine;
        bool isRevealed;
        bool isFlagged;
        int adjacentMines;
        
        Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0) {}
    };
    
    vector<vector<Cell>> board;
    int rows, cols, mines;
    bool gameOver;
    int revealedCells;
    
    // Direction arrays for checking adjacent cells
    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    bool isValid(int x, int y) const {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    void placeMines(int firstX, int firstY) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> disX(0, rows - 1);
        uniform_int_distribution<> disY(0, cols - 1);
        
        int placedMines = 0;
        while (placedMines < mines) {
            int x = disX(gen);
            int y = disY(gen);
            
            // Don't place mine on first click or where a mine already exists
            if (!board[x][y].isMine && !(x == firstX && y == firstY)) {
                board[x][y].isMine = true;
                placedMines++;
                
                // Update adjacent mine counts
                for (int i = 0; i < 8; i++) {
                    int newX = x + dx[i];
                    int newY = y + dy[i];
                    if (isValid(newX, newY)) {
                        board[newX][newY].adjacentMines++;
                    }
                }
            }
        }
    }
    
    void revealCell(int x, int y) {
        if (!isValid(x, y) || board[x][y].isRevealed || board[x][y].isFlagged) {
            return;
        }
        
        board[x][y].isRevealed = true;
        revealedCells++;
        
        // If cell has no adjacent mines, reveal adjacent cells
        if (board[x][y].adjacentMines == 0 && !board[x][y].isMine) {
            for (int i = 0; i < 8; i++) {
                revealCell(x + dx[i], y + dy[i]);
            }
        }
    }

public:
    Minesweeper(int r, int c, int m) : rows(r), cols(c), mines(m), gameOver(false), revealedCells(0) {
        board = vector<vector<Cell>>(rows, vector<Cell>(cols));
    }
    
    bool makeMove(int x, int y, bool flag) {
        if (!isValid(x, y) || gameOver) {
            return false;
        }
        
        if (flag) {
            if (!board[x][y].isRevealed) {
                board[x][y].isFlagged = !board[x][y].isFlagged;
            }
            return true;
        }
        
        if (board[x][y].isFlagged) {
            return true;
        }
        
        // First move
        if (revealedCells == 0) {
            placeMines(x, y);
        }
        
        if (board[x][y].isMine) {
            gameOver = true;
            return false;
        }
        
        revealCell(x, y);
        return true;
    }
    
    bool hasWon() const {
        return revealedCells == (rows * cols - mines);
    }
    
    bool isGameOver() const {
        return gameOver;
    }
    
    void printBoard(bool showAll = false) const {
        // Print column numbers
        cout << "   ";
        for (int j = 0; j < cols; j++) {
            cout << j << " ";
        }
        cout << "\n   ";
        for (int j = 0; j < cols; j++) {
            cout << "--";
        }
        cout << "\n";
        
        for (int i = 0; i < rows; i++) {
            cout << i << "| ";
            for (int j = 0; j < cols; j++) {
                if (board[i][j].isFlagged && !showAll) {
                    cout << "F ";
                }
                else if (!board[i][j].isRevealed && !showAll) {
                    cout << ". ";
                }
                else if (board[i][j].isMine) {
                    cout << "* ";
                }
                else {
                    cout << (board[i][j].adjacentMines == 0 ? " " : to_string(board[i][j].adjacentMines)) << " ";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    int rows = 9, cols = 9, mines = 10;
    Minesweeper game(rows, cols, mines);
    
    cout << "Welcome to Minesweeper!\n";
    cout << "Enter moves as: row col [f]\n";
    cout << "Add 'f' to flag/unflag a cell\n\n";
    
    while (!game.isGameOver() && !game.hasWon()) {
        game.printBoard();
        
        int row, col;
        string flag;
        cout << "\nEnter move: ";
        cin >> row >> col;
        getline(cin, flag);
        
        bool isFlag = flag.find('f') != string::npos;
        if (!game.makeMove(row, col, isFlag)) {
            cout << "\nGame Over! You hit a mine!\n";
            game.printBoard(true);
            break;
        }
        
        if (game.hasWon()) {
            cout << "\nCongratulations! You've won!\n";
            game.printBoard(true);
        }
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
public:
    Minesweeper(int width, int height, int mines) 
        : width(width), height(height), mines(mines) {
        initializeBoard();
        placeMines();
        calculateAdjacentMines();
    }

    void playGame() { // add functionality to FLAG here
        bool gameOver = false;
        while (!gameOver) {
            printBoard();
            int x, y;
            cout << "Enter row and column to reveal (e.g., 1 1): ";
            cin >> x >> y;
            if (reveal(x - 1, y - 1)) {
                cout << "You hit a mine! Game Over. This is the minefield" << endl;
                for (int i =0;i<height;i++)
                {
                    for (int j =0; j<width;j++)
                    {
                        cout << board[i][j] << " ";
                    }
                    cout<<endl;
                }
                gameOver = true;
            } else {
                if (checkWin()) {
                    cout << "Congratulations! You've cleared the minefield!" << endl;
                    gameOver = true;
                }
            }
        }
    }

private:
    int width, height, mines;
    vector<vector<char>> board;
    vector<vector<char>> displayBoard;

    void initializeBoard() {
        board.resize(height, vector<char>(width, '0'));
        displayBoard.resize(height, vector<char>(width, '*'));
    }

    void placeMines() {
        srand(time(0));
        int placedMines = 0;
        while (placedMines < mines) {
            int x = rand() % height;
            int y = rand() % width;
            if (board[x][y] == '0') {
                board[x][y] = 'M';
                placedMines++;
            }
        }
    }

    void calculateAdjacentMines() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (board[i][j] == 'M') continue;
                int mineCount = 0;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int ni = i + x, nj = j + y;
                        if (ni >= 0 && ni < height && nj >= 0 && nj < width && board[ni][nj] == 'M') {
                            mineCount++;
                        }
                    }
                }
                board[i][j] = '0' + mineCount;
            }
        }
    }

    bool reveal(int x, int y) {
        if (x < 0 || x >= height || y < 0 || y >= width || displayBoard[x][y] != '*') {
            return false;
        }
        displayBoard[x][y] = board[x][y];
        if (board[x][y] == 'M') {
            return true;
        }
        if (board[x][y] == '0') {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx != 0 || dy != 0) {
                        reveal(x + dx, y + dy);
                    }
                }
            }
        }
        return false;
    }

    bool checkWin() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (displayBoard[i][j] == '*' && board[i][j] != 'M') {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard() {
        cout << "  ";
        for (int j = 0; j < width; ++j) {
            cout << j + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < height; ++i) {
            cout << i + 1 << " ";
            for (int j = 0; j < width; ++j) {
                cout << displayBoard[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int width, height, mines;
    cout << "Enter board width: ";
    cin >> width;
    cout << "Enter board height: ";
    cin >> height;
    cout << "Enter number of mines: ";
    cin >> mines;

    Minesweeper game(width, height, mines);
    game.playGame();

    return 0;
}

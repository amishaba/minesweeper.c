# minesweeper.c
# C++ Minesweeper

A console-based implementation of the classic Minesweeper game written in C++. This implementation features a clean, object-oriented design with a user-friendly interface and all the traditional Minesweeper gameplay mechanics.

## Features

- Classic Minesweeper gameplay
- Configurable board size and number of mines
- First-click protection (first move is always safe)
- Cell flagging system
- Automatic cell revelation for empty regions
- Clear console-based visualization
- Input validation and error handling

## Requirements

- C++ compiler with C++11 support
- Standard Template Library (STL)
- Console/Terminal that supports basic text output

## Building and Running

To compile the game, use any C++ compiler that supports C++11 or later. For example:

```bash
g++ minesweeper.cpp -o minesweeper
```

To run the game:

```bash
./minesweeper
```

## How to Play

1. The game starts with a grid of unrevealed cells, where mines are hidden
2. Enter moves by typing the row number, followed by the column number
3. To flag/unflag a potential mine, add 'f' after the coordinates

### Input Format
- Regular move: `row col` (e.g., `3 4`)
- Flag move: `row col f` (e.g., `3 4 f`)

### Game Symbols
- `.` - Unrevealed cell
- `F` - Flagged cell
- `*` - Mine (shown when game is over)
- ` ` (space) - Revealed empty cell
- `1-8` - Number of adjacent mines



## Customization

You can modify the game parameters in `main()`:
```cpp
int rows = 9;    // Number of rows
int cols = 9;    // Number of columns
int mines = 10;  // Number of mines
```

## Winning Condition

The game is won when all non-mine cells are revealed. The game is lost if a mine is revealed.



## Future Enhancements

Planned features for future releases:
- Timer functionality
- Game statistics
- Custom board configurations
- Improved UI with color support
- Save/load game states

# Tetris Game 🎮

A console-based Tetris Game with customizable settings. The game includes all the standard tetromino pieces, game mechanics such as line clearing, scoring, and increasing difficulty as the game progresses.

## Features

- **Tetromino Pieces**  Can implement all seven standard tetrominoes (I, O, T, S, Z, J, L).
- **Grid Representation** The game board is a 10x20 grid.
- **Piece Movement** Players can move left, move right, rotate, and drop pieces.
- **Gravity** Tetrominoes fall at a constant speed, increasing as the game progresses.
- **Collision Detection** Prevent blocks from overlapping or moving out of bounds.
- **Line Clearing** Removes full rows and shifts the grid downwards.
- **Scoring System** Award points for cleared lines.

## Controls
- Left Arrow (←): Move left
- Right Arrow (→): Move right
- Up Arrow (↑): Rotate piece
- Down Arrow (↓): Soft drop
- Spacebar: Hard drop
- Escape (ESC): Pause or Quit


## Installation and Execution 

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/snake-game.git
   cd snake-game
   ```

2. **Compile the Code:**
   ```sh
   g++ snake_game.cpp -o snake_game
   ```
3. **Run the Game:**
   ```sh
   ./snake_game
   ```

## Requirements

 A C++ compiler 


## How to Play

1.Start the game and a random tetromino appears at the top of the 10x20 grid.
2.The player moves and rotates the piece to fit within the grid.
3.When a horizontal row is completely filled, it is cleared, and the above rows shift down.
4.The score increases based on the number of lines cleared at once:
    1 line: 40 points × (current level + 1)
    2 lines: 100 points × (current level + 1)
    3 lines: 300 points × (current level + 1)
    4 lines (Tetris): 1200 points × (current level + 1)
5.The game speeds up as the player progresses, making it more challenging.
6.The game ends when the pieces stack to the top of the grid.


## Data Structure Analysis

- **4D Arrays:** Used to store the tetrominoes
- **Score, Level, and Speed Management:** Stored as integer variables that dynamically update based on cleared lines.
- **Current Tetromino and Next Tetromino:** Tracks the falling piece and preloads the next piece for better UX ,respectively.
- **2D Vector:** Represents the grid.

## Object-Oriented Programming (OOPs)

-  **Encapsulation:** Game elements like console display, tetromino piece, and the main game portion is encapsulated in classes.
-  **Abstraction:** Hides complex game logic behind simple interfaces.

## Contributions

Feel free to contribute by adding new features like :
    -Hold Piece: Allow players to store a tetromino for later use.
    -Ghost Piece: Show where the tetromino will land.
    -Multiplayer Mode: Implement competitive or cooperative gameplay.

### Contributors
- Mrunali Parmar - 202401122
- Manya Rana - 202401115

---

Enjoy the game!


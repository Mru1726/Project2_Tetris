#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#ifdef _WIN32
    #include <conio.h> // For Windows-specific input handling
    #define CLEAR_SCREEN "cls"
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    
    int getch() { // Linux/macOS alternative to _getch()
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

enum class TetrominoType { I, O, T, S, Z, J, L, NONE };

struct Point {
    int x, y;
};

class Tetromino {
public:
    TetrominoType type;
    std::vector<Point> blocks;
    int rotation;

    Tetromino(TetrominoType type);
    void rotate();
    void move(int dx, int dy);
    std::vector<Point> getRotatedShape() const;
    std::vector<Point> getMovedShape(int dx, int dy) const;
    std::string getColorCode() const;

private:
    static const std::vector<std::vector<Point>> baseShapes;
};

const std::vector<std::vector<Point>> Tetromino::baseShapes = {
    {{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }}, // I
    {{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }}, // O
    {{ {0, 0}, {1, 0}, {2, 0}, {1, 1} }}, // T
    {{ {1, 0}, {2, 0}, {0, 1}, {1, 1} }}, // S
    {{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }}, // Z
    {{ {0, 0}, {0, 1}, {1, 1}, {2, 1} }}, // J
    {{ {2, 0}, {0, 1}, {1, 1}, {2, 1} }}  // L
};

Tetromino::Tetromino(TetrominoType type) : type(type), rotation(0) {
    if (type != TetrominoType::NONE) {
        blocks = baseShapes[(int)type];
    }
}

void Tetromino::rotate() {
    std::vector<Point> rotatedBlocks;
    for (const auto& block : blocks) {
        rotatedBlocks.push_back({ -block.y, block.x }); // 90-degree rotation formula
    }
    blocks = rotatedBlocks;
}

void Tetromino::move(int dx, int dy) {
    for (auto& block : blocks) {
        block.x += dx;
        block.y += dy;
    }
}

std::vector<Point> Tetromino::getMovedShape(int dx, int dy) const {
    std::vector<Point> movedBlocks;
    for (const auto& block : blocks) {
        movedBlocks.push_back({ block.x + dx, block.y + dy });
    }
    return movedBlocks;
}

class TetrisGame {
public:
    TetrisGame();
    void run();
private:
    std::vector<std::vector<char>> grid;
    Tetromino currentPiece;
    int score, level, linesCleared;
    float fallSpeed;
    bool gameOver, paused;

    void initializeGame();
    void generateNewPiece();
    void updateGrid();
    void drawGrid();
    void handleInput();
    void movePieceLeft();
    void movePieceRight();
    void movePieceDown();
    void hardDrop();
    bool rotatePiece();
    bool checkCollision(const std::vector<Point>& blocks) const;
    void clearLines();
    void updateScore(int lines);
    void updateLevel();
    void checkGameOver();
    void pauseGame();
    TetrominoType getRandomPieceType();

    static const int GRID_WIDTH = 10;
    static const int GRID_HEIGHT = 20;
};

TetrisGame::TetrisGame() 
    : grid(GRID_HEIGHT, std::vector<char>(GRID_WIDTH, ' ')), 
      score(0), level(1), linesCleared(0), fallSpeed(0.8f), gameOver(false), paused(false), 
      currentPiece(Tetromino(TetrominoType::NONE)) {
    initializeGame();
}

void TetrisGame::initializeGame() {
    grid.assign(GRID_HEIGHT, std::vector<char>(GRID_WIDTH, ' '));
    generateNewPiece();
}

TetrominoType TetrisGame::getRandomPieceType() {
    return static_cast<TetrominoType>(std::rand() % 7);
}

void TetrisGame::generateNewPiece() {
    currentPiece = Tetromino(getRandomPieceType());
    if (checkCollision(currentPiece.blocks)) {
        gameOver = true;
    }
}

bool TetrisGame::checkCollision(const std::vector<Point>& blocks) const {
    for (const auto& block : blocks) {
        if (block.x < 0 || block.x >= GRID_WIDTH || block.y >= GRID_HEIGHT) {
            return true;
        }
        if (grid[block.y][block.x] != ' ') {
            return true;
        }
    }
    return false;
}

void TetrisGame::run() {
    std::cout << "Press any key to start...\n";
    getch();

    while (!gameOver) {
        handleInput();
        updateGrid();
        drawGrid();
        #ifdef _WIN32
            Sleep(50);
        #else
            usleep(50000);
        #endif
    }

    std::cout << "Game Over! Score: " << score << std::endl;
}

void TetrisGame::drawGrid() {
    system(CLEAR_SCREEN);
    std::cout << "Score: " << score << " Level: " << level << "\n";
    for (const auto& row : grid) {
        std::cout << "|";
        for (char cell : row) {
            std::cout << (cell == '#' ? "[]" : "  ");
        }
        std::cout << "|\n";
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    TetrisGame game;
    game.run();
    return 0;
}

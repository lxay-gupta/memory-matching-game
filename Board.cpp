#include "Board.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

Board::Board() : size(4) {
    initializeBoard();
}

Board::Board(int size) : size(size) {
    initializeBoard();
}

int Board::getSize() const {
    return size;
}

void Board::initializeBoard() {
    int totalCards = size * size;
    int numPairs = totalCards / 2;

    std::vector<int> values;
    for (int i = 1; i <= numPairs; ++i) {
        values.push_back(i);
        values.push_back(i);
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(values.begin(), values.end(), std::default_random_engine(seed));

    grid.assign(size, std::vector<Card>(size));
    int valueIndex = 0;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            grid[r][c] = {values[valueIndex++], false, false};
        }
    }
}

void Board::displayBoard() const {
    std::cout << "\n     ";
    for (int c = 0; c < size; ++c) {
        std::cout << std::setw(4) << c + 1 << " ";
    }
    std::cout << "\n";

    std::cout << "     ";
    for (int c = 0; c < size; ++c) {
        std::cout << "-----";
    }
    std::cout << "-\n";

    for (int r = 0; r < size; ++r) {
        std::cout << std::setw(3) << r + 1 << " |";
        for (int c = 0; c < size; ++c) {
            if (grid[r][c].isRevealed || grid[r][c].isMatched) {
                std::cout << " " << std::setw(3) << grid[r][c].value << "|";
            } else {
                std::cout << " " << std::setw(3) << "*" << "|";
            }
        }
        std::cout << "\n";

        std::cout << "     ";
        for (int c = 0; c < size; ++c) {
            std::cout << "-----";
        }
        std::cout << "-\n";
    }
    std::cout << std::endl;
}

bool Board::isRevealed(int r, int c) const {
    return grid[r][c].isRevealed;
}

bool Board::isMatched(int r, int c) const {
    return grid[r][c].isMatched;
}

int Board::getValue(int r, int c) const {
    return grid[r][c].value;
}

void Board::revealCard(int r, int c) {
    grid[r][c].isRevealed = true;
}

void Board::hideCard(int r, int c) {
    grid[r][c].isRevealed = false;
}

void Board::setMatched(int r, int c) {
    grid[r][c].isMatched = true;
}

bool Board::isValidCoordinates(int r, int c) const {
    return r >= 0 && r < size && c >= 0 && c < size;
}

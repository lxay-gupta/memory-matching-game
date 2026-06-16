#ifndef BOARD_H
#define BOARD_H

#include <vector>

struct Card {
    int value;
    bool isRevealed;
    bool isMatched;
};

class Board {
private:
    int size;
    std::vector<std::vector<Card>> grid;

public:
    Board();
    Board(int size);

    int getSize() const;
    void initializeBoard();
    void displayBoard() const;

    bool isRevealed(int r, int c) const;
    bool isMatched(int r, int c) const;
    int getValue(int r, int c) const;

    void revealCard(int r, int c);
    void hideCard(int r, int c);
    void setMatched(int r, int c);

    bool isValidCoordinates(int r, int c) const;
};

#endif

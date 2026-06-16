#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "ScoreManager.h"
#include <string>
#include <vector>

class Game {
private:
    std::vector<Player> players;
    ScoreManager scoreManager;
    bool isTwoPlayer;

    void displayWelcomeScreen() const;
    void displayMainMenu();
    void viewInstructions() const;
    void startNewGame();
    void handleGameplay(Board& board);
    void getCoordinatesInput(const Board& board, int& r, int& c, const std::string& prompt, int excludeR = -1, int excludeC = -1);

public:
    Game();
    void run();
};

#endif

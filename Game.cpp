#include "Game.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <iomanip>
#include <algorithm>

Game::Game() : scoreManager("highscores.txt"), isTwoPlayer(false) {}

void Game::run() {
    displayWelcomeScreen();
    displayMainMenu();
}

void Game::displayWelcomeScreen() const {
    std::cout << "\n";
    std::cout << "=========================================================\n";
    std::cout << "||                                                     ||\n";
    std::cout << "||             WELCOME TO MEMORY MATCHING GAME         ||\n";
    std::cout << "||                                                     ||\n";
    std::cout << "=========================================================\n";
    std::cout << "  A C++ project illustrating basic Data Structures and\n";
    std::cout << "  Algorithms: Vector representation, Shuffling, and File IO.\n";
    std::cout << "=========================================================\n\n";
}

void Game::displayMainMenu() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "=== MAIN MENU ===\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. View Instructions\n";
        std::cout << "3. View High Scores\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter a number between 1 and 4.\n\n";
            continue;
        }

        switch (choice) {
            case 1:
                startNewGame();
                break;
            case 2:
                viewInstructions();
                break;
            case 3:
                scoreManager.displayHighScores();
                break;
            case 4:
                std::cout << "\nThank you for playing Memory Matching Game! Goodbye.\n";
                break;
            default:
                std::cout << "\nInvalid choice. Select from 1 to 4.\n\n";
        }
    }
}

void Game::viewInstructions() const {
    std::cout << "\n=========================================================\n";
    std::cout << "                       INSTRUCTIONS                      \n";
    std::cout << "=========================================================\n";
    std::cout << "1. Choose Single-Player or Two-Player mode.\n";
    std::cout << "2. Choose a difficulty level (board size):\n";
    std::cout << "   - Easy: 4x4 (8 pairs)\n";
    std::cout << "   - Medium: 8x8 (32 pairs)\n";
    std::cout << "   - Hard: 16x16 (128 pairs)\n";
    std::cout << "3. The grid displays all cards hidden as '*'.\n";
    std::cout << "4. Turn Gameplay:\n";
    std::cout << "   - Enter coordinates (row col) to flip two cards.\n";
    std::cout << "   - If they match, you get a point and another turn!\n";
    std::cout << "   - If they mismatch, the turn passes to the next player.\n";
    std::cout << "5. Complete the board to save results and view the winner.\n";
    std::cout << "=========================================================\n";
    std::cout << "\nPress Enter to return to the Main Menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Game::startNewGame() {
    players.clear();

    int mode = 0;
    while (true) {
        std::cout << "\nSelect Game Mode:\n";
        std::cout << "1. Single-Player\n";
        std::cout << "2. Two-Player\n";
        std::cout << "Enter choice: ";
        if (std::cin >> mode) {
            if (mode == 1) {
                isTwoPlayer = false;
                break;
            } else if (mode == 2) {
                isTwoPlayer = true;
                break;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid mode selection. Choose 1 or 2.\n";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear stream buffer
    if (!isTwoPlayer) {
        std::string name;
        std::cout << "\nEnter player name: ";
        std::getline(std::cin, name);
        if (name.empty()) name = "Player";
        players.push_back(Player(name));
    } else {
        std::string name1, name2;
        std::cout << "\nEnter Player 1 name: ";
        std::getline(std::cin, name1);
        if (name1.empty()) name1 = "Player 1";
        
        std::cout << "Enter Player 2 name: ";
        std::getline(std::cin, name2);
        if (name2.empty()) name2 = "Player 2";

        players.push_back(Player(name1));
        players.push_back(Player(name2));
    }

    int diff = 0;
    int boardSize = 4;
    std::string diffLabel = "Easy";
    
    while (true) {
        std::cout << "\nChoose Difficulty:\n";
        std::cout << "1. Easy (4x4 board, 8 pairs)\n";
        std::cout << "2. Medium (8x8 board, 32 pairs)\n";
        std::cout << "3. Hard (16x16 board, 128 pairs)\n";
        std::cout << "Enter choice: ";
        
        if (std::cin >> diff) {
            if (diff == 1) {
                boardSize = 4;
                diffLabel = "Easy";
                break;
            } else if (diff == 2) {
                boardSize = 8;
                diffLabel = "Medium";
                break;
            } else if (diff == 3) {
                boardSize = 16;
                diffLabel = "Hard";
                break;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid difficulty. Choose 1, 2, or 3.\n";
    }

    Board board(boardSize);
    std::cout << "\nGenerating a random board...\n";
    
    auto startTime = std::chrono::steady_clock::now();

    handleGameplay(board);

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    double timeSeconds = elapsed.count();
    
    // Distribute timeTaken equally or individually
    for (auto& p : players) {
        p.setTimeTaken(timeSeconds);
        
        int totalPairs = (boardSize * boardSize) / 2;
        int baseScore = totalPairs * 50;
        int penalty = (p.getMoves() * 10) + static_cast<int>(timeSeconds * 2);
        int finalScore = std::max(10, baseScore - penalty);
        p.addScore(finalScore);

        ScoreRecord record;
        record.name = p.getName();
        record.difficulty = diffLabel;
        record.moves = p.getMoves();
        record.timeTaken = timeSeconds;
        record.score = p.getScore();
        scoreManager.addScore(record);
    }

    // Display Congratulatory Screen
    std::cout << "\n=========================================================\n";
    std::cout << "                    GAME OVER RESULTS                    \n";
    std::cout << "=========================================================\n";
    std::cout << "Difficulty:  " << diffLabel << "\n";
    std::cout << "Time Taken:  " << std::fixed << std::setprecision(1) << timeSeconds << " seconds\n";
    std::cout << "---------------------------------------------------------\n";

    if (!isTwoPlayer) {
        std::cout << "Player:      " << players[0].getName() << "\n";
        std::cout << "Total Moves: " << players[0].getMoves() << "\n";
        std::cout << "Matches:     " << players[0].getMatches() << "\n";
        std::cout << "Final Score: " << players[0].getScore() << "\n";
    } else {
        std::cout << std::left << std::setw(15) << "Player Name"
                  << std::setw(10) << "Moves"
                  << std::setw(10) << "Matches"
                  << "Score\n";
        std::cout << "---------------------------------------------------------\n";
        for (const auto& p : players) {
            std::cout << std::left << std::setw(15) << p.getName().substr(0, 13)
                      << std::setw(10) << p.getMoves()
                      << std::setw(10) << p.getMatches()
                      << p.getScore() << "\n";
        }
        std::cout << "---------------------------------------------------------\n";

        // Declare Winner
        if (players[0].getMatches() > players[1].getMatches()) {
            std::cout << "Winner: " << players[0].getName() << " 🎉\n";
        } else if (players[1].getMatches() > players[0].getMatches()) {
            std::cout << "Winner: " << players[1].getName() << " 🎉\n";
        } else {
            // Tie-breaker by fewer moves
            if (players[0].getMoves() < players[1].getMoves()) {
                std::cout << "Winner (Tie-break by fewer moves): " << players[0].getName() << " 🎉\n";
            } else if (players[1].getMoves() < players[0].getMoves()) {
                std::cout << "Winner (Tie-break by fewer moves): " << players[1].getName() << " 🎉\n";
            } else {
                std::cout << "It's a complete Draw! Both players played exceptionally well.\n";
            }
        }
    }
    std::cout << "=========================================================\n";
    std::cout << "\nScores have been saved to the high scores list!\n";
    std::cout << "\nPress Enter to return to the Main Menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Game::getCoordinatesInput(const Board& board, int& r, int& c, const std::string& prompt, int excludeR, int excludeC) {
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> r >> c)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input format. Please enter two integers (row and column).\n";
            continue;
        }

        r--;
        c--;

        if (!board.isValidCoordinates(r, c)) {
            std::cout << "Coordinates out of bounds! Choose numbers between 1 and " << board.getSize() << ".\n";
        } else if (board.isMatched(r, c)) {
            std::cout << "This card has already been matched! Select another card.\n";
        } else if (board.isRevealed(r, c) || (r == excludeR && c == excludeC)) {
            std::cout << "This card is already revealed! Select another card.\n";
        } else {
            break;
        }
    }
}

void Game::handleGameplay(Board& board) {
    int totalPairs = (board.getSize() * board.getSize()) / 2;
    int matchesFound = 0;
    int activePlayerIdx = 0;

    while (matchesFound < totalPairs) {
        board.displayBoard();
        
        std::string nameHeader = " [Turn: " + players[activePlayerIdx].getName() + "] ";
        std::cout << "=== " << nameHeader << " ===\n";

        int r1, c1;
        getCoordinatesInput(board, r1, c1, "Enter Row and Column for card 1: ");
        
        board.revealCard(r1, c1);
        board.displayBoard();
        std::cout << "=== " << nameHeader << " ===\n";

        int r2, c2;
        getCoordinatesInput(board, r2, c2, "Enter Row and Column for card 2: ", r1, c1);
        
        board.revealCard(r2, c2);
        board.displayBoard();

        players[activePlayerIdx].incrementMoves();

        if (board.getValue(r1, c1) == board.getValue(r2, c2)) {
            board.setMatched(r1, c1);
            board.setMatched(r2, c2);
            matchesFound++;
            players[activePlayerIdx].incrementMatches();
            players[activePlayerIdx].addScore(10);
            std::cout << "Match found! Card " << board.getValue(r1, c1) << " matches.\n";
            if (matchesFound < totalPairs) {
                std::cout << players[activePlayerIdx].getName() << " gets another turn!\n";
            }
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        } else {
            std::cout << "No match! Card 1 was: " << board.getValue(r1, c1) 
                      << ", Card 2 was: " << board.getValue(r2, c2) << ".\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            
            board.hideCard(r1, c1);
            board.hideCard(r2, c2);

            // Alternate turn
            if (isTwoPlayer) {
                activePlayerIdx = (activePlayerIdx + 1) % players.size();
            }
        }
    }
}

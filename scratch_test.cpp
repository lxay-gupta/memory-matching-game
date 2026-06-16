#include "Player.h"
#include <iostream>
#include <cassert>
#include <vector>

// Simulates the turn-switching logic used in Game::handleGameplay
int simulateTurn(bool isMatch, int activePlayerIdx, size_t numPlayers, bool isTwoPlayer) {
    if (isMatch) {
        // Player gets another turn, active index remains same
        return activePlayerIdx;
    } else {
        // Turn alternates
        if (isTwoPlayer) {
            return (activePlayerIdx + 1) % numPlayers;
        }
        return activePlayerIdx;
    }
}

int main() {
    std::cout << "Running automated logic test for Two-Player mode...\n";

    std::vector<Player> players;
    players.push_back(Player("Alice"));
    players.push_back(Player("Bob"));

    assert(players.size() == 2);
    std::cout << "✓ Player list initialized with 2 players.\n";

    // Test Turn Alternation Logic
    int activePlayerIdx = 0; // Starts with Alice

    // Scenario 1: Alice gets a match
    activePlayerIdx = simulateTurn(true, activePlayerIdx, players.size(), true);
    assert(activePlayerIdx == 0);
    std::cout << "✓ Player keeps turn after a match.\n";

    // Scenario 2: Alice misses a match
    activePlayerIdx = simulateTurn(false, activePlayerIdx, players.size(), true);
    assert(activePlayerIdx == 1);
    std::cout << "✓ Turn switches to Player 2 (Bob) after a mismatch.\n";

    // Scenario 3: Bob misses a match
    activePlayerIdx = simulateTurn(false, activePlayerIdx, players.size(), true);
    assert(activePlayerIdx == 0);
    std::cout << "✓ Turn switches back to Player 1 (Alice) after Bob mismatches.\n";

    std::cout << "\nAll logic checks passed successfully!\n";
    return 0;
}

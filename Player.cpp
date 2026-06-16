#include "Player.h"

Player::Player() : name("Guest"), moves(0), matches(0), score(0), timeTaken(0.0) {}

Player::Player(const std::string& name) : name(name), moves(0), matches(0), score(0), timeTaken(0.0) {}

std::string Player::getName() const { return name; }
int Player::getMoves() const { return moves; }
int Player::getMatches() const { return matches; }
int Player::getScore() const { return score; }
double Player::getTimeTaken() const { return timeTaken; }

void Player::setName(const std::string& newName) { name = newName; }
void Player::incrementMoves() { moves++; }
void Player::incrementMatches() { matches++; }
void Player::addScore(int points) { score += points; }
void Player::setTimeTaken(double duration) { timeTaken = duration; }
void Player::reset() {
    moves = 0;
    matches = 0;
    score = 0;
    timeTaken = 0.0;
}

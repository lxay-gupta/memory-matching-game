#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int moves;
    int matches;
    int score;
    double timeTaken;

public:
    Player();
    Player(const std::string& name);

    std::string getName() const;
    int getMoves() const;
    int getMatches() const;
    int getScore() const;
    double getTimeTaken() const;

    void setName(const std::string& newName);
    void incrementMoves();
    void incrementMatches();
    void addScore(int points);
    void setTimeTaken(double duration);
    void reset();
};

#endif

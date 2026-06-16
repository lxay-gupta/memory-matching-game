#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <vector>

struct ScoreRecord {
    std::string name;
    std::string difficulty;
    int moves;
    double timeTaken;
    int score;
};

class ScoreManager {
private:
    std::string filename;
    std::vector<ScoreRecord> scores;

    void loadScores();
    void saveScores();

public:
    ScoreManager();
    ScoreManager(const std::string& filepath);

    void addScore(const ScoreRecord& record);
    void displayHighScores() const;
};

#endif

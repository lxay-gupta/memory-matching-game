#include "ScoreManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>

ScoreManager::ScoreManager() : filename("highscores.txt") {
    loadScores();
}

ScoreManager::ScoreManager(const std::string& filepath) : filename(filepath) {
    loadScores();
}

void ScoreManager::loadScores() {
    scores.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string name, difficulty, movesStr, timeStr, scoreStr;

        if (std::getline(ss, name, '|') &&
            std::getline(ss, difficulty, '|') &&
            std::getline(ss, movesStr, '|') &&
            std::getline(ss, timeStr, '|') &&
            std::getline(ss, scoreStr, '|')) {
            try {
                ScoreRecord rec;
                rec.name = name;
                rec.difficulty = difficulty;
                rec.moves = std::stoi(movesStr);
                rec.timeTaken = std::stod(timeStr);
                rec.score = std::stoi(scoreStr);
                scores.push_back(rec);
            } catch (...) {
                // Ignore corrupt lines
            }
        }
    }
    file.close();

    std::sort(scores.begin(), scores.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
        if (a.score != b.score) return a.score > b.score;
        if (a.moves != b.moves) return a.moves < b.moves;
        return a.timeTaken < b.timeTaken;
    });
}

void ScoreManager::saveScores() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filename << " to write scores.\n";
        return;
    }

    for (const auto& rec : scores) {
        file << rec.name << "|"
             << rec.difficulty << "|"
             << rec.moves << "|"
             << rec.timeTaken << "|"
             << rec.score << "|\n";
    }
    file.close();
}

void ScoreManager::addScore(const ScoreRecord& record) {
    scores.push_back(record);
    std::sort(scores.begin(), scores.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
        if (a.score != b.score) return a.score > b.score;
        if (a.moves != b.moves) return a.moves < b.moves;
        return a.timeTaken < b.timeTaken;
    });

    if (scores.size() > 10) {
        scores.resize(10);
    }
    saveScores();
}

void ScoreManager::displayHighScores() const {
    std::cout << "\n=========================================================\n";
    std::cout << "                      HIGH SCORES                        \n";
    std::cout << "=========================================================\n";
    std::cout << std::left << std::setw(5) << "Rank"
              << std::setw(20) << "Name"
              << std::setw(12) << "Difficulty"
              << std::setw(8) << "Moves"
              << std::setw(10) << "Time (s)"
              << "Score\n";
    std::cout << "---------------------------------------------------------\n";

    if (scores.empty()) {
        std::cout << "               No high scores recorded yet!              \n";
    } else {
        int rank = 1;
        for (const auto& rec : scores) {
            std::cout << std::left << std::setw(5) << rank++
                      << std::setw(20) << rec.name.substr(0, 18)
                      << std::setw(12) << rec.difficulty
                      << std::setw(8) << rec.moves
                      << std::setw(10) << std::fixed << std::setprecision(1) << rec.timeTaken
                      << rec.score << "\n";
        }
    }
    std::cout << "=========================================================\n";
    std::cout << "\nPress Enter to return to the Main Menu...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

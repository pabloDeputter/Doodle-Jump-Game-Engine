//
// Created by Pablo Deputter on 13/12/2021.
//

#ifndef DOODLEJUMP_HIGHSCORE_H
#define DOODLEJUMP_HIGHSCORE_H

#include "util/Exception.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

struct HighScoreScore
{
        unsigned int mScore;
        std::string mName;

        HighScoreScore() : mScore(0), mName(std::string()) {}

        HighScoreScore(unsigned int score, std::string name) : mScore(score), mName(std::move(name)) {}

        virtual ~HighScoreScore() = default;

        [[nodiscard]] std::string toString() const { return mName + " - " + std::to_string(mScore); }

        friend std::ostream& operator<<(std::ostream& os, const HighScoreScore& score)
        {
                os << score.mName << " - " << score.mScore << "\n";
                return os;
        }
};

class HighScore
{
private:
        std::string mPath;
        unsigned int mQuantity;
        std::vector<std::shared_ptr<HighScoreScore>> mScores;

        HighScore() = default;

        HighScore(std::string path, unsigned int quantity) : mPath(path), mQuantity(quantity)
        {
                try {
                        load();
                } catch (const std::exception& exc) {
                        std::cerr << exc.what();
                }
        }

public:
        HighScore(const HighScore&) = delete;

        HighScore& operator=(const HighScore&) = delete;

        ~HighScore() { save(); }

        static HighScore& getInstance();

        void load();

        void save();

        void add(const std::shared_ptr<HighScoreScore>& score);

        [[nodiscard]] const std::vector<std::shared_ptr<HighScoreScore>>& getScores() const { return mScores; }

        [[nodiscard]] unsigned int getHighScore() const
        {
                if (mScores.empty()) {
                        return 0;
                }
                return mScores.front()->mScore;
        }
};

#endif // DOODLEJUMP_HIGHSCORE_H

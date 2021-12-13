//
// Created by Pablo Deputter on 13/12/2021.
//

#include "HighScore.h"

HighScore& HighScore::getInstance()
{
        static HighScore instance(
            "/Users/pablodeputter/Documents/GitHub/Advanced-Programming-DoodleJump/resource/highscore.txt", 10);
        return instance;
}

void HighScore::load()
{
        std::ifstream file(mPath);
        // If file can't be opened, throw exception and return
        if (!file.is_open()) {
                throw(Utils::FileException(std::move(mPath), "HighScore"));
                return;
        }
        // Read file
        std::string line;
        while (std::getline(file, line)) {
                // Find name and score in line
                std::string name = line.substr(0, line.find(" -"));
                line.erase(0, line.find(" -") + 2);
                std::string score = line.substr(1, line.find('-'));
                // Create new score
                std::shared_ptr<HighScoreScore> newScore = std::make_shared<HighScoreScore>(std::stoi(score), name);
                add(newScore);
        }
        file.close();
}

void HighScore::save()
{
        std::ofstream file(mPath);
        // If file can't be opened, throw exception and return
        if (!file.is_open()) {
                throw(Utils::FileException(std::move(mPath), "HighScore"));
                return;
        }
        // Write to file
        for (const auto& i : mScores) {
                file << *i;
        }
        file.close();
}

void HighScore::add(const std::shared_ptr<HighScoreScore>& score)
{
        // If new Score is less or equal to last score, return
        if (mScores.size() == mQuantity && mScores.back()->mScore >= score->mScore) {
                return;
        }

        // Find index to insert new score
        auto index = std::lower_bound(
            std::begin(mScores), std::end(mScores), score,
            [](const std::shared_ptr<HighScoreScore>& lhs, const std::shared_ptr<HighScoreScore>& rhs) -> bool {
                    // Return true if lhs's score is greater than rhs's
                    return lhs->mScore > rhs->mScore;
            });
        // Insert new score at right index
        mScores.insert(index, score);

        // Remove last element if mScores exceed quantity
        if (mScores.size() > mQuantity) {
                mScores.erase(std::end(mScores) - 1);
        }
}

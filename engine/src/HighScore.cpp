//
// Created by Pablo Deputter on 13/12/2021.
//

#include "HighScore.h"

#include <algorithm>

HighScore& HighScore::getInstance()
{
        static HighScore instance("resource/config.json", 10);
        return instance;
}

void HighScore::load()
{
        // Open file as input
        json j;
        std::ifstream file(mPath);
        // If file can't be opened, throw exception and return
        if (!file.is_open()) {
                throw(Utils::FileException(std::move(mPath), "HighScore"));
                return;
        }
        // Read data into json
        file >> j;
        // Close file
        file.close();
        // Find scores element in json
        json scores = j["scores"];
        auto it = std::begin(scores);
        while (it != std::end(scores)) {
                // Create new Score and add this to std::vector
                const std::string name = (*it)["name"];
                const int score = (*it)["score"];
                std::shared_ptr<HighScoreData> newScore = std::make_shared<HighScoreData>(score, name);
                add(newScore);
                it++;
        }
}

json HighScore::save()
{
        // Create new json array
        json scores = json::array();
        for (const auto& i : mScores) {
                // Create new score json element
                json score;
                score["name"] = i->mName;
                score["score"] = i->mScore;
                scores.emplace_back(score);
        }
        json j;
        j["scores"] = scores;
        //        std::ofstream file(mPath);
        //        file << j.dump(4);
        //        file.close();
        return j;
}

int HighScore::add(const std::shared_ptr<HighScoreData>& score)
{
        // If new Score is less or equal to last score, return
        if (mScores.size() == mQuantity && mScores.back()->mScore >= score->mScore) {
                return 11;
        }

        // Find index to insert new score
        auto index = std::lower_bound(
            std::begin(mScores), std::end(mScores), score,
            [](const std::shared_ptr<HighScoreData>& lhs, const std::shared_ptr<HighScoreData>& rhs) -> bool {
                    // Return true if lhs's score is greater than rhs's
                    return lhs->mScore > rhs->mScore;
            });
        // Insert new score at right index
        mScores.insert(index, score);

        // Remove last element if mScores exceed quantity
        if (mScores.size() > mQuantity) {
                mScores.erase(std::end(mScores) - 1);
        }
        // Find index of new element added
        for (int i = 0; i < mScores.size(); i++) {
                if (mScores[i] == score) {
                        return i;
                }
        }
        // Not found
        return -1;
}

//[[maybe_unused]] int HighScore::getHighScore() const
//{
//        // If no scores are stored high score is equal to 0
//        if (mScores.empty()) {
//                return 0;
//        }
//        return mScores.front()->mScore;
//}

bool HighScore::isHighScore(int score) const
{
        // If stored high scores does not exceed capacity new score is automatically a new high score
        // Else check if it is higher than the lowest high score
        if (mScores.size() < mQuantity || score > mScores.back()->mScore) {
                return true;
        }
        return false;
}

void HighScore::changeName(const std::string& newName, unsigned int index)
{
        if (index < 0 || index > mScores.size()) {
                return;
        }
        mScores[index]->mName = newName;
}

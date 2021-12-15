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
#include <utility>
#include <vector>

/**
 * Struct for High Score data
 */
struct HighScoreData
{
public:
        int mScore;        /**< Score */
        std::string mName; /**< Name of Player who achieve the High Score */

public:
        /**
         * @brief Constructor for HighScoreData object
         */
        HighScoreData() : mScore(0), mName(std::string()) {}
        /**
         * @brief Constructor for HighScoreData object
         * @param score int - score achieved
         * @param name std::string - name of Player
         */
        HighScoreData(int score, std::string name) : mScore(score), mName(std::move(name)) {}
        /**
         * @brief Default destructor of HighScoreData object
         */
        virtual ~HighScoreData() = default;
        /**
         * @brief Convert data to std::string
         * @return std::string - HighScore in std::string form
         */
        [[nodiscard]] std::string toString() const { return mName + " - " + std::to_string(mScore); }
        /**
         * @brief Overloaded << operator, implemented to write to file
         * @param os std::ostream
         * @param score HighScoreData - to be written
         * @return std::ostream
         */
        friend std::ostream& operator<<(std::ostream& os, const HighScoreData& score)
        {
                os << score.mName << " - " << score.mScore << "\n";
                return os;
        }
};

/**
 * @brief Class for HighScore implemented using singleton pattern
 */
class HighScore
{
private:
        std::string mPath;                                   /**< Path to High Score file */
        unsigned int mQuantity;                              /**< Amount of high scores to be stored */
        std::vector<std::shared_ptr<HighScoreData>> mScores; /**< Stored high scores */
        int mToAdd;                                          /**< Buffer with score to be added */

private:
        /**
         * @brief Constructor for HighScore object
         * @param path
         * @param quantity
         */
        HighScore(std::string path, unsigned int quantity) : mPath(std::move(path)), mQuantity(quantity), mToAdd(0)
        {
                // Try loading the given file, otherwise throw exception
                try {
                        load();
                } catch (const std::exception& exc) {
                        std::cerr << exc.what();
                }
        }

public:
        /**
         * @brief Deleted copy constructor
         */
        HighScore(const HighScore&) = delete;
        /**
         * @brief Deleted assignment operator
         * @return HighScore
         */
        HighScore& operator=(const HighScore&) = delete;
        /**
         * @brief Destructor for HighScore object
         */
        ~HighScore()
        {
                save();
                clear();
        }
        /**
         * @brief Get instance of HighScore object
         * @return HighScore
         */
        static HighScore& getInstance();
        /**
         * @brief Load high score file
         */
        void load();
        /**
         * @brief Save stored high scores to file
         */
        void save();
        /**
         * @brief Clear stored high scores
         */
        void clear() { mScores.clear(); }
        /**
         * @brief Add new high score
         * @param score HighScoreData - score to be added
         */
        void add(const std::shared_ptr<HighScoreData>& score);
        /**
         * @brief Get stored scores
         * @return std::vector<HighScoreData> - std::vector containing pointers to stored scores
         */
        [[nodiscard]] const std::vector<std::shared_ptr<HighScoreData>>& getScores() const { return mScores; }
        /**
         * @brief Get highest high score
         * @return int - score
         */
        [[maybe_unused]] [[nodiscard]] int getHighScore() const;
        /**
         * @brief Check if given score is high score
         * @param score int - score to be checked
         * @return bool - true if new high score
         */
        [[nodiscard]] bool isHighScore(int score) const;
        /**
         * @brief Add score to buffer
         * @param score int - score to be added
         */
        void add(int score) { mToAdd = score; }
        /**
         * @brief Get score stored in buffer
         * @return int - score stored in buffer
         */
        [[nodiscard]] int getToAdd() const { return mToAdd; }
};

#endif // DOODLEJUMP_HIGHSCORE_H

//
// Created by Pablo Deputter on 11/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

#include <random>

/**
 * @brief Namespace holds all Utilities
 */
namespace Utils {
/**
 * @brief Class for Random
 */
class Random
{
private:
        /**
         * @brief Private default constructor
         */
        Random() = default;

public:
        /**
         * @brief Default destructor
         */
        ~Random() = default;
        /**
         * @brief Deleted copy constructor
         */
        Random(const Random&) = delete;
        /**
         * @brief Deleted assignment operator
         * @return Random
         */
        Random& operator=(const Random&) = delete;
        /**
         * @brief Get instance of Random
         * @return Random
         */
        static Random& getInstance();
        /**
         * @brief Get random float in given interval
         * @param a float - begin interval
         * @param b float - end interval
         * @return float
         */
        [[nodiscard]] float random(float a, float b);
};
} // namespace Utils

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_RANDOM_H

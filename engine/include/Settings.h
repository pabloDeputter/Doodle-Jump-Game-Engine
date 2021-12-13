//
// Created by Pablo Deputter on 12/12/2021.
//

#ifndef DOODLEJUMP_SETTINGS_H
#define DOODLEJUMP_SETTINGS_H

/**
 * @brief Namespace for Settings used in World
 */
namespace Settings {
/**
 * @brief Spawn rates - Platform
 */
static float CHANCE_STATIC = .9;      /**< Spawn rate of Static Platform */
static float CHANCE_HORIZONTAL = .04; /**< Spawn rate of Horizontal Platform */
static float CHANCE_VERTICAL = .04;   /**< Spawn rate of Vertical Platform */
static float CHANCE_TEMPORARY = .02f; /**< Spawn rate of Temporary Platform */

/**
 * @brief Spawn rates - Bonus
 */
static float CHANCE_BONUS = .1f;   /**< Spawn rate of Bonus object */
static float CHANCE_SPRING = 1.;   /**< Spawn rate of Spring */
static float CHANCE_JETPACK = .0f; /**< Spawn rate of Jetpack */

/**
 * @brief Max. amount and min amount of platforms that can be on the screen at the same time
 */
static unsigned int MIN_PLATFORMS = 7;  /**< Min. amount of Platforms */
static unsigned int MAX_PLATFORMS = 20; /**< Max. amount of Platforms */

static float DIFFICULTY = 0.f; /** Difficulty */

/**
 * @brief Enum holding different difficulties
 */
enum Difficulty
{
        eEasy = 0,
        eNormal,
        eDifficult,
        eHard,
        eExtreme
};
/**
 * @brief Update difficulty of current game
 * @param difficulty Settings::Difficulty - mode
 */
bool static setDifficulty(Difficulty difficulty)
{
        switch (difficulty) {
        case eEasy:
                //                std::cout << "Easy\n";
                CHANCE_STATIC = .9f;
                CHANCE_HORIZONTAL = .04f;
                CHANCE_VERTICAL = .04f;
                CHANCE_TEMPORARY = .02f;

                CHANCE_BONUS = .05f;
                CHANCE_SPRING = .95f;
                CHANCE_JETPACK = .05f;

                MAX_PLATFORMS = 20;
                DIFFICULTY = 0.f;
                break;
        case eNormal:
                //                std::cout << "Normal\n";
                CHANCE_STATIC = .8f;
                CHANCE_HORIZONTAL = .07f;
                CHANCE_VERTICAL = .07f;
                CHANCE_TEMPORARY = .06f;

                CHANCE_BONUS = .15f;
                CHANCE_SPRING = .9f;
                CHANCE_JETPACK = .1f;

                MAX_PLATFORMS = 17;
                DIFFICULTY = 0.25f;
                break;
        case eDifficult:
                //                std::cout << "Difficult\n";
                CHANCE_STATIC = .6f;
                CHANCE_HORIZONTAL = .15f;
                CHANCE_VERTICAL = .15f;
                CHANCE_TEMPORARY = .1f;

                CHANCE_BONUS = .25f;
                CHANCE_SPRING = .75;
                CHANCE_JETPACK = .25f;

                MAX_PLATFORMS = 14;
                DIFFICULTY = 0.5f;
                break;
        case eHard:
                //                std::cout << "Hard\n";
                CHANCE_STATIC = .4f;
                CHANCE_HORIZONTAL = .22f;
                CHANCE_VERTICAL = .22f;
                CHANCE_TEMPORARY = .16f;

                CHANCE_BONUS = .30f;
                CHANCE_SPRING = .75f;
                CHANCE_JETPACK = .25f;

                MAX_PLATFORMS = 10;
                DIFFICULTY = 0.75f;
                break;
        case eExtreme:
                //                std::cout << "Extreme\n";
                CHANCE_STATIC = .2f;
                CHANCE_HORIZONTAL = .3f;
                CHANCE_VERTICAL = .3f;
                CHANCE_TEMPORARY = .2f;

                CHANCE_BONUS = .30f;
                CHANCE_SPRING = .75f;
                CHANCE_JETPACK = .25f;

                MAX_PLATFORMS = 7;
                DIFFICULTY = 0.85f;
                break;
        }
        return true;
}
} // namespace Settings

#endif // DOODLEJUMP_SETTINGS_H

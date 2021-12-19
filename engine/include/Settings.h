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
static float CHANCE_STATIC = .9f;
;                                      /**< Spawn rate of Static Platform */
static float CHANCE_HORIZONTAL = .04f; /**< Spawn rate of Horizontal Platform */
static float CHANCE_VERTICAL = .04f;   /**< Spawn rate of Vertical Platform */
static float CHANCE_TEMPORARY = .02f;  /**< Spawn rate of Temporary Platform */

/**
 * @brief Spawn rates - Bonus
 */
static float CHANCE_BONUS = 0.05f;  /**< Spawn rate of Bonus object */
static float CHANCE_SPRING = .85;   /**< Spawn rate of Spring */
static float CHANCE_JETPACK = .05f; /**< Spawn rate of Jetpack */
static float CHANCE_COIN = .1f;     /**< Spawn rate of Coin */

/**
 * @brief Max. amount and min amount of platforms that can be on the screen at the same time
 */
//[[maybe_unused]] static unsigned int MIN_PLATFORMS = 7; /**< Min. amount of Platforms */
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
        eInsane,
        eExtreme
};
/**
 * @brief Update difficulty of current game
 * @param difficulty Settings::Difficulty - mode
 */
[[maybe_unused]] bool static setDifficulty(Difficulty difficulty)
{
        switch (difficulty) {
        case eEasy:
                CHANCE_STATIC = .9f;
                CHANCE_HORIZONTAL = .04f;
                CHANCE_VERTICAL = .04f;
                CHANCE_TEMPORARY = .02f;

                CHANCE_BONUS = .05f;
                CHANCE_SPRING = .80f;
                CHANCE_JETPACK = .05f;
                CHANCE_COIN = .15f;

                MAX_PLATFORMS = 20;
                DIFFICULTY = 0.f;
                break;
        case eNormal:
                CHANCE_STATIC = .8f;
                CHANCE_HORIZONTAL = .07f;
                CHANCE_VERTICAL = .07f;
                CHANCE_TEMPORARY = .06f;

                CHANCE_BONUS = .15f;
                CHANCE_SPRING = .75f;
                CHANCE_JETPACK = .1f;
                CHANCE_COIN = .15f;

                MAX_PLATFORMS = 17;
                DIFFICULTY = 0.25f;
                break;
        case eDifficult:
                CHANCE_STATIC = .6f;
                CHANCE_HORIZONTAL = .15f;
                CHANCE_VERTICAL = .15f;
                CHANCE_TEMPORARY = .1f;

                CHANCE_BONUS = .25f;
                CHANCE_SPRING = .70f;
                CHANCE_JETPACK = .15f;
                CHANCE_COIN = .15f;

                MAX_PLATFORMS = 14;
                DIFFICULTY = 0.5f;
                break;
        case eHard:
                CHANCE_STATIC = .4f;
                CHANCE_HORIZONTAL = .22f;
                CHANCE_VERTICAL = .22f;
                CHANCE_TEMPORARY = .16f;

                CHANCE_BONUS = .30f;
                CHANCE_SPRING = .60f;
                CHANCE_JETPACK = .25f;
                CHANCE_COIN = .15f;

                MAX_PLATFORMS = 10;
                DIFFICULTY = 0.75f;
                break;
        case eInsane:
                CHANCE_STATIC = .3f;
                CHANCE_HORIZONTAL = .25f;
                CHANCE_VERTICAL = .25f;
                CHANCE_TEMPORARY = .2f;

                CHANCE_BONUS = .30f;
                CHANCE_SPRING = .60f;
                CHANCE_JETPACK = .25f;
                CHANCE_COIN = .15f;

                MAX_PLATFORMS = 10;
                DIFFICULTY = 0.85f;
                break;
        case eExtreme:
                CHANCE_STATIC = .2f;
                CHANCE_HORIZONTAL = .3f;
                CHANCE_VERTICAL = .3f;
                CHANCE_TEMPORARY = .2f;

                CHANCE_BONUS = .20f;
                CHANCE_SPRING = .60f;
                CHANCE_JETPACK = .10f;
                CHANCE_COIN = .30f;

                MAX_PLATFORMS = 7;
                DIFFICULTY = 0.90f;
                break;
        }
        return true;
}
} // namespace Settings

#endif // DOODLEJUMP_SETTINGS_H

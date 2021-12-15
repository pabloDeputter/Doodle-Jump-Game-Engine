//
// Created by Pablo Deputter on 07/12/2021.
//

#ifndef DOODLEJUMP_BONUSCONTROLLER_H
#define DOODLEJUMP_BONUSCONTROLLER_H

#include "IController.h"

/**
 * @brief Namespace holds all Controllers
 */
namespace Controller {
/**
 * @brief Class for Bonus Controller
 */
class BonusController : public IController
{
public:
        /**
         * @brief Constructor for BonusController object
         * @param entity Model::Entity - pointer to Entity to be controlled
         */
        explicit BonusController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}
        /**
         * @brief Default constructor for BonusController object
         */
        BonusController() = default;
        /**
         * @brief Default destructor for BonusController object
         */
        ~BonusController() override = default;
};
} // namespace Controller

#endif // DOODLEJUMP_BONUSCONTROLLER_H

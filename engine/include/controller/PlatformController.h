//
// Created by Pablo Deputter on 20/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H

#include "IController.h"

/**
 * @brief Namespace holds all Controllers
 */
namespace Controller {
/**
 * @brief Class for Platform Controller
 */
class PlatformController : public IController
{
public:
        /**
         * @brief Constructor for PlatformController object
         * @param entity Model::Entity - pointer to Entity to be controlled
         */
        explicit PlatformController(std::shared_ptr<Model::Entity>& entity) : IController(entity) {}
        /**
         * @brief Default constructor for PlatformController object
         */
        PlatformController() = default;
        /**
         * @brief Default destructor for PlatformController object
         */
        ~PlatformController() override = default;
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORMCONTROLLER_H

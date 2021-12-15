//
// Created by Pablo Deputter on 19/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H

#include "IController.h"

/**
 * @brief Namespace holds all Controllers
 */
namespace Controller {
/**
 * @brief Class for Player Controller
 */
class PlayerController : public IController
{
private:
        /**
         * @brief Handle KeyPressedEvent
         * @param event KeyPressedEvent
         */
        void handleEvent(const KeyPressedEvent& event) override;
        /**
         * @brief Handle MoveEvent
         * @param event MoveEvent
         */
        void handleEvent(const MoveEvent& event) override;
        /**
         * @brief Handle CollisionEvent
         * @param event CollisionEvent
         */
        void handleEvent(const CollisionEvent& event) override;

public:
        /**
         * @brief Constructor for PlayerController object
         * @param entity Model::Entity - pointer to Entity to be controlled
         */
        explicit PlayerController(std::shared_ptr<Model::Player>& entity) { mEntity = entity; }
        /**
         * @brief Default constructor for PlayerController object
         */
        PlayerController() = default;
        /**
         * @brief Default destructor for PlayerController object
         */
        ~PlayerController() override { std::cout << "lol\n"; }
};
} // namespace Controller

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLAYERCONTROLLER_H

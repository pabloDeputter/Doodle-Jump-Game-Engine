//
// Created by Pablo Deputter on 06/12/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Player.h"

namespace Model {

class Jetpack : public Entity
{
private:
        std::pair<float, float> mBounds;
        bool mMovingDown;
        bool mInit;
        bool mStarted;

public:
        Jetpack() = default;

        ~Jetpack() override = default;

        [[nodiscard]] Model::Type getType() const override;

        void move(bool collision) override;

        void initBounds();

        // TODO - jetpack
        void visit(Model::Player& player) override
        {
                if (isRemovable()) {
                        player.setDrag(0.006f);
                        return;
                }
                Utils::Stopwatch::getInstance().addTimer(Model::eJetpack, 4.5f);
                player.setDrag(0.f);
                mStarted = true;
        }

        bool getRemovable() const override { return mStarted; }

        bool isRemovable() const override
        {
                if (mRemoveFlag && Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                        std::cout << "removeJetpackEntity\n";
                        return true;
                }
                if (mRemoveFlag && !Utils::Stopwatch::getInstance().checkTimer(Model::eJetpack)) {
                        return false;
                }
        }

        unsigned int getVal() const override { return 15; }
};
} // namespace Model

#endif // DOODLEJUMP_JETPACK_H

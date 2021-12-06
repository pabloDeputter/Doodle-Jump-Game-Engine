//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/TemporaryPlatform.h"

using namespace Model;

Model::Type TemporaryPlatform::getType() const { return Model::eTemporary; }

void TemporaryPlatform::move(bool collision)
{
        if (collision) {
                Entity::onDestroy();
        }
}
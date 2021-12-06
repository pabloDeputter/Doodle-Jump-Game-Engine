//
// Created by Pablo Deputter on 06/12/2021.
//

#include "model/Spring.h"

using namespace Model;

Model::Type Model::Spring::getType() const { return Model::eSpring; }

void Spring::move(bool collision)
{
        if (collision) {
                onDestroy();
        }
}

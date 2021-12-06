//
// Created by Pablo Deputter on 05/12/2021.
//

#include "model/StaticPlatform.h"

using namespace Model;

Model::Type StaticPlatform::getType() const { return Model::eStatic; }

void StaticPlatform::move(bool collision) {}
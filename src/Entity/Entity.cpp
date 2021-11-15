//
// Created by Pablo Deputter on 13/11/2021.
//

#include "Entity.h"

using namespace Model;

float Entity::getX() const { return mX; }

float Entity::getY() const { return mY; }

void Entity::setX(const float x) { mX = x; }

void Entity::setY(const float y) { mY = y; }
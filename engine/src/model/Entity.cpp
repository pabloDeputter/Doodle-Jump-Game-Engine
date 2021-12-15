//
// Created by Pablo Deputter on 13/11/2021.
//

#include "model/Entity.h"

using namespace Model;

float Entity::getX() const { return mX; }

float Entity::getY() const { return mY; }

void Entity::setX(float x) { mX = x; }

void Entity::setY(float y) { mY = y; }

float Entity::getWidth() const { return mWidth; }

float Entity::getHeight() const { return mHeight; }

void Entity::setWidth(float width) { mWidth = width; }

void Entity::setHeight(float height) { mHeight = height; }

void Entity::move(float x, float y)
{
        mX += x;
        mY += y;
}

void Entity::onDestroy() { Subject::clear(); }
void Entity::setRemoveFlag(bool flag)
{
        mRemoveFlag = true;
        onDestroy();
}

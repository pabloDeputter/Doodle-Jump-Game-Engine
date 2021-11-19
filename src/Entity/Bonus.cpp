//
// Created by Pablo Deputter on 16/11/2021.
//

#include "Bonus.h"

using namespace Model;

Bonus::Sort Bonus::getMSort() const { return Bonus::eSpring; }

void Bonus::setMSort(Bonus::Sort sort) { mSort = sort; }
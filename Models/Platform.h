//
// Created by Pablo Deputter on 13/11/2021.
//

#ifndef ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H
#define ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H

#include "Entity.h"

namespace Model {

class Platform : public Entity
{
private:
        //        Model::PlatformType sort;

public:
        std::string getType() const override { return "platform"; }

        //        const Model::PlatformType& getSort() const { return Platform::sort; }
        //
        //        void setSort(Model::PlatformType s) { Platform::sort = s; }
};
} // namespace Model

#endif // ADVANCED_PROGRAMMING_DOODLEJUMP_PLATFORM_H

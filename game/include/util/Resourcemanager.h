//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_RESOURCEMANAGER_H
#define DOODLEJUMP_RESOURCEMANAGER_H

#include "SFML/Graphics.hpp"
#include "model/Entity.h"

#include <map>
#include <string>

struct Resourceholder
{
private:
        std::string mPath;
        std::map<Model::Type, std::shared_ptr<sf::Texture>> mResources;

public:
        void insert(Model::Type type, const std::string& subPath)
        {
                std::shared_ptr<sf::Texture> tex = std::make_shared<sf::Texture>();
                tex->loadFromFile(mPath + subPath);
                mResources.emplace(type, tex);
        }

        std::shared_ptr<sf::Texture>& get(Model::Type type) { return mResources[type]; }
};

class Resourcemanager
{
private:
        std::shared_ptr<Resourceholder> mTextures;

public:
        Resourcemanager() = default;

        ~Resourcemanager() = default;

        Resourcemanager(const Resourcemanager&) = delete;

        Resourcemanager& operator=(const Resourcemanager&) = delete;

        const std::shared_ptr<Resourceholder>& getTextures() const { return mTextures; }
};

#endif // DOODLEJUMP_RESOURCEMANAGER_H

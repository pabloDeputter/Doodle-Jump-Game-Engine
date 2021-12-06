//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_RESOURCEMANAGER_H
#define DOODLEJUMP_RESOURCEMANAGER_H

#include "SFML/Graphics.hpp"
#include "model/Entity.h"

#include <map>
#include <string>
#include <utility>

namespace Utils {
struct Resourceholder
{
private:
        std::string mPath;
        std::map<Model::Type, std::shared_ptr<sf::Texture>> mResources;
public:
        explicit Resourceholder(std::string path) : mPath(std::move(path)) {}

        ~Resourceholder() = default;

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

        explicit Resourcemanager(const std::string& path) { mTextures = std::make_shared<Resourceholder>(path); }

public:
        ~Resourcemanager() = default;

        Resourcemanager(const Resourcemanager&) = delete;

        Resourcemanager& operator=(const Resourcemanager&) = delete;

        static Resourcemanager& getInstance()
        {
                static Resourcemanager instance(
                    "/Users/pablodeputter/Documents/GitHub/Advanced-Programming-DoodleJump/resource");
                return instance;
        }

        void addTexture(Model::Type type, const std::string& subPath) { mTextures->insert(type, subPath); }

        const std::shared_ptr<Resourceholder>& getTextures() const { return mTextures; }
};
} // namespace Utils

#endif // DOODLEJUMP_RESOURCEMANAGER_H

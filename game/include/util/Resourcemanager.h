//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_RESOURCEMANAGER_H
#define DOODLEJUMP_RESOURCEMANAGER_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


#include "model/Entity.h"
#include "util/Exception.h"

#include <map>
#include <string>
#include <utility>
#include <typeinfo>

namespace Utils {
template<class Type>
struct Resourceholder
{
private:
        std::string mPath;
        std::map<Model::Type, std::shared_ptr<Type>> mResources;
public:
        explicit Resourceholder(std::string path) : mPath(std::move(path)) {}

        ~Resourceholder() = default;

        void insert(Model::Type type, const std::string& subPath)
        {
                std::shared_ptr<Type> file = std::make_shared<Type>();
                std::string path = mPath + std::string(subPath);

                if (!file->loadFromFile(path)) {
                        throw(FileException(path, typeid(file).name()));
                }
                mResources.emplace(type, file);
        }

        std::shared_ptr<Type>& get(Model::Type type) { return mResources[type]; }

        void clear() { mResources.clear(); }
};

class Resourcemanager
{
private:
        std::shared_ptr<Resourceholder<sf::Texture>> mTextures;
        std::shared_ptr<Resourceholder<sf::Font>> mFonts;
        std::shared_ptr<Resourceholder<sf::SoundBuffer>> mSounds;

        explicit Resourcemanager(const std::string& path)
        {
                mTextures = std::make_shared<Resourceholder<sf::Texture>>(path);
                mFonts = std::make_shared<Resourceholder<sf::Font>>(path);
                mSounds = std::make_shared<Resourceholder<sf::SoundBuffer>>(path);
        }

public:
        ~Resourcemanager() { clear(); }

        Resourcemanager(const Resourcemanager&) = delete;

        Resourcemanager& operator=(const Resourcemanager&) = delete;

        static Resourcemanager& getInstance()
        {
                static Resourcemanager instance(
                    "/Users/pablodeputter/Documents/GitHub/Advanced-Programming-DoodleJump/resource");
                return instance;
        }

        void addTexture(Model::Type type, const std::string& subPath) { mTextures->insert(type, subPath); }

        void addFont(Model::Type type, const std::string& subPath) { mFonts->insert(type, subPath); }

        void addSound(Model::Type type, const std::string& subPath) { mSounds->insert(type, subPath); }

        [[nodiscard]] const std::shared_ptr<Resourceholder<sf::Texture>>& getTextures() const { return mTextures; }

        [[nodiscard]] const std::shared_ptr<Resourceholder<sf::Font>>& getFonts() const { return mFonts; }

        [[nodiscard]] const std::shared_ptr<Resourceholder<sf::SoundBuffer>>& getSounds() const { return mSounds; }

        void clear() const
        {
                mTextures->clear();
                mFonts->clear();
                mSounds->clear();
        }
};
} // namespace Utils

#endif // DOODLEJUMP_RESOURCEMANAGER_H

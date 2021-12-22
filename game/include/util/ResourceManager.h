//
// Created by Pablo Deputter on 29/11/2021.
//

#ifndef DOODLEJUMP_RESOURCEMANAGER_H
#define DOODLEJUMP_RESOURCEMANAGER_H

#include "model/Entity.h"
#include "util/Exception.h"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <map>
#include <string>
#include <typeinfo>
#include <utility>

/**
 * @brief Namespace holds all utilities
 */
namespace Utils {

/**
 * @brief Enum holds all resources that can be loaded
 */
enum Type
{
        // Entities
        ePlayer = 0,
        eBonus,
        eStatic,
        eHorizontal,
        eVertical,
        eTemporary,
        eBackground,
        eJetpack,
        eSpring,
        eScore,
        eCoin,
        eMenuLogo,
        eMenuCursor,
        eMenuHighScores,
        eMenuInfo,
        eMenuSettings,
        eMenuItemBack,
        eShopCh1,
        eShopCh2,
        eShopCh3,
        eShopBg1,
        eShopBg2,
        eShopBg3
};

/**
 * @brief Class for ResourceHolder
 * @tparam Type class - type of resource to store
 */
template <class Type>
class ResourceHolder
{
private:
        std::string mPath;                                       /**< Path to resources */
        std::map<Utils::Type, std::shared_ptr<Type>> mResources; /**< std::map containing all stored resources */
public:
        /**
         * @brief Constructor for ResourceHolder object
         * @param path std::string - path to resources
         */
        explicit ResourceHolder(std::string path) : mPath(std::move(path)) {}
        /**
         * @brief Destructor for ResourceHolder object
         */
        ~ResourceHolder() { clear(); }
        /**
         * @brief Add new resource to ResourceHolder
         * @param type Utils::Type - key to identify resource in future
         * @param subPath std::string - sub path to specific resource
         */
        void insert(Utils::Type type, const std::string& subPath)
        {
                std::shared_ptr<Type> file = std::make_shared<Type>();
                std::string path = mPath + std::string(subPath);
                // If file cannot be loaded --> throw exception
                if (!file->loadFromFile(path)) {
                        throw(FileException(path, typeid(file).name()));
                }
                mResources.emplace(type, file);
        }
        /**
         * @brief Get specific resource depending on given key
         * @param type Utils::Type - key to be used
         * @return Type - found resource
         */
        std::shared_ptr<Type>& get(Utils::Type type) { return mResources[type]; }
        /**
         * @brief Get resources
         * @return std::map<Utils::Type, Type> - resources
         */
        [[nodiscard]] std::map<Utils::Type, std::shared_ptr<Type>>& getResources() { return mResources; }
        /**
         * @brief Clear stored resources
         */
        void clear() { mResources.clear(); }
};

/**
 * @brief Class for ResourceManager implemented using singleton pattern
 */
class ResourceManager
{
private:
        std::shared_ptr<ResourceHolder<sf::Texture>> mTextures;   /**< Stored textures */
        std::shared_ptr<ResourceHolder<sf::Font>> mFonts;         /**< Stored fonts */
        std::shared_ptr<ResourceHolder<sf::SoundBuffer>> mSounds; /**< Stored sounds */
private:
        /**
         * @brief Constructor for ResourceManager object
         * @param path std::string - main path to resources
         */
        explicit ResourceManager(const std::string& path)
        {
                mTextures = std::make_shared<ResourceHolder<sf::Texture>>(path);
                mFonts = std::make_shared<ResourceHolder<sf::Font>>(path);
                mSounds = std::make_shared<ResourceHolder<sf::SoundBuffer>>(path);
        }

public:
        /**
         * @brief Destructor for ResourceManager object
         */
        ~ResourceManager() { clear(); }
        /**
         * @brief Deleted copy constructor operator
         */
        ResourceManager(const ResourceManager&) = delete;
        /**
         * @brief Deleted assignment operator
         * @return ResourceManager
         */
        ResourceManager& operator=(const ResourceManager&) = delete;
        /**
         * @brief Get instance
         * @return Resourcemanager
         */
        static ResourceManager& getInstance()
        {
                static ResourceManager instance("resource");
                return instance;
        }
        /**
         * @brief Add texture
         * @param type Utils::Type - key to store resource
         * @param subPath std::string - sub path to specific resource
         */
        void addTexture(Utils::Type type, const std::string& subPath) { mTextures->insert(type, subPath); }
        /**
         * @brief Add font
         * @param type Utils::Type - key to store resource
         * @param subPath std::string - sub path to specific resource
         */
        void addFont(Utils::Type type, const std::string& subPath) { mFonts->insert(type, subPath); }
        /**
         * @brief Add sound
         * @param type Utils::Type - key to store resource
         * @param subPath std::string - sub path to specific resource
         */
        void addSound(Utils::Type type, const std::string& subPath) { mSounds->insert(type, subPath); }
        /**
         * @brief Get textures
         * @return ResourceHolder - textures
         */
        [[nodiscard]] const std::shared_ptr<ResourceHolder<sf::Texture>>& getTextures() const { return mTextures; }
        /**
         * @brief Get fonts
         * @return ResourceHolder - fonts
         */
        [[nodiscard]] const std::shared_ptr<ResourceHolder<sf::Font>>& getFonts() const { return mFonts; }
        /**
         * @brief Get fonts
         * @return ResourceHolder - fonts
         */
        [[nodiscard]] const std::shared_ptr<ResourceHolder<sf::SoundBuffer>>& getSounds() const { return mSounds; }
        /**
         * @brief Assign one texture to another
         * @param type Utils::Type - type of texture to change
         * @param toSet Utils::Type - type of texture to change will get this one's texture assigned
         */
        void setTexture(Utils::Type type, Utils::Type toSet) const
        {
                auto& textures = mTextures->getResources();
                textures[toSet] = mTextures->get(type);
        }
        /**
         * @brief Clear all resources
         */
        void clear() const
        {
                mTextures->clear();
                mFonts->clear();
                mSounds->clear();
        }
};
} // namespace Utils

#endif // DOODLEJUMP_RESOURCEMANAGER_H

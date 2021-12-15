//
// Created by Pablo Deputter on 09/12/2021.
//

#ifndef DOODLEJUMP_EXCEPTION_H
#define DOODLEJUMP_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @brief Namespace holds all utilities
 */
namespace Utils {
/**
 * @brief Class for Exception
 */
class Exception : public std::exception
{
protected:
        std::string mValue; /**< Exception message */

public:
        /**
         * @brief Constructor for Exception object
         * @param value std::string - value of Exception message
         */
        explicit Exception(std::string value) : mValue(std::move(value)) {}
        /**
         * @brief Default constructor for Exception object
         */
        Exception() = default;
        /**
         * @brief Default destructor for Exception object
         */
        ~Exception() override = default;
        /**
         * @brief Get Exception message
         * @return char - value of Exception message
         */
        [[nodiscard]] const char* what() const noexcept override { return mValue.c_str(); }
};

/**
 * @brief Class for File Exception
 */
class FileException : public Exception
{
public:
        /**
         * @brief Constructor for FileException object
         * @param file std::string - path to file to be loaded
         * @param sort std::string - where is this file needed / why was this loaded
         */
        explicit FileException(std::string file, std::string sort)
            : Exception("Failed to load " + std::move(sort) + " '" + std::move(file) + "'. File is missing.\n")
        {
        }
        /**
         * @brief Default destructor for FileException object
         */
        ~FileException() override = default;
};
} // namespace Utils

#endif // DOODLEJUMP_EXCEPTION_H

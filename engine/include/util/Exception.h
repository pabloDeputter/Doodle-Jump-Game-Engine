//
// Created by Pablo Deputter on 09/12/2021.
//

#ifndef DOODLEJUMP_EXCEPTION_H
#define DOODLEJUMP_EXCEPTION_H

#include <exception>
#include <string>

namespace Utils {

class Exception : public std::exception
{
protected:
        std::string mValue;

public:
        explicit Exception(std::string value) : mValue(std::move(value)) {}

        Exception() = default;

        ~Exception() override = default;

        [[nodiscard]] const char* what() const noexcept override { return mValue.c_str(); }
};

class FileException : public Exception
{
public:
        explicit FileException(std::string file, std::string sort)
            : Exception("Failed to load " + std::move(sort) + " '" + std::move(file) + "'. File is missing.\n")
        {
        }
};
} // namespace Utils

#endif // DOODLEJUMP_EXCEPTION_H

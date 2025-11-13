/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DLloader
*/

#include "DLloader.hpp"

/**
 * @brief Constructor for the DLloader class.
 * Initializes the dynamic library handle to nullptr.
 * This constructor is used when no path is provided.
 */
DLloader::DLloader()
{
    _handle = nullptr;
}

/**
 * @brief Constructor for the DLloader class.
 * Loads the dynamic library from the specified path.
 * @param path The path to the dynamic library.
 */
DLloader::DLloader(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_handle) {
        std::cerr << "Error: " << dlerror() << std::endl;
    }
}

/**
 * @brief Retrieves a function from the loaded dynamic library.
 * @tparam T The type of the function to retrieve.
 * @param funcName The name of the function to retrieve.
 * @return A pointer to the function, or nullptr if the function could not be found.
 */
DLloader::~DLloader()
{
    if (_handle) {
        dlclose(_handle);
        _handle = nullptr;
    }
}

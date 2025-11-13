/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DLloader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

    #include <iostream>
    #include <dlfcn.h>

/**
 * @brief Class for loading dynamic libraries.
 * This class provides functionality to load a dynamic library
 * and retrieve functions from it.
 * It uses the dlopen and dlsym functions from the dlfcn.h library.
 */
class DLloader {
    public:
        DLloader();
        explicit DLloader(const std::string &path);
        ~DLloader();

        template <typename T>
        T *getFunc(const std::string &name) const
        {
            void *func = dlsym(_handle, name.c_str());
            if (!func) {
                std::cerr << "Error: " << dlerror() << std::endl;
                return nullptr;
            }
            auto castedFunc = reinterpret_cast<T *(*)()>(func);
          
            return (castedFunc)();
        }

    protected:
    private:
        void *_handle;
};

#endif /* !DLLOADER_HPP_ */

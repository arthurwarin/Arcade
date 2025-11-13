/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
    #define IGAME_HPP_

    #include <iostream>
    #include <vector>
    #include <string>
    #include <map>
    #include <chrono>
    #include <fstream>
    #include "Info.hpp"

namespace arcade {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual void init() = 0;
            virtual void update(EventEntries event) = 0;
            virtual void close() = 0;
            virtual bool isRunning() = 0;
            virtual const std::map<char, std::string> &getAssets() const = 0;
            virtual const std::vector<Drawables> &getDrawables() const = 0;
            virtual const std::vector<Texts> &getText() const = 0;
            virtual MenuItem getMenu() const = 0;
            virtual void setMenu(MenuItem path) = 0;
            virtual void setIsRunning(bool running) = 0;

        protected:
        private:
    };
}

#endif /* !IGAME_HPP_ */

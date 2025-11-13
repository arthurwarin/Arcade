/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
    #define IDISPLAY_HPP_

    #include <ios>
    #include <iostream>
    #include <filesystem>
    #include <vector>
    #include <chrono>
    #include <map>
    #include <fstream>
    #include <string>
    #include "Info.hpp"
    
namespace arcade {
    class IDisplay {
        public:
            virtual ~IDisplay() = default;
            virtual void init(const std::map<char, std::string> &Assets) = 0;
            virtual void update() = 0;
            virtual void close() = 0;
            virtual void display(std::vector<Drawables> drawable) = 0;
            virtual void display(std::vector<Texts> text) = 0;
            virtual void clear() = 0;
            virtual EventEntries getEvent() = 0;

        protected:
        private:
    };
}

#endif /* !IDISPLAY_HPP_ */

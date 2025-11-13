/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <filesystem>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <utility>
    #include "../../Abstract/AGame.hpp"
    #include "../../Core/DLloader.hpp"

namespace arcade {
    class Menu : public AGame {
        public:
            Menu();
            ~Menu() override;
            
            void init() override;
            void update(EventEntries event) override;
            void close() override;
            void setMenuInfo(const MenuItem& info);
            MenuItem getMenuInfo() const;
            MenuItem getMenu() const override;
            void setMenu(MenuItem path) override;
            
        private:
            size_t _index;
            bool _isUsernameSet;
            std::string _username;
            int _alphabetIndex;
            std::vector<std::string> _alphabet;
            
            std::pair<std::string, std::string> _selectedLib;
            std::pair<std::string, std::string> _selectedGame;
            
            std::vector<std::pair<std::string, std::string>> _libs;
            std::vector<std::pair<std::string, std::string>> _games;
            
            MenuItem _menuInfo;
            
            void loadLibraries();
    };
}

#endif /* !MENU_HPP_ */
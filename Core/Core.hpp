/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #define MENU_PATH "./lib/arcade_menu.so"

    #include "../interface/IDisplay.hpp"
    #include "../interface/IGame.hpp"
    #include "DLloader.hpp"

namespace arcade {
    class Core {
        public:
            Core();
            Core(std::string libPath);
            Core(std::string libPath, std::string gamePath);
            ~Core();
            void setLib(IDisplay *lib);
            void setGame(IGame *game);
            void setMenu();
            void setChangeLib(EventEntries event);
            void setChangeGame(EventEntries event);
            void run();
            void menuGetChange();
            void changeLib(std::string lib);
            void changeGame(std::string game);


        protected:
        private:
            size_t _currentLib;
            size_t _currentGame;
            IGame *_game;
            IDisplay *_lib;
            DLloader *_graphicLoader;
            DLloader *_gameLoader;
            MenuItem _menu;
            std::vector<std::string> _libPath;
            std::vector<std::string> _gamePath;
    };
}

#endif /* !CORE_HPP_ */

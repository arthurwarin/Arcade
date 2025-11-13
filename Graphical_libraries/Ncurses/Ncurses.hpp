/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
    #define NCURSES_HPP_

    #include <curses.h>
    #include "../../Abstract/ADisplay.hpp"

namespace arcade {
    class Ncurses : public ADisplay {
        public:
            Ncurses();
            ~Ncurses() override = default;

            void init(const std::map<char, std::string> &assets) override;
            void close() override;
            void update() override;
            void clear() override;
            void display(std::vector<Drawables> drawable) override;
            void display(std::vector<Texts> text) override;
            EventEntries getEvent() override;

        protected:
        private:
            WINDOW *_win;
    };
}

#endif /* !NCURSES_HPP_ */

/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"
#include <cmath>

namespace arcade {

    /**
     * @brief Constructor for the Ncurses class.
     * Initializes the Ncurses display.
     * This constructor is used to set up the Ncurses display.
     * It initializes the window pointer to nullptr.
     */
    Ncurses::Ncurses()
    {
        _win = nullptr;
    }

    /**
     * @brief Initializes the Ncurses display.
     * 
     * This function sets up the Ncurses display, initializes colors, and creates
     * a window for rendering. It also sets up the main menu and other UI elements.
     * 
     * @param assets A map of character keys to asset file paths.
     */
    void Ncurses::init(const std::map<char, std::string> &assets)
    {
        (void) assets;
        _win = initscr();
        nodelay(_win, TRUE);
        keypad(_win, TRUE);
        noecho();
        start_color();
        cbreak();
        curs_set(0);
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        box(_win, 0, 0);
        mvwprintw(_win, 0, max_x/2 - 8, " ARCADE GAME ");
        mvwprintw(_win, max_y-1, 2, " [ESC] Exit | [M] Menu | [Space] Restart | [LK] Switch Lib | [GH] Switch Game ");
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
        init_pair(8, COLOR_BLACK, COLOR_WHITE);
        init_pair(11, COLOR_BLACK, COLOR_BLACK);
        init_pair(12, COLOR_BLACK, COLOR_RED);
        init_pair(13, COLOR_BLACK, COLOR_YELLOW);
        init_pair(14, COLOR_BLACK, COLOR_CYAN);
        init_pair(15, COLOR_BLACK, COLOR_GREEN);
        init_pair(16, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(17, COLOR_BLACK, COLOR_BLUE);
        init_pair(18, COLOR_BLACK, COLOR_WHITE);
        wattron(_win, COLOR_PAIR(5) | A_BOLD);
        mvwprintw(_win, max_y/2, max_x/2 - 14, "Ncurses Display Initialized!");
        wattroff(_win, COLOR_PAIR(5) | A_BOLD);
        wrefresh(_win);
    }
    
    /**
     * @brief Updates the Ncurses display.
     * 
     * This function refreshes the display at a set interval to avoid flickering.
     * It uses a timer to control the refresh rate.
     */
    void Ncurses::update()
    {
        static auto start = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        if (elapsed_seconds.count() > 0.1) {
            start = now;
            wrefresh(_win);
        }
    }

    /**
     * @brief Clears the Ncurses display.
     * 
     * This function clears the display and redraws the main menu and other UI elements.
     * It uses a timer to control the refresh rate and avoid flickering.
     */
    void Ncurses::clear()
    {
        static bool initialized = false;
        static auto lastClear = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - lastClear;

        if (elapsed_seconds.count() < 0.1 && initialized) {
            return;
        }
        lastClear = now;
        initialized = true;        
        werase(_win);        
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        box(_win, 0, 0);
        wattron(_win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(_win, 0, max_x/2 - 8, " ARCADE GAME ");
        wattroff(_win, COLOR_PAIR(3) | A_BOLD);        
        wattron(_win, COLOR_PAIR(4) | A_DIM);
        mvwprintw(_win, max_y-1, 2, " [ESC] Exit | [M] Menu | [Space] Restart | [LK] Switch Lib | [GH] Switch Game ");
        wattroff(_win, COLOR_PAIR(4) | A_DIM);
    }

    /**
     * @brief Displays drawable elements on the Ncurses window.
     * 
     * This function takes a vector of drawable elements and displays them on the
     * Ncurses window. It sets the color and attributes for each element based on
     * its properties.
     * 
     * @param drawable A vector of drawable elements to display.
     */
    void Ncurses::display(std::vector<Drawables> drawable)
    {
        for (auto &elem : drawable) {
            int color_pair;
            int attrs = 0;            
            switch (elem.color) {
                case Color::BLACK:  color_pair = 11; break;
                case Color::RED:    color_pair = 12; break;
                case Color::YELLOW: color_pair = 13; break;
                case Color::CYAN:   color_pair = 14; break;
                case Color::GREEN:  color_pair = 15; break;
                case Color::MAGENTA: color_pair = 16; break;
                case Color::BLUE:   color_pair = 17; break;
                case Color::WHITE:  color_pair = 18; break;
                default:            color_pair = 11; break;
            }            
            switch (elem.direction) {
                case Direction::UP_G:    attrs |= A_BOLD; break;
                case Direction::DOWN_G:  attrs |= A_DIM; break;
                case Direction::LEFT_G:  attrs |= A_REVERSE; break;
                case Direction::RIGHT_G: attrs |= A_BOLD; break;
                default: break;
            }
            
            wattron(_win, COLOR_PAIR(color_pair) | attrs);
            mvwprintw(_win, elem.pos.y, elem.pos.x * 2, "%c", elem.draw != 0 ? elem.draw : ' ');
            wattroff(_win, COLOR_PAIR(color_pair) | attrs);
        }
    }

    /**
     * @brief Displays text elements on the Ncurses window.
     * 
     * This function takes a vector of text elements and displays them on the
     * Ncurses window. It sets the color and attributes for each element based on
     * its properties.
     * 
     * @param text A vector of text elements to display.
     */
    void Ncurses::display(std::vector<Texts> text)
    {
        for (auto &elem : text) {
            int color_pair;
            int attrs = 0;
            
            switch (elem.color) {
                case Color::BLACK:  color_pair = 1; break;
                case Color::RED:    color_pair = 2; break;
                case Color::YELLOW: color_pair = 3; break;
                case Color::CYAN:   color_pair = 4; break;
                case Color::GREEN:  color_pair = 5; break;
                case Color::MAGENTA: color_pair = 6; break;
                case Color::BLUE:   color_pair = 7; break;
                case Color::WHITE:  color_pair = 8; break;
                default:            color_pair = 1; break;
            }            
            switch (elem.direction) {
                case Direction::UP_G:    attrs |= A_BOLD; break;
                case Direction::DOWN_G:  attrs |= A_DIM; break;
                case Direction::LEFT_G:  attrs |= A_UNDERLINE; break;
                case Direction::RIGHT_G: attrs |= A_STANDOUT; break;
                default: break;
            }
            wattron(_win, COLOR_PAIR(color_pair) | attrs);
            mvwprintw(_win, elem.pos.y, elem.pos.x * 2, "%s", elem.text.c_str());
            wattroff(_win, COLOR_PAIR(color_pair) | attrs);
        }
    }

    /**
     * @brief Gets user input events from the Ncurses window.
     * 
     * This function captures user input events and returns the corresponding
     * EventEntries enum value based on the key pressed.
     * 
     * @return EventEntries The event corresponding to the key pressed.
     */
    EventEntries Ncurses::getEvent()
    {
        int ch = wgetch(_win);
        switch (ch) {
            case 27:
                return EventEntries::CLOSE;
            case KEY_UP:
                return EventEntries::UP;
            case KEY_DOWN:
                return EventEntries::DOWN;
            case KEY_LEFT:
                return EventEntries::LEFT;
            case KEY_RIGHT:
                return EventEntries::RIGHT;
            case ' ':
                return EventEntries::RESTART;
            case 'm':
            case 'M':
                return EventEntries::MENU;
            case 's':
            case 'S':
                return EventEntries::SAVE;
            case 'n':
            case 'N':
                return EventEntries::LIB_NEXT;
            case 'p':
            case 'P':
                return EventEntries::LIB_PREV;
            case 'g':
            case 'G':
                return EventEntries::GAME_NEXT;
            case 'b':
            case 'B':
                return EventEntries::GAME_PREV;
            case '\n':
            case KEY_ENTER:
                return EventEntries::ACTION1;
            case 'r':
            case 'R':
                return EventEntries::ACTION2;
            default:
                return EventEntries::NO_EVENT;
        }
    }

    /**
     * @brief Closes the Ncurses display.
     * 
     * This function cleans up and closes the Ncurses display, restoring the terminal
     * to its original state.
     */
    void Ncurses::close()
    {
        endwin();
    }

    extern "C" {
        /**
        * @brief Entry point for the Ncurses library.
        * 
        * This function returns a new instance of the Ncurses class.
        * 
        * @return IDisplay* A pointer to the Ncurses display instance.
        */
        IDisplay *entryPoint()
        {
            return new Ncurses();
        }
        
        /**
         * @brief Returns the type of the Ncurses library.
         * 
         * This function returns a string indicating the type of the library.
         * 
         * @return A C-style string indicating the library type.
         */
        char *getType()
        {
            return (char *) "libNcurses";
        }
    }
}

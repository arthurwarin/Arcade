/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Info
*/

#ifndef INFO_HPP_
    #define INFO_HPP_

    #include <iostream>
    #include <vector>
    #include <map>

namespace arcade {
    enum Color {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        WHITE,
        BLACK,
        CYAN,
        MAGENTA
    };

    enum EventEntries {
        NO_EVENT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        CLOSE,
        RESTART,
        LIB_NEXT,
        LIB_PREV,
        GAME_NEXT,
        GAME_PREV,
        ACTION1,
        ACTION2,
        MENU,
        SAVE
    };

    struct Rectangle {
        int x;
        int y;
        int width;
        int height;
    };

    enum Direction {
        UP_G,
        DOWN_G,
        LEFT_G,
        RIGHT_G,
        NONE_G
    };
    
    struct Position {
        int x;
        int y;
        bool operator==(const Position& other) const {
            return x == other.x && y == other.y;
        }
    };
    
    struct Drawables {
        Position pos;
        char draw;
        Color color;
        enum Direction direction = NONE_G;
        struct Rectangle rect = {0, 0, 40, 40}; 
        Drawables(int x, int y, char sp) : pos{x, y}, draw(sp) {}
    };
    
    struct Texts {
        Position pos;
        std::string text;
        Texts(int x, int y, std::string txt) : pos{x, y}, text(std::move(txt)) {}
        std::string font;
        Color color;
        enum Direction direction = NONE_G;
        int size;
    };

    struct MenuItem {
        std::string gpath;
        std::string lpath;
        std::string pseudo;
    };
}

#endif /* !INFO_HPP_ */
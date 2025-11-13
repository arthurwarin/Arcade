/*
** EPITECH PROJECT, 2025
** nibbler header
** File description:
** arcade
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_

    #include "../../Abstract/AGame.hpp"

namespace arcade {
    class Nibbler : virtual public AGame {
        public:
            Nibbler();
            ~Nibbler() override = default;
            void init() override;
            void update(EventEntries event) override;
            void checkCollisions(EventEntries event);
            void close() override;
            void setMap(int index);
            void sethighScore();
            void getHighScore();
            bool Start();
            void snakeMove(Direction direction);
            void Apple();
            void move();
            void reset();

        private:
            std::vector<arcade::Drawables> _snake;
            std::vector<arcade::Drawables> _walls;
            std::vector<arcade::Drawables> _apples;
            EventEntries _event;
            Drawables _fruit;
            int _mIndex;
            int _score;
            float _speed;
            bool _tail;
            bool _start;
            int _highScore;
            int _size;
    };
}

#endif /*!NIBBLER_HPP*/
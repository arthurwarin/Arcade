/*
** EPITECH PROJECT, 2025
** snake header
** File description:
** arcade
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "../../Abstract/AGame.hpp"

namespace arcade {
    class Snake : virtual public AGame {
        public:
            Snake();
            ~Snake() override = default;
            void init() override;
            void update(EventEntries event) override;
            void move(Direction direction);
            void close() override;
            void Apple();
            void sethighScore();
            void getHighScore();
            void setMap();
        private:
            EventEntries _event;
            Drawables _apple{0, 0 , 'a'};
            std::vector<Drawables> _snake;
            std::vector<Drawables> _walls;
            bool _start;
            int _score;
            int _highScore;
            float _speed;
            int _size;
            bool _push;
    };
}

#endif /*!SNAKE_HPP_*/
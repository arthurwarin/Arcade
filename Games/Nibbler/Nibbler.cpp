/*
** EPITECH PROJECT, 2025
** nibbler
** File description:
** arcade
*/

#include "Nibbler.hpp"
#include "../../Abstract/AGame.hpp"
#include <chrono>


namespace arcade {

    /**
     * 
     */
    Nibbler::Nibbler() : AGame(), _fruit(0, 0, 'a')
    {
        _score = 0;
        _highScore = 0;
        _event = EventEntries::NO_EVENT;
        _running = true;
    }

    /**
     * @brief Set the map for the Nibbler game.
     * 
     * This function reads a map file and initializes the walls, apples, and snake
     * based on the contents of the file. The map is specified by the index parameter.
     * 
     * @param index The index of the map to load.
     */
    void Nibbler::setMap(int index)
    {
        std::string str;
        std::string path;
        Drawables wall (0, 0, 'w');
        Drawables apple (0, 0, 'a');
        Drawables head (0, 0, 'h');
        Drawables body (0, 0, 'b');
        Drawables tail (0, 0, 't');
        if (std::ifstream("./Assets/Nibbler/Configuration/map" + std::to_string(index) + ".txt")) {
            path = "./Assets/Nibbler/Configuration/map" + std::to_string(index) + ".txt";
        } else {
            std::cout << "Error: map" + std::to_string(index) + ".txt not found" << std::endl;
            exit(84);
        }
        std::ifstream file(path);
        int row = 0;
        while (std::getline(file, str)) {
            for (size_t col = 0; col < str.length(); col++) {
                switch (str[col]) {
                    case '|':
                        wall = Drawables(col + 15, row + 5, 'w');
                        wall.color = WHITE;
                        wall.direction = LEFT_G;
                        wall.rect = {0, 0, _size, _size};
                        _walls.push_back(wall);
                        break;
                    case 'h':
                        head = Drawables(col + 15, row + 5, 'h');
                        head.color = WHITE;
                        head.direction = LEFT_G;
                        head.rect = {0, 0, _size, _size};
                        _snake.push_back(head);
                        break;
                    case 'b':
                        body = Drawables(col + 15, row + 5, 'b');
                        body.color = WHITE;
                        body.direction = LEFT_G;
                        body.rect = {0, 0, _size, _size};
                        _snake.push_back(body);
                        break;
                    case 't':
                        tail = Drawables(col + 15, row + 5, 't');
                        tail.color = WHITE;
                        tail.direction = LEFT_G;
                        tail.rect = {0, 0, _size, _size};
                        _snake.push_back(tail);
                        break;
                    case 'a':
                        apple = Drawables(col + 15, row + 5, 'a');
                        apple.color = WHITE;
                        apple.direction = LEFT_G;
                        apple.rect = {0, 0, _size, _size};
                        _apples.push_back(apple);
                        break;
                }
            }
            row++;
        }
    }

    /**
     * @brief Resets the Nibbler game.
     * 
     * This function clears the snake, walls, apples, and text. It also resets the
     * game state and sets a new map based on the current index.
     */
    void Nibbler::reset()
    {
        _snake.clear();
        _walls.clear();
        _apples.clear();
        _text.clear();
        _drawables.clear();
        _tail = false;
        _event = EventEntries::NO_EVENT;
        if (_mIndex == 3) {
            _mIndex = 1;
            _speed = 0.1;
        } else {
            _mIndex++;
            _speed += 0.01;
        }
        setMap(_mIndex);
        _assets.insert({{'a', "./Assets/Nibbler/apple.png"}});
        _assets.insert({{'h', "./Assets/Nibbler/head_right.png"}});
        _assets.insert({{'b', "./Assets/Nibbler/body_horizontal.png"}});
        _assets.insert({{'w', "./Assets/Nibbler/images.png"}});
        _assets.insert({{'t', "./Assets/Nibbler/tail_right.png"}});
        _text.push_back(Texts(0, 0, "Nibbler"));
        _text[0].color = WHITE;
        _text[0].font = "Poppins-Black";
        _text[0].direction = NONE_G;
        _text.push_back(Texts(0, 1, "High Score: " + std::to_string(_highScore)));
        _text[1].color = WHITE;
        _text[1].font = "Poppins-Black";
        _text[1].direction = NONE_G;
        _text.push_back(Texts(0, 2, "Press [SPACE] to start"));
        _text[2].color = WHITE;
        _text[2].font = "Poppins-Black";
        _text[2].direction = NONE_G;
        _text.push_back(Texts(0, 3, "Username: " + _menu.pseudo));
        _text[3].color = WHITE;
        _text[3].font = "Poppins-Black";
        _text[3].direction = NONE_G;
        _text.push_back(Texts(0, 4, "Score: " + std::to_string(_score)));
        _text[4].color = WHITE;
        _text[4].font = "Poppins-Black";
        _text[4].direction = NONE_G;
    }

    /**
     * @brief Initializes the Nibbler game.
     * 
     * This function sets up the initial state of the Nibbler game, including
     * loading assets, setting the initial score, and initializing the snake and
     * walls.
     */
    void Nibbler::init()
    {
        srand(time(nullptr));
        _score = 0;
        _highScore = 0;
        _mIndex = 1;
        _speed = 1;
        _tail = false;
        _running = true;
        _size = 40;
        _event = EventEntries::NO_EVENT;
        _tail = false;
        getHighScore();
        _assets.insert({{'a', "./Assets/Nibbler/apple.png"}});
        _assets.insert({{'h', "./Assets/Nibbler/head_right.png"}});
        _assets.insert({{'b', "./Assets/Nibbler/body_horizontal.png"}});
        _assets.insert({{'w', "./Assets/Nibbler/images.png"}});
        _assets.insert({{'t', "./Assets/Nibbler/tail_right.png"}});
        _text.push_back(Texts(0, 0, "Nibbler"));
        _text[0].color = WHITE;
        _text[0].font = "Poppins-Black";
        _text[0].direction = NONE_G;
        _text.push_back(Texts(0, 1, "High Score: " + std::to_string(_highScore)));
        _text[1].color = WHITE;
        _text[1].font = "Poppins-Black";
        _text[1].direction = NONE_G;
        _text.push_back(Texts(0, 2, "Press [SPACE] to start"));
        _text[2].color = WHITE;
        _text[2].font = "Poppins-Black";
        _text[2].direction = NONE_G;
        _text.push_back(Texts(0, 3, "Username: " + _menu.pseudo));
        _text[3].color = WHITE;
        _text[3].font = "Poppins-Black";
        _text[3].direction = NONE_G;
        _text.push_back(Texts(0, 4, "Score: " + std::to_string(_score)));
        _text[4].color = WHITE;
        _text[4].font = "Poppins-Black";
        _text[4].direction = NONE_G;
    }

    /**
     * @brief Gets the high score from the configuration file.
     * 
     * This function reads the high score from a file and sets it to the _highScore
     * member variable. If the file is not found or the value is invalid, it sets
     * the high score to 0.
     */
    void Nibbler::getHighScore()
    {
        if (std::ifstream("./Assets/Nibbler/Configuration/highscore.txt")) {
            std::ifstream file("./Assets/Nibbler/Configuration/highscore.txt");
            std::string line = "";
            for (int i = 0; i < 1; i++) {
                std::getline(file, line);
            }
            file.close();
            try {
                _highScore = std::stoi(line);
            } catch (std::exception &e) {
                _highScore = 0;
            }
        }
    }

    /**
     * @brief Sets the high score in the configuration file.
     * 
     * This function writes the current score to the high score file if it is
     * greater than the current high score.
     */
    void Nibbler::sethighScore()
    {
        if (_score > _highScore) {
            std::ofstream file("./Assets/Nibbler/Configuration/highscore.txt");
            if (!file.is_open()) {
                std::cout << "Error: highscore.txt not found" << std::endl;
                return;
            }
            file << std::to_string(_score) << std::endl;
            file.close();
        }
    }

    /**
     * @brief Checks for collisions with walls and updates the event accordingly.
     * 
     * This function checks for collisions between the snake and walls, and
     * updates the event based on the direction of movement.
     * 
     * @param event The current event to check for collisions against.
     */
    void Nibbler::checkCollisions(EventEntries event)
    {
        for (auto &it : _walls) {
            switch (_event) {
                case EventEntries::UP:
                    if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y - 1 == it.pos.y && _snake[1].pos.y != _snake[0].pos.y + 1)
                        _event = event;
                    break;
                case EventEntries::DOWN:
                    if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y + 1 == it.pos.y && _snake[1].pos.y != _snake[0].pos.y - 1)
                        _event = event;
                    break;
                case EventEntries::LEFT:
                    if (_snake[0].pos.x - 1 == it.pos.x && _snake[0].pos.y == it.pos.y && _snake[1].pos.x != _snake[0].pos.x + 1)
                        _event = event;
                    break;
                case EventEntries::RIGHT:
                    if (_snake[0].pos.x + 1 == it.pos.x && _snake[0].pos.y == it.pos.y && _snake[1].pos.x != _snake[0].pos.x - 1)
                        _event = event;
                    break;
                default:
                    break;
            }
        }
    }

    /**
     * @brief Handles the apple collision and updates the score.
     * 
     * This function checks for collisions between the snake and apples, and
     * updates the score and apple list accordingly.
     */
    void Nibbler::Apple()
    {
        int i = 0;
        for (auto &it : _apples) {
            if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y == it.pos.y) {
                _apples.erase(_apples.begin() + i);
                _tail = true;
                _score += 10;
                _text[4].text = "Score: " + std::to_string(_score);
            }
            i++;
        }
    }

    /**
     * @brief Moves the snake in the specified direction.
     * 
     * This function updates the position of the snake based on the specified
     * direction and handles the tail and body segments accordingly.
     * 
     * @param direction The direction to move the snake (UP, DOWN, LEFT, RIGHT).
     */
    void Nibbler::snakeMove(Direction direction)
    {
        std::pair<int, int> newPos = {_snake[_snake.size() - 1].pos.x, _snake[_snake.size() - 1].pos.y};
        for (size_t i = _snake.size() - 1; i > 0; i--) {
            _snake[i].direction = _snake[i - 1].direction;
            _snake[i].pos.x = _snake[i - 1].pos.x;
            _snake[i].pos.y = _snake[i - 1].pos.y;
        }
        if (_tail) {
            _snake[_snake.size() - 1].draw = 'b';
            Drawables body(newPos.first, newPos.second, 'b');
            body.color = BLUE;
            body.direction = LEFT_G;
            body.rect = {0, 0, _size, _size};
            _snake.push_back(body);
            _tail = false;
        }
        switch (direction) {
            case UP_G:
                _snake[0].pos.y -= 1;
                break;
            case DOWN_G:
                _snake[0].pos.y += 1;
                break;
            case LEFT_G:
                _snake[0].pos.x -= 1;
                break;
            case RIGHT_G:
                _snake[0].pos.x += 1;
                break;
            default:
                break;
        }
        _snake[0].direction = direction;
    }

    /**
     * @brief Moves the snake based on the current event.
     * 
     * This function checks the current event and moves the snake in the
     * corresponding direction, handling collisions with walls and other segments.
     */
    void Nibbler::move()
    {
        switch (_event) {
            case EventEntries::UP:
                for (auto x : _walls) {
                    if (_snake[0].pos.x == x.pos.x && _snake[0].pos.y - 1 == x.pos.y) {
                        for (auto y : _walls) {
                            if (_snake[0].pos.x + 1 == y.pos.x && _snake[0].pos.y == y.pos.y) {
                                _event = EventEntries::LEFT;
                                return;
                            }
                            if (_snake[0].pos.x - 1 == y.pos.x && _snake[0].pos.y == y.pos.y) {
                                _event = EventEntries::RIGHT;
                                return;
                            }
                        }
                        return;
                    }
                }
                snakeMove(UP_G);
                break;
            case EventEntries::DOWN:
                for (auto x : _walls) {
                    if (_snake[0].pos.x == x.pos.x && _snake[0].pos.y + 1 == x.pos.y) {
                        for (auto y : _walls) {
                            if (_snake[0].pos.x + 1 == y.pos.x && _snake[0].pos.y == y.pos.y) {
                                _event = EventEntries::LEFT;
                                return;
                            }
                            if (_snake[0].pos.x - 1 == y.pos.x && _snake[0].pos.y == y.pos.y) {
                                _event = EventEntries::RIGHT;
                                return;
                            }
                        }
                        return;
                    }
                }
                snakeMove(DOWN_G);
                break;
            case EventEntries::LEFT:
                for (auto x : _walls) {
                    if (_snake[0].pos.x - 1 == x.pos.x && _snake[0].pos.y == x.pos.y) {
                        for (auto y : _walls) {
                            if (_snake[0].pos.x == y.pos.x && _snake[0].pos.y + 1 == y.pos.y) {
                                _event = EventEntries::UP;
                                return;
                            }
                            if (_snake[0].pos.x == y.pos.x && _snake[0].pos.y - 1 == y.pos.y) {
                                _event = EventEntries::DOWN;
                                return;
                            }
                        }
                        return;
                    }
                }
                snakeMove(LEFT_G);
                break;
            case EventEntries::RIGHT:
                for (auto x : _walls) {
                    if (_snake[0].pos.x + 1 == x.pos.x && _snake[0].pos.y == x.pos.y) {
                        for (auto y : _walls) {
                            if (_snake[0].pos.x == y.pos.x && _snake[0].pos.y + 1 == y.pos.y) {
                                _event = EventEntries::UP;
                                return;
                            }
                            if (_snake[0].pos.x == y.pos.x && _snake[0].pos.y - 1 == y.pos.y) {
                                _event = EventEntries::DOWN;
                                return;
                            }
                        }
                        return;
                    }
                }
                snakeMove(RIGHT_G);
                break;
            default:
                break;
        }
    }

    /**
     * @brief Updates the game state based on the current event.
     * 
     * This function handles the game logic, including checking for collisions,
     * moving the snake, and updating the score. It also resets the game if
     * necessary.
     * 
     * @param event The current event to process.
     */
    void Nibbler::update(EventEntries event)
    {
        _drawables.clear();
        _drawables.push_back(_fruit);
        for (auto &it : _walls) {
            _drawables.push_back(it);
        }
        for (auto &it : _snake) {
            _drawables.push_back(it);
        }
        for (auto &it : _apples) {
            _drawables.push_back(it);
        }

        EventEntries temp = _event;
        if (_apples.size() == 0) {
            reset();
        }
        switch (event) {
            case EventEntries::NO_EVENT:
                break;
            case EventEntries::CLOSE:
                if (_score > _highScore) {
                    sethighScore();
                }
                close();
                return;
            case EventEntries::UP:
                if (_event != EventEntries::DOWN) {
                    _event = EventEntries::UP;
                }
                break;
            case EventEntries::DOWN:
                if (_event != EventEntries::UP) {
                    _event = EventEntries::DOWN;
                }
                break;
            case EventEntries::LEFT:
                if (_event != EventEntries::RIGHT) {
                    _event = EventEntries::LEFT;
                }
                break;
            case EventEntries::RIGHT:
                if (_event != EventEntries::LEFT) {
                    _event = EventEntries::RIGHT;
                }
                break;
        }
        if (!_start) {
            for (auto &it : _walls) {
                switch (_event) {
                    case EventEntries::UP:
                        if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y - 1 == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::DOWN:
                        if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y + 1 == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::LEFT:
                        if (_snake[0].pos.x - 1 == it.pos.x && _snake[0].pos.y == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::RIGHT:
                        if (_snake[0].pos.x + 1 == it.pos.x && _snake[0].pos.y == it.pos.y) {
                            return;
                        } else 
                            break;
                    default:
                        return;
                }
            }
            for (auto &it : _snake) {
                if (it.draw == 'h')
                    continue;
                switch (_event) {
                    case EventEntries::UP:
                        if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y - 1 == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::DOWN:
                        if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y + 1 == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::LEFT:
                        if (_snake[0].pos.x - 1 == it.pos.x && _snake[0].pos.y == it.pos.y) {
                            return;
                        } else 
                            break;
                    case EventEntries::RIGHT:
                        if (_snake[0].pos.x + 1 == it.pos.x && _snake[0].pos.y == it.pos.y) {
                            return;
                        } else 
                            break;
                    default:
                        return;
                }
            }
            _start = true;
        }
        checkCollisions(temp);
        static auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = end - start;
        if (elapsed.count() * _speed > 0.1) {
            start = std::chrono::steady_clock::now();
        } else {
            return;
        }
        move();
        Apple();
        if (!_snake.empty()) {
            for (auto it = _snake.begin() + 1; it != _snake.end(); it++) {
                if (_snake[0].pos.x == it->pos.x && _snake[0].pos.y == it->pos.y) {
                    if (_score > _highScore) {
                        sethighScore();
                    }
                    close();
                    return;
                }
            }
        }
    }

    /**
     * @brief Closes the Nibbler game and cleans up resources.
     * 
     * This function sets the running state to false, clears the snake, walls,
     * and apples, and resets the game state.
     */
    void Nibbler::close()
    {
        _running = false;
        _snake.clear();
        _walls.clear();
        _apples.clear();
    }

    extern "C" {
        /**
         * @brief Entry point for the Nibbler game.
         */
        IGame *entryPoint()
        {
            return new Nibbler();
        }

        /**
         * @brief Returns the type of the game.
         */
        char *getType()
        {
            return (char *) "gameNibbler";
        }
    }
}
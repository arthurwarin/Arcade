/*
** EPITECH PROJECT, 2025
** snake
** File description:
** arcade
*/

#include "Snake.hpp"

namespace arcade {
    /**
     * @brief Constructor for the Snake class.
     * Initializes the snake game state and assets.
     * This constructor is used to set up the snake game.
     * It initializes the apple position and other game variables.
     */
    Snake::Snake() : AGame(), _apple(0, 0, 'a')
    {
        _score = 0;
        _highScore = 0;
        _event = EventEntries::NO_EVENT;
        _running = true;
    }

    /**
    * @brief Initializes the Snake game state.
    * 
    * This function sets up all the necessary variables, assets, and text elements
    * required to start the Snake game. It initializes the random seed, sets the 
    * game status flags, loads high score data, populates the asset map with image
    * file paths, and creates initial text prompts for the game screen.
    */
    void Snake::init()
    {
        srand(time(NULL));
        _running = true;
        _score = 0;
        _highScore = 0;
        _speed = 1;
        _size = 40;
        _push = false;
        _start = false;
        getHighScore();
        _event = EventEntries::NO_EVENT;
        _assets.insert({{'a', "./Assets/Snake/apple.png"}});
        _assets.insert({{'h', "./Assets/Snake/head_right.png"}});
        _assets.insert({{'b', "./Assets/Snake/body_horizontal.png"}});
        _assets.insert({{'w', "./Assets/Snake/images.png"}});
        _assets.insert({{'t', "./Assets/Snake/tail_right.png"}});
        _text.push_back(Texts(0, 0, "Snake" + std::to_string(_score)));
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
        setMap();
        Apple();
    }


    /**
    * @brief Initializes the map layout by reading from the configuration file.
    * 
    * Reads the map data from "configmap.txt" and sets up wall and snake elements 
    * based on the characters found in the file. Each character corresponds to a
    * specific drawable game element.
    */
    void Snake::setMap()
    {
        std::string str;
        Drawables wall(0, 0, 'w');
        Drawables head(0, 0, 'h');
        Drawables body(0, 0, 'b');
        Drawables tail(0, 0, 't');
        if (!std::ifstream("./Assets/Snake/Configuration/configmap.txt")) {
            std::cout << "Error: map.txt not found" << std::endl;
            return;
        }
        std::ifstream file("./Assets/Snake/Configuration/configmap.txt");
        int row = 0;
        while (std::getline(file, str)) {
            for (size_t col = 0; col < str.length(); col++) {
                switch (str[col]) {
                    case '|':
                        wall = Drawables(col + 2, row + 3, 'w');
                        wall.color = WHITE;
                        wall.direction = LEFT_G;
                        wall.rect = {0, 0, _size, _size};
                        _walls.push_back(wall);
                        break;
                    case 'h':
                        head = Drawables(col + 2, row + 3, 'h');
                        head.color = WHITE;
                        head.direction = LEFT_G;
                        head.rect = {0, 0, _size, _size};
                        _snake.push_back(head);
                        break;
                    case 'b':
                        body = Drawables(col + 2, row + 3, 'b');
                        body.color = WHITE;
                        body.direction = LEFT_G;
                        body.rect = {0, 0, _size, _size};
                        _snake.push_back(body);
                        break;
                    case 't':
                        tail = Drawables(col + 2, row + 3, 't');
                        tail.color = WHITE;
                        tail.direction = LEFT_G;
                        tail.rect = {0, 0, _size, _size};
                        _snake.push_back(tail);
                        break;
                    default:
                        break;
                }
            }
            row++;
        }
    }

    /**
    * @brief Loads the high score from a file.
    * 
    * Attempts to read the high score from "highscore.txt". If the file or value
    * is invalid, sets the high score to 0.
    */
    void Snake::getHighScore()
    {
        if (std::ifstream("./Assets/Snake/Configuration/highscore.txt")) {
            std::ifstream file("./Assets/Snake/Configuration/highscore.txt");
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
     * @brief Saves the current score to the high score file if it's higher.
     * 
     * Writes the current score to "highscore.txt" only if it exceeds the existing
     * high score value.
     */
    void Snake::sethighScore()
    {
        if (_score > _highScore) {
            std::ofstream file("./Assets/Snake/Configuration/highscore.txt");
            if (!file.is_open()) {
                std::cout << "Error: highscore.txt not found" << std::endl;
                return;
            }
            file << std::to_string(_score) << std::endl;
            file.close();
        }
    }

    /**
     * @brief Closes the game and resets all stateful resources.
     * 
     * Sets the running state to false and clears all vectors and events.
     */
    void Snake::close()
    {
        _running = false;
        _drawables.clear();
        _text.clear();
        _assets.clear();
        _event = EventEntries::NO_EVENT;
        _snake.clear();
    }

    /**
     * @brief Generates and places an apple on the game map.
     * 
     * Selects a random position for the apple that is not occupied by the snake
     * or walls. If no valid positions exist, places the apple in a fallback location.
     */
    void Snake::Apple()
    {
        std::vector<std::pair<int, int>> coord;
        coord.clear();
        int minX = 7;
        int maxX = 15;
        int minY = 6;
        int maxY = 20;

        for (int y = minY; y < maxY; y++) {
            for (int x = minX; x < maxX; x++) {
                coord.push_back({x, y});
            }
        }
        for (size_t i = 0; i < coord.size(); i++) {
            bool occupied = false;        
            for (auto &snakePart : _snake) {
                if (coord[i].first == snakePart.pos.x && coord[i].second == snakePart.pos.y) {
                    occupied = true;
                    break;
                }
            }        
            if (!occupied) {
                for (auto &wall : _walls) {
                    if (coord[i].first == wall.pos.x && coord[i].second == wall.pos.y) {
                        occupied = true;
                        break;
                    }
                }
            }       
            if (occupied) {
                coord.erase(coord.begin() + i);
                i--;
            }
        }    
        if (coord.empty()) {
            _apple = Drawables((minX + maxX) / 2, (minY + maxY) / 2, 'a');
            _apple.color = GREEN;
            std::cout << "Warning: No valid positions for apple, using fallback position" << std::endl;
        } else {
            size_t randomIndex = rand() % coord.size();
            _apple = Drawables(coord[randomIndex].first, coord[randomIndex].second, 'a');
            _apple.draw = 'a';
            _apple.color = GREEN;        
            if (_score != 0 && _score % 5 == 0) {
                _speed += 0.1;
            }        
            _text[4].text = "Score: " + std::to_string(_score);
        }
    }

    /**
     * @brief Moves the snake in the given direction.
     * 
     * Updates the position of each segment of the snake. If the _push flag is set,
     * adds a new body segment to the snake.
     * 
     * @param direction The direction in which to move the snake.
     */
    void Snake::move(Direction direction)
    {
        std::pair<int, int> newPos = {_snake[_snake.size() - 1].pos.x, _snake[_snake.size() - 1].pos.y};
        for (size_t i = _snake.size() - 1; i > 0; i--) {
            _snake[i].direction = _snake[i - 1].direction;
            _snake[i].pos.x = _snake[i - 1].pos.x;
            _snake[i].pos.y = _snake[i - 1].pos.y;
        }
        if (_push) {
            _snake[_snake.size() - 1].draw = 'b';
            Drawables body(newPos.first, newPos.second, 'b');
            body.color = BLUE;
            body.direction = LEFT_G;
            body.rect = {0, 0, _size, _size};
            _snake.push_back(body);
            _push = false;
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
     * @brief Updates the game state based on the current event.
     * 
     * Processes input events, collision detection, snake movement, and apple
     * collection. Handles restart and game-over logic.
     * 
     * @param event The current input event.
     */
    void Snake::update(EventEntries event)
    {
        _drawables.clear();
        _drawables.push_back(_apple);
        for (auto &it : _walls) {
            _drawables.push_back(it);
        }
        for (auto &it : _snake) {
            _drawables.push_back(it);
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
            case EventEntries::RESTART:
                if (_score > _highScore) {
                    sethighScore();
                }
                close();
                init();
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
        static auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        if (elapsed.count() * _speed > 0.1) {
            start = std::chrono::steady_clock::now();
        } else {
            return;
        }
        switch (_event) {
            case EventEntries::UP:
                move(UP_G);
                break;
            case EventEntries::DOWN:
                move(DOWN_G);
                break;
            case EventEntries::LEFT:
                move(LEFT_G);
                break;
            case EventEntries::RIGHT:
                move(RIGHT_G);
                break;
            default:
                break;
        }
        if (!_snake.empty() && _snake[0].pos.x == _apple.pos.x && _snake[0].pos.y == _apple.pos.y) {
            _push = true;
            _score += 1;
            Apple();
        }
        if (!_snake.empty()) {
            for (auto &it : _walls) {
                if (_snake[0].pos.x == it.pos.x && _snake[0].pos.y == it.pos.y) {
                    if (_score > _highScore) {
                        sethighScore();
                    }
                    close();
                    return;
                }
            }
        }
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

    extern "C" {
           /**
        * @brief Entry point for the game.
        * 
        * Used for dynamic loading; creates a new instance of the Snake game.
        * 
        * @return Pointer to a newly created Snake game instance.
        */
        IGame *entryPoint()
        {
            return new Snake();
        }


        /**
         * @brief Returns the type of the game.
         * 
         * Used for identifying the game type when loaded.
         * 
         * @return A C-style string indicating the game type.
         */
        char *getType()
        {
            return (char *) "gameSnake";
        }
    }
}
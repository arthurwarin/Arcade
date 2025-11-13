/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sfml
*/

#include "Sfml.hpp"

namespace arcade {
    /**
     * @brief Constructor for the Sfml class.
     * Initializes the SFML display.
     * This constructor is used to set up the SFML display.
     * It initializes the window, font, text, and event variables.
     */
    Sfml::Sfml()
    {
        _event = sf::Event();
    }

    /**
     * @brief Initializes the SFML display.
     * 
     * This function sets up the SFML display, initializes the window, font,
     * text, and loads assets from the provided map. It also sets the size of the
     * display and initializes the event variable.
     * 
     * @param Assets A map of character keys to asset file paths.
     */
    void Sfml::init(const std::map<char, std::string> &Assets)
    {
        int characterSize = 14;

        _window.create(sf::VideoMode(1920, 1080), "Arcade");
        _window.setFramerateLimit(60);
        _font.loadFromFile("./Assets/font/Arial.ttf");
        _text.setFont(_font);
        _text.setCharacterSize(characterSize);
        _text.setStyle(sf::Text::Bold);
        _size = 1920 / 40;
        sf::IntRect rect(0, 0, _size, _size);
        for (auto &asset : Assets) {
            _assets[asset.first] = {sf::Texture(), sf::Sprite()};
            _assets[asset.first].texture.loadFromFile(asset.second);
            _assets[asset.first].sprite.setTexture(_assets[asset.first].texture);
            _assets[asset.first].sprite.setTextureRect(rect);
            _assets[asset.first].sprite.setOrigin(_size / 2, _size / 2);
        }
    }

    /**
     * @brief Gets user input events from the SFML window.
     * 
     * This function captures user input events and returns the corresponding
     * EventEntries enum value based on the key pressed.
     * 
     * @return EventEntries The event corresponding to the key pressed.
     */
    EventEntries Sfml::getEvent()
    {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed)
                return EventEntries::CLOSE;
            if (_event.type == sf::Event::KeyPressed) {
                switch (_event.key.code) {
                    case sf::Keyboard::Up:
                        return EventEntries::UP;
                    case sf::Keyboard::Down:
                        return EventEntries::DOWN;
                    case sf::Keyboard::Left:
                        return EventEntries::LEFT;
                    case sf::Keyboard::Right:
                        return EventEntries::RIGHT;
                    case sf::Keyboard::Escape:
                        return EventEntries::CLOSE;
                    case sf::Keyboard::Space:
                        return EventEntries::RESTART;
                    case sf::Keyboard::N:
                        return EventEntries::LIB_NEXT;
                    case sf::Keyboard::P:
                        return EventEntries::LIB_PREV;
                    case sf::Keyboard::G:
                        return EventEntries::GAME_NEXT;
                    case sf::Keyboard::B:
                        return EventEntries::GAME_PREV;
                    case sf::Keyboard::M:
                        return EventEntries::MENU;
                    case sf::Keyboard::S:
                        return EventEntries::SAVE;
                    case sf::Keyboard::R:
                        return EventEntries::ACTION2;
                    case sf::Keyboard::Enter:
                        return EventEntries::ACTION1;
                    default:
                        return EventEntries::NO_EVENT;
                }
            }
        }
        return EventEntries::NO_EVENT;
    }

    /**
     * @brief Displays the drawable elements on the SFML display.
     * 
     * This function takes a vector of Drawables and displays them on the SFML
     * display using the appropriate texture and position.
     * 
     * @param drawable A vector of Drawables to be displayed.
     */
    void Sfml::display(std::vector<Drawables> drawable)
    {
        if (drawable.empty())
            return;
        for (auto &draw : drawable) {
            for (auto &asset : _assets) {
                if (asset.first == draw.draw) {
                    sf::IntRect rect(0, 0, draw.rect.width, draw.rect.height);
                    asset.second.sprite.setTextureRect(rect);
                    asset.second.sprite.setPosition((float) draw.pos.x * _size, (float) draw.pos.y * _size);
                    _window.draw(asset.second.sprite);
                    switch (draw.direction) {
                        case Direction::UP_G:
                            asset.second.sprite.rotate(90);
                            break;
                        case Direction::DOWN_G:
                            asset.second.sprite.rotate(270);
                            break;
                        case Direction::LEFT_G:
                            asset.second.sprite.rotate(0);
                            break;
                        case Direction::RIGHT_G:
                            asset.second.sprite.rotate(180);
                            break;
                        default:
                            asset.second.sprite.rotate(0);
                            break;
                    }
                }
            }
        }
    }

    /**
     * @brief Displays text elements on the SFML display.
     * 
     * This function takes a vector of Texts and displays them on the SFML
     * display using the appropriate font, color, and position.
     * 
     * @param text A vector of Texts to be displayed.
     */
    void Sfml::display(std::vector<Texts> text)
    {
        if (text.empty())
            return;
        for (auto &txt : text) {
            _text.setString(txt.text);
            switch (txt.color) {
                case Color::RED:
                    _text.setFillColor(sf::Color::Red);
                    break;
                case Color::GREEN:
                    _text.setFillColor(sf::Color::Green);
                    break;
                case Color::BLUE:
                    _text.setFillColor(sf::Color::Blue);
                    break;
                case Color::YELLOW:
                    _text.setFillColor(sf::Color::Yellow);
                    break;
                case Color::WHITE:
                    _text.setFillColor(sf::Color::White);
                    break;
                case Color::BLACK:
                    _text.setFillColor(sf::Color::Black);
                    break;
                case Color::CYAN:
                    _text.setFillColor(sf::Color::Cyan);
                    break;
                case Color::MAGENTA:
                    _text.setFillColor(sf::Color::Magenta);
                    break;
            }
            _text.setPosition((float) txt.pos.x * _size, (float) txt.pos.y * _size);
            _window.draw(_text);
        }
    }

    /**
     * @brief Updates the SFML display.
     * 
     * This function updates the SFML display by calling the display method on
     * the window object.
     */
    void Sfml::update()
    {
        _window.display();
    }

    /**
     * @brief Closes the SFML display.
     * 
     * This function cleans up and closes the SFML display, freeing all resources
     * and destroying the window.
     */
    void Sfml::close()
    {
        _window.close();
    }

    /**
     * @brief Clears the SFML display.
     * 
     * This function clears the SFML display by calling the clear method on the
     * window object.
     */
    void Sfml::clear()
    {
        _window.clear(sf::Color::Black);
    }

    extern "C" {
        /**
         * @brief Entry point for the SFML library.
         * 
         * This function returns a new instance of the Sfml class.
         * 
         * @return A pointer to a new Sfml object.
         */
        ADisplay *entryPoint()
        {
            return new Sfml();
        }
        /**
         * @brief Returns the type of the library.
         * 
         * This function returns a C-style string indicating the type of the
         * library (in this case, "libSFML").
         * 
         * @return A C-style string indicating the library type.
         */
        char *getType()
        {
            return (char *) "libSFML";
        }
    }
}

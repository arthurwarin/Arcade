/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sfml
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #include "../../Abstract/ADisplay.hpp"
    #include "../../interface/Info.hpp"

namespace arcade {

    struct SpriteInfoSFML {
        sf::Texture texture;
        sf::Sprite sprite;
    };

    class Sfml : public ADisplay {
        public:
            Sfml();
            ~Sfml() override = default;
            void init(const std::map<char, std::string> &Assets) override;
            EventEntries getEvent() override;
            void update() override;
            void close() override;
            void display(std::vector<Drawables> drawable) override;
            void display(std::vector<Texts> text) override;
            void clear() override;

        protected:
        private:
            sf::Text _text;
            sf::Font _font;
            sf::Event _event;
            sf::Sprite _sprite;
            int _size;
            std::map<char, SpriteInfoSFML> _assets;
            sf::RenderWindow _window;
    };

}

#endif /* !SFML_HPP_ */

/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGame
*/

#ifndef AGAME_HPP_
    #define AGAME_HPP_

    #include "../interface/IGame.hpp"

namespace arcade {
    class AGame : public IGame {
        public:
            AGame();
            ~AGame() override;
            void init() override;
            void update(EventEntries event) override;
            void close() override;
            bool isRunning() override;
            const std::map<char, std::string> &getAssets() const override;
            const std::vector<Drawables> &getDrawables() const override;
            const std::vector<Texts> &getText() const override;
            void setIsRunning(bool running) override;
            MenuItem getMenu() const override;
            void setMenu(MenuItem path) override;

        protected:
            bool _running;
            std::map<char, std::string> _assets;
            std::vector<Drawables> _drawables;
            std::vector<Texts> _text;
            MenuItem _menu;
        private:
    };
}

#endif /* !AGAME_HPP_ */
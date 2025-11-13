/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplay
*/

#ifndef ADISPLAY_HPP_
    #define ADISPLAY_HPP_

    #include "../interface/IDisplay.hpp"

namespace arcade {
    class ADisplay : public IDisplay {
        public:
            ADisplay();
            ~ADisplay() override;
            void init(const std::map<char, std::string> &Assets) override;
            void update() override;
            void close() override;
            void clear() override;
            void display(std::vector<Drawables> drawable) override;
            void display(std::vector<Texts> text) override;
            EventEntries getEvent() override;

        protected:
        private:
    };
}

#endif /* !ADISPLAY_HPP_ */

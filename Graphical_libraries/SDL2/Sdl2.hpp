/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl2
*/

#ifndef SDL2_HPP_
    #define SDL2_HPP_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
    #include "../../Abstract/ADisplay.hpp"

namespace arcade {
    class Sdl2 : public ADisplay {
        public:
            Sdl2();
            ~Sdl2() override = default;
            void init(const std::map<char, std::string> &Assets) override;
            EventEntries getEvent() override;
            void update() override;
            void close() override;
            void display(std::vector<Drawables> drawable) override;
            void display(std::vector<Texts> text) override;
            void clear() override;

        protected:
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
            TTF_Font *font;
            SDL_Event event;
            int _size;
            std::map<char, SDL_Texture *> assets;
    };
}

#endif /* !SDL2_HPP_ */

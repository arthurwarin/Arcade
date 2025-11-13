/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sdl2
*/

#include "Sdl2.hpp"

namespace arcade {
    /**
     * @brief Constructor for the Sdl2 class.
     * Initializes the SDL2 display.
     * This constructor is used to set up the SDL2 display.
     * It initializes the window, renderer, font, and event variables.
     */
    Sdl2::Sdl2()
    {
    }

    /**
     * @brief Initializes the SDL2 display.
     * 
     * This function sets up the SDL2 display, initializes the window, renderer,
     * font, and loads assets from the provided map. It also sets the size of the
     * display and initializes the event variable.
     * 
     * @param Assets A map of character keys to asset file paths.
     */
    void Sdl2::init(const std::map<char, std::string> &Assets)
    {
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
        if (TTF_Init() == -1) {
            std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
            return;
        }
        window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        font = TTF_OpenFont("./Assets/font/Arial.ttf", 18);
        if (!font) {
            std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
            return;
        }
        _size = 50;
        event = SDL_Event();
        for (auto &asset : Assets) {
            SDL_Surface *surface = IMG_Load(asset.second.c_str());
            if (surface == nullptr) {
                std::cerr << "Failed to load image: " << asset.second << std::endl;
                continue;
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            if (texture == nullptr) {
                std::cerr << "Failed to create texture from surface: " << asset.second << std::endl;
                continue;
            }
            assets[asset.first] = texture;
        }

    }

    /**
     * @brief Clears the SDL2 display.
     * 
     * This function clears the SDL2 display by calling SDL_RenderClear.
     */
    void Sdl2::clear()
    {
        SDL_RenderClear(renderer);
    }

    /**
     * @brief Updates the SDL2 display.
     * 
     * This function updates the SDL2 display by calling SDL_RenderPresent.
     */
    void Sdl2::update()
    {
        SDL_RenderPresent(renderer);
    }

    /**
     * @brief Closes the SDL2 display.
     * 
     * This function cleans up and closes the SDL2 display, freeing all resources
     * and destroying the window, renderer, and font.
     */
    void Sdl2::close()
    {
        for (auto &asset : assets) {
            SDL_DestroyTexture(asset.second);
        }
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    /**
     * @brief Gets user input events from the SDL2 display.
     * 
     * This function captures user input events and returns the corresponding
     * EventEntries enum value based on the key pressed.
     * 
     * @return EventEntries The event corresponding to the key pressed.
     */
    EventEntries Sdl2::getEvent()
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return EventEntries::CLOSE;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        return EventEntries::UP;
                    case SDLK_DOWN:
                        return EventEntries::DOWN;
                    case SDLK_LEFT:
                        return EventEntries::LEFT;
                    case SDLK_RIGHT:
                        return EventEntries::RIGHT;
                    case SDLK_ESCAPE:
                        return EventEntries::CLOSE;
                    case SDLK_SPACE:
                        return EventEntries::RESTART;
                    case SDLK_n:
                        return EventEntries::LIB_NEXT;
                    case SDLK_p:
                        return EventEntries::LIB_PREV;
                    case SDLK_g:
                        return EventEntries::GAME_NEXT;
                    case SDLK_b:
                        return EventEntries::GAME_PREV;
                    case SDLK_m:
                        return EventEntries::MENU;
                    case SDLK_s:
                        return EventEntries::SAVE;
                    case SDLK_r:
                        return EventEntries::ACTION2;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        return EventEntries::ACTION1;
                    default:
                        return EventEntries::NO_EVENT;
                }
            }
        }
        return NO_EVENT;
    }

    /**
     * @brief Displays the drawable elements on the SDL2 display.
     * 
     * This function takes a vector of Drawables and displays them on the SDL2
     * display using the appropriate texture and position.
     * 
     * @param drawable A vector of Drawables to be displayed.
     */
    void Sdl2::display(std::vector<Drawables> drawable)
    {
        if (drawable.empty())
            return;
        int maxX = 0;
        int maxY = 0;
        for (auto &draw : drawable) {
            if (draw.pos.x > maxX)
                maxX = draw.pos.x;
            if (draw.pos.y > maxY)
                maxY = draw.pos.y;
        }
        int width = (maxX + 1) * _size;
        int height = (maxY + 1) * _size;
        int x = (1920 - width);
        int y = (1080 - height);
        for (auto &draw : drawable) {
            SDL_Rect rect = {draw.rect.x, draw.rect.y, draw.rect.width, draw.rect.height};
            SDL_Rect pos = {x + draw.pos.x * _size, y + draw.pos.y * _size, draw.rect.width, draw.rect.height};
            SDL_Point center = {draw.rect.width / 2, draw.rect.height / 2};
            switch (draw.direction) {
                case UP_G:
                    SDL_RenderCopyEx(renderer, assets[draw.draw], &rect, &pos, 90, &center, SDL_FLIP_NONE);
                    break;
                case DOWN_G:
                    SDL_RenderCopyEx(renderer, assets[draw.draw], &rect, &pos, 270, &center, SDL_FLIP_NONE);
                    break;
                case LEFT_G:
                    SDL_RenderCopyEx(renderer, assets[draw.draw], &rect, &pos, 0, &center, SDL_FLIP_NONE);
                    break;
                case RIGHT_G:
                    SDL_RenderCopyEx(renderer, assets[draw.draw], &rect, &pos, 180, &center, SDL_FLIP_NONE);
                    break;
                case NONE_G:
                    SDL_RenderCopy(renderer, assets[draw.draw], &rect, &pos);
                    break;
            }
        }
    }

    /**
     * @brief Displays text elements on the SDL2 display.
     * 
     * This function takes a vector of Texts and displays them on the SDL2
     * display using the appropriate font, color, and position.
     * 
     * @param text A vector of Texts to be displayed.
     */
    void Sdl2::display(std::vector<Texts> text)
    {
        if (text.empty())
            return;
        for (size_t i  = 0; i < text.size(); i++) {
            auto &txt = text[i];
            SDL_Color color = {255, 255, 255, 255};
            switch (txt.color) {
                case Color::RED:
                    color = {255, 0, 0, 255};
                    break;
                case Color::GREEN:
                    color = {0, 255, 0, 255};
                    break;
                case Color::BLUE:
                    color = {0, 0, 255, 255};
                    break;
                case Color::YELLOW:
                    color = {255, 255, 0, 255};
                    break;
                case Color::WHITE:
                    color = {255, 255, 255, 255};
                    break;
                case Color::BLACK:
                    color = {0, 0, 0, 255};
                    break;
                case Color::CYAN:
                    color = {0, 255, 255, 255};
                    break;
                case Color::MAGENTA:
                    color = {255, 0, 255, 255};
                    break;
            }
            SDL_Surface *surface = TTF_RenderText_Solid(font, txt.text.c_str(), color);
            if (surface == nullptr) {
                std::cerr << "TTF_RenderText_Solid: " << TTF_GetError() << std::endl;
                continue;
            }
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) {
                std::cerr << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(surface);
                continue;
            }
            int textWidth = surface->w;
            int textHeight = surface->h;
            SDL_Rect dstRect = {txt.pos.x * _size, txt.pos.y * _size, textWidth, textHeight};
            SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }

    extern "C" {
        /**
         * @brief Entry point for the SDL2 library.
         * 
         * This function returns a new instance of the Sdl2 class.
         * 
         * @return ADisplay* A pointer to the Sdl2 display instance.
         */
        ADisplay *entryPoint()
        {
            return new Sdl2();
        }

        /**
         * @brief Returns the type of the library.
         * 
         * This function returns a C-style string indicating the type of the
         * library (in this case, "libSDL2").
         * 
         * @return A C-style string indicating the library type.
         */
        char *getType()
        {
            return (char *) "libSDL2";
        }
    }
}
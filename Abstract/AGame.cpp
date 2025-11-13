/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** AGame
*/

#include "AGame.hpp"

namespace arcade {
    

    /**
     * @brief Constructor for the AGame class.
     * Initializes the game state and assets.
     */
    AGame::AGame()
    {
        _running = true;
        _assets = std::map<char, std::string>();
        _drawables = std::vector<Drawables>();
        _text = std::vector<Texts>();
    }

    /**
     * @brief Destructor for the AGame class.
     * Cleans up any resources used by the game.
     */
    AGame::~AGame()
    {
    }

    /**
     * @brief Initializes the game.
     * This function should be overridden by derived classes to set up the game state.
     */
    void AGame::init()
    {
    }

    /**
     * @brief Updates the game state based on the provided event.
     * This function should be overridden by derived classes to handle game logic.
     * @param event The event that triggered the update.
     */
    void AGame::update(EventEntries event)
    {
        (void)event;
    }

    /**
     * @brief Clears the game state and prepares for the next frame.
     * This function should be overridden by derived classes to handle rendering.
     */
    void AGame::close()
    {
    }

    /**
     * @brief Clears the game state and prepares for the next frame.
     * This function should be overridden by derived classes to handle rendering.
     */
    bool AGame::isRunning()
    {
        return _running;
    }

    /**
     * @brief Returns the assets used by the game.
     * @return A map of character keys to asset file paths.
     */
    const std::map<char, std::string> &AGame::getAssets() const
    {
        return _assets;
    }

    /**
     * @brief Returns the drawables used by the game.
     * @return A vector of drawables.
     */
    const std::vector<Drawables> &AGame::getDrawables() const
    {
        return _drawables;
    }

    /**
     * @brief Returns the texts used by the game.
     * @return A vector of texts.
     */
    const std::vector<Texts> &AGame::getText() const
    {
        return _text;
    }

    /**
     * @brief Returns the menu item associated with the game.
     * @return The menu item.
     */
    MenuItem AGame::getMenu() const
    {
        return _menu;
    }

    /**
     * @brief Sets the game to running or not.
     * @param running The new running state of the game.
     */
    void AGame::setIsRunning(bool runnning)
    {
        _running = runnning;
    }

    /**
     * @brief Sets the menu item associated with the game.
     * @param path The new menu item.
     */
    void AGame::setMenu(MenuItem path)
    {
        (void)path;
    }
}
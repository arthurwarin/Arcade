/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** ADisplay
*/

#include "ADisplay.hpp"

namespace arcade {
    /**
     * @brief Constructor for the ADisplay class.
     * Initializes the display state and assets.
     */
    ADisplay::ADisplay()
    {
    }

    /**
     * @brief Destructor for the ADisplay class.
     * Cleans up any resources used by the display.
     */
    ADisplay::~ADisplay()
    {
    }

    /**
     * @brief Initializes the display.
     * This function should be overridden by derived classes to set up the display state.
     * @param Assets The assets used by the display.
     */
    void ADisplay::init(const std::map<char, std::string> &Assets)
    {
        (void)Assets;
    }

    /**
     * @brief Updates the display state.
     * This function should be overridden by derived classes to handle rendering.
     */
    void ADisplay::update()
    {
    }

    /**
     * @brief Closes the display and cleans up resources.
     * This function should be overridden by derived classes to handle cleanup.
     */
    void ADisplay::close()
    {
    }

    /**
     * @brief Clears the display state and prepares for the next frame.
     * This function should be overridden by derived classes to handle rendering.
     */
    void ADisplay::clear()
    {
    }

    /**
     * @brief Displays the provided drawables on the display.
     * This function should be overridden by derived classes to handle rendering.
     * @param drawable The drawables to display.
     */
    void ADisplay::display(std::vector<Drawables> drawable)
    {
        (void)drawable;
    }

    /**
     * @brief Displays the provided texts on the display.
     * This function should be overridden by derived classes to handle rendering.
     * @param text The texts to display.
     */
    void ADisplay::display(std::vector<Texts> text)
    {
        (void)text;
    }

    /**
     * @brief Gets the current event from the display.
     * This function should be overridden by derived classes to handle event retrieval.
     * @return The current event.
     */
    EventEntries ADisplay::getEvent()
    {
        return EventEntries::NO_EVENT;
    }
}


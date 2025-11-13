/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#include "Menu.hpp"

namespace arcade {
    /**
     * @brief Constructor for the Menu class.
     * Initializes the menu state and assets.
     * This constructor is used to set up the menu for the game.
     * It initializes the libraries and games available for selection.
     * It also sets up the background and title for the menu.
     */
    Menu::Menu() : AGame()
    {
        _libs = std::vector<std::pair<std::string, std::string>>();
        _games = std::vector<std::pair<std::string, std::string>>();
        _selectedLib = std::make_pair("", "");
    }

    /**
     * @brief Destructor for the Menu class.
     * Cleans up any resources used by the menu.
     */
    Menu::~Menu()
    {
    }

    /**
     * @brief Initializes the menu.
     * This function sets up the initial state of the menu,
     * including loading libraries and setting up the background and title.
     * It also initializes the username and alphabet for user input.
     */
    void Menu::init()
    {
        _running = true;
        _username = "Player 1";
        _isUsernameSet = false;
        _alphabetIndex = 0;
        _index = 0;
        
        _alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", 
                    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
                    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "_", "DEL"};
        
        loadLibraries();
        
        _assets.insert({{'b', "./Assets/Menu/Background.png"}});
        Drawables background(0, 0, 'b');
        background.color = BLACK;
        background.direction = NONE_G;
        background.rect = {0, 0, 1920, 1080};
        _drawables.push_back(background);
        
        Texts title(0, 0, "Arcade");
        title.color = WHITE;
        title.font = "Poppins-Black";
        title.direction = NONE_G;
        _text.push_back(title);
    }

    /**
     * @brief Loads the libraries available for selection.
     * This function scans the "./lib" directory for shared object files,
     * loads them, and categorizes them as either libraries or games.
     * It also checks for valid library types and handles errors accordingly.
     */
    void Menu::loadLibraries()
    {
        _libs.clear();
        _games.clear();
        
        std::string path = "./lib";
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() != ".so") {
                std::cout << "Error: " << entry.path() << " is not a library" << std::endl;
                continue;
            }
            
            DLloader *loader = new DLloader(entry.path());
            char *libType = loader->getFunc<char>("getType");
            if (libType == nullptr) {
                std::cout << "Error: " << entry.path() << " is not a valid library" << std::endl;
                delete loader;
                continue;
            }
            
            std::string typeStr(libType);
            
            if (typeStr.substr(0, 3) == "lib") {
                _libs.emplace_back(typeStr.substr(3), entry.path().string());
            } else if (typeStr.substr(0, 4) == "game") {
                _games.emplace_back(typeStr.substr(4), entry.path().string());
            } else {
                std::cout << "Error: " << entry.path() << " is not a valid library type" << std::endl;
            }
            
            delete loader;
        }
    }

    /**
     * @brief Updates the menu based on user input.
     * This function handles user input events and updates the menu state accordingly.
     * It allows the user to navigate through libraries and games, select options,
     * and set the username.
     * @param event The event that triggered the update.
     */
    void Menu::update(EventEntries event)
    {
        _text.clear();
        
        if (!_isUsernameSet) {
            Texts usernameLabel(19, 1, "Username :");
            usernameLabel.color = WHITE;
            usernameLabel.font = "Poppins-Black";
            usernameLabel.direction = NONE_G;
            _text.push_back(usernameLabel);

            Texts usernameText(19 + 6, 1, _username);
            usernameText.color = WHITE;
            usernameText.font = "Poppins-Black";
            usernameText.direction = NONE_G;
            _text.push_back(usernameText);

            int line = 3;
            int index = 0;
            int indexInAlphabet = 0;

            for (const auto &letter : _alphabet) {
                if (index == 20) { 
                    index = 0; 
                    line += 1; 
                }

                Color color = (_alphabetIndex == indexInAlphabet) ? RED : WHITE;
                Texts letterText(14 + index, line, letter);
                letterText.color = color;
                letterText.font = "Poppins-Black";
                letterText.direction = NONE_G;
                _text.push_back(letterText);

                index += 1;
                indexInAlphabet += 1;
            }
            switch (event) {
                case EventEntries::LEFT:
                    _alphabetIndex -= 1;
                    if (_alphabetIndex < 0) _alphabetIndex = _alphabet.size() - 1;
                    break;
                case EventEntries::RIGHT:
                    _alphabetIndex += 1;
                    if (_alphabetIndex >= (int) _alphabet.size()) _alphabetIndex = 0;
                    break;
                case EventEntries::ACTION1:
                    if (_alphabet[_alphabetIndex] == "DEL") {
                        if (_username.size() > 0) _username.pop_back();
                    } else if (_alphabet[_alphabetIndex] == " ") {
                        if (_username.size() < 10) _username += " ";
                    } else {
                        if (_username.size() < 10) _username += _alphabet[_alphabetIndex];
                    }
                    break;
                case EventEntries::CLOSE: 
                    _running = false; 
                    break;
                case EventEntries::ACTION2: 
                    if (!_username.empty()) {
                        _isUsernameSet = true;
                        _index = 0;  // Reset index when entering menu selection
                    }
                    break;
                default: 
                    break;
            }
            return;
        }
        int index = 5;
        size_t indexSelector = 0;
        
        Texts libsLabel(10, index, "Libs :");
        libsLabel.color = WHITE;
        libsLabel.font = "Poppins-Black";
        libsLabel.direction = NONE_G;
        _text.push_back(libsLabel);
        index += 1;
        
        for (const auto &lib : _libs) {
            Color color = indexSelector == _index ? RED : 
                           _selectedLib.first == lib.first ? GREEN : WHITE;
                           
            Texts libText(10, index, lib.first);
            libText.color = color;
            libText.font = "Poppins-Black";
            libText.direction = NONE_G;
            _text.push_back(libText);
            indexSelector += 1; 
            index += 1;
        }
        
        Texts gamesLabel(10, index, "Games :");
        gamesLabel.color = WHITE;
        gamesLabel.font = "Poppins-Black";
        gamesLabel.direction = NONE_G;
        _text.push_back(gamesLabel);
        index += 1;
        
        for (const auto &game : _games) {
            Color color = indexSelector == _index ? RED : 
                           _selectedGame.first == game.first ? GREEN : WHITE;
                           
            Texts gameText(10, index, game.first);
            gameText.color = color;
            gameText.font = "Poppins-Black";
            gameText.direction = NONE_G;
            _text.push_back(gameText);
            indexSelector += 1; 
            index += 1;
        }
        switch (event) {
            case EventEntries::CLOSE:   
                close(); 
                return;
            case EventEntries::RESTART: 
                close(); 
                init(); 
                return;
            case EventEntries::LEFT:   
                _isUsernameSet = false; 
                break;
            case EventEntries::UP:
                if (_index == 0) 
                    _index = _libs.size() + _games.size() - 1;
                else 
                    _index--;
                break;
            case EventEntries::DOWN:
                if (_index == _libs.size() + _games.size() - 1) 
                    _index = 0;
                else 
                    _index++;
                break;
            case EventEntries::ACTION1:
                if (_index >= _libs.size()) 
                    _selectedGame = _games[_index - _libs.size()];
                else 
                    _selectedLib = _libs[_index];
                break;
            case EventEntries::ACTION2:
                if (!_selectedLib.first.empty() && !_selectedGame.first.empty()) {
                    _menuInfo = {_selectedGame.second, _selectedLib.second, _username};
                }
                break;
            default: 
                break;
        }
    }

    /**
     * @brief Closes the menu and cleans up resources.
     * This function clears the menu state and releases any resources used by the menu.
     */
    void Menu::close()
    {
        _running = false;
        _libs.clear();
        _games.clear();
    }

    /**
     * @brief Returns the current menu state.
     * This function returns the current menu state, including the selected game and library.
     * @return The current menu state.
     */
    void Menu::setMenuInfo(const MenuItem& info)
    {
        _menuInfo = info;
    }

    /**
     * @brief Returns the current menu state.
     * This function returns the current menu state, including the selected game and library.
     * @return The current menu state.
     */
    MenuItem Menu::getMenuInfo() const
    {
        return _menuInfo;
    }

    /**
     * @brief Returns the current menu state.
     * This function returns the current menu state, including the selected game and library.
     * @return The current menu state.
     */
    MenuItem Menu::getMenu() const
    {
        return _menuInfo;
    }
    
    /**
     * @brief Sets the current menu state.
     * This function sets the current menu state, including the selected game and library.
     * @param path The new menu state to set.
     */
    void Menu::setMenu(MenuItem path)
    {
        _menuInfo = path;
    }

    /**
     * @brief Entry point for the dynamic library.
     * This function is called when the library is loaded.
     * It returns a pointer to the Menu object.
     * @return A pointer to the Menu object.
     */
    extern "C" {
        IGame *entryPoint()
        {
            return new Menu();
        }

        char *getType()
        {
            return (char *) "gameMenu";
        }
    }
}
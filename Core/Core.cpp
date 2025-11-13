/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core
*/

#include "Core.hpp"

namespace arcade {
    Core::Core()
    {
    }
    
    /**
     * @brief Constructor for the Core class.
     * Initializes the core components and loads the libraries.
     * @param libPath The path to the graphical library.
     */
    Core::Core(std::string libPath)
    {
        _currentGame = 0;
        _currentLib = 0;
        _graphicLoader = new DLloader(libPath);
        char *str = _graphicLoader->getFunc<char>("getType");
        if (str == nullptr) {
            std::cerr << "Error: A" << libPath << " is not valid" <<std::endl;
            exit(84);
        }
        setLib(_graphicLoader->getFunc<IDisplay>("entryPoint"));
        if (!std::filesystem::exists(MENU_PATH)) {
            std::cerr << "Error: B" << MENU_PATH<< " is not valid" <<std::endl;
            exit(84);
        }
        _gameLoader = new DLloader(MENU_PATH);
        setGame(_gameLoader->getFunc<IGame>("entryPoint"));
        std::string path = "./lib";
        for (auto &entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() != ".so") {
                std::cout << "Error: C" << entry.path() << " is not a library" << std::endl;
            }
            DLloader *load = new DLloader(entry.path());
            char *tmp = load->getFunc<char>("getType");
            if (tmp == nullptr) {
                std::cerr << "Error: D" << entry.path() << " is not valid" <<std::endl;
                exit(84);
            }
            if (std::string(tmp).compare(0, 3, "lib") == 0)
                _libPath.push_back(entry.path());
            else if (std::string(tmp).compare(0, 4, "game") == 0)
                _gamePath.push_back(entry.path());
            else
                std::cerr << "Error: E" << entry.path() << " is not a valid library" << std::endl;
        }
    }

    /**
     * @brief Constructor for the Core class.
     * Initializes the core components and loads the libraries.
     * @param libPath The path to the graphical library.
     * @param gamePath The path to the game library.
     */
    Core::Core(std::string libPath, std::string gamePath)
    {
        _graphicLoader = new DLloader(libPath);
        setLib(_graphicLoader->getFunc<IDisplay>("entryPoint"));
        _gameLoader = new DLloader(gamePath);
        setGame(_gameLoader->getFunc<IGame>("entryPoint"));
    }

    /**
     * @brief Destructor for the Core class.
     * Cleans up the core components and libraries.
     */
    void Core::run()
    {
        _game->init();
        _lib->init(_game->getAssets());
        while(_game->isRunning()) {
            _lib->display(_game->getDrawables());
            _lib->display(_game->getText());
            EventEntries event = _lib->getEvent();
            
            if (event == EventEntries::MENU) {
                setMenu();
            }
            _game->update(event);
            setChangeLib(event);
            setChangeGame(event);
            menuGetChange();
            if (!_game->isRunning())
                break;
            _lib->update();
            _lib->clear();
        }
        _lib->close();
    }

    /**
     * @brief Sets the menu for the game.
     * Initializes the menu and displays it using the graphical library.
     */
    void Core::setMenu()
    {
        if (!std::filesystem::exists(MENU_PATH)) {
            std::cerr << "Error: F" << MENU_PATH << " is not valid" <<std::endl;
            return;
        }
        _game->close();
        _lib->close();
        _gameLoader = new DLloader(MENU_PATH);
        setGame(_gameLoader->getFunc<IGame>("entryPoint"));
        _game->init();
        _lib->init(_game->getAssets());
        _lib->display(_game->getDrawables());
        _lib->display(_game->getText());
        _lib->update();
        _lib->clear();
    }

    /**
     * @brief Sets the game and graphical library for the core.
     * @param game The game library to set.
     */
    void Core::setGame(IGame *game)
    {
        _game = game;
    }

    /**
     * @brief Sets the graphical library for the core.
     * @param lib The graphical library to set.
     */
    void Core::setLib(IDisplay *lib)
    {
        _lib = lib;
    }

    /**
     * @brief Sets the game path for the core.
     * @param path The path to the game library.
     */
    void Core::setChangeGame(EventEntries event)
    {
        if (event == EventEntries::GAME_NEXT) {
            if (_currentGame == _gamePath.size() - 1)
                _currentGame = 0;
            else
                _currentGame++;
            changeGame(_gamePath[_currentGame]);
        } else if (event == EventEntries::GAME_PREV) {
            if (_currentGame == 0)
                _currentGame = _gamePath.size() - 1;
            else
                _currentGame--;
            changeGame(_gamePath[_currentGame]);
        }
    }

    /**
     * @brief Sets the graphical library path for the core.
     * @param path The path to the graphical library.
     */
    void Core::setChangeLib(EventEntries event)
    {
        if (event == EventEntries::LIB_NEXT) {
            if (_currentLib == _libPath.size() - 1)
                _currentLib = 0;
            else
                _currentLib++;
            changeLib(_libPath[_currentLib]);
        } else if (event == EventEntries::LIB_PREV) {
            if (_currentLib == 0)
                _currentLib = _libPath.size() - 1;
            else
                _currentLib--;
            changeLib(_libPath[_currentLib]);
        }
    }

    /**
     * @brief Sets the menu for the game.
     * Initializes the menu and displays it using the graphical library.
     */
    void Core::menuGetChange()
    {
        MenuItem tmp = _game->getMenu();
        if (tmp.gpath == "" || tmp.lpath == "")
            return;
        else {
            if (!std::filesystem::exists(tmp.lpath)) {
                std::cerr << "Error: G" << tmp.lpath << " is not valid" <<std::endl;
                return;
            } else if (!std::filesystem::exists(tmp.gpath)) {
                std::cerr << "Error: H" << tmp.gpath << " is not valid" <<std::endl;
                return;
            }
            _menu = tmp;
            changeGame(_menu.gpath);
            changeLib(_menu.lpath);
        }
    }

    /**
     * @brief Changes the graphical library for the core.
     * @param lib The new graphical library to set.
     */
    void Core::changeLib(std::string lib)
    {
        _lib->close();
        _graphicLoader->~DLloader();
        _graphicLoader = new DLloader(lib);
        setLib(_graphicLoader->getFunc<IDisplay>("entryPoint"));
        _lib->init(_game->getAssets());
    }

    /**
     * @brief Changes the game for the core.
     * @param game The new game library to set.
     */
    void Core::changeGame(std::string game)
    {
        _game->close();
        _gameLoader->~DLloader();
        _gameLoader = new DLloader(game);
        setGame(_gameLoader->getFunc<IGame>("entryPoint"));
        _game->setMenu({_menu.pseudo, "", ""});
        _game->init();
        _lib->close();
        _lib->init(_game->getAssets());
    }

    /**
     * @brief Destructor for the Core class.
     * Cleans up the core components and libraries.
     */
    Core::~Core()
    {
    }
}

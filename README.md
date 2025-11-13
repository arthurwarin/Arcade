Arcade
A comprehensive gaming platform featuring multiple retro games with interchangeable graphical libraries, built as part of an advanced C++ architecture project.
Overview
Arcade is a modular gaming platform that demonstrates advanced software architecture principles through a plugin-based system. The project allows users to play classic arcade games (Snake and Nibbler) using different rendering engines (SFML, SDL2, or Ncurses), all switchable in real-time without restarting the application.
Key Features

Dynamic Library Loading: Games and graphical libraries are loaded at runtime using the dlopen system
Hot-Swapping: Switch between graphical libraries and games on-the-fly during gameplay
Multiple Rendering Engines:

SFML (hardware-accelerated graphics)
SDL2 (cross-platform multimedia)
Ncurses (terminal-based display)


Interactive Menu System: Username input with alphabet selection and game/library selection
Score Persistence: High scores saved between sessions
Progressive Difficulty: Dynamic speed increases based on score

Architecture
The project follows a plugin architecture pattern with clear separation of concerns:

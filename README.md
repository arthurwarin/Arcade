# Arcade

A comprehensive gaming platform featuring multiple retro games with interchangeable graphical libraries, built as part of an advanced C++ architecture project.

## Overview

Arcade is a modular gaming platform that demonstrates advanced software architecture principles through a plugin-based system. The project allows users to play classic arcade games (Snake and Nibbler) using different rendering engines (SFML, SDL2, or Ncurses), all switchable in real-time without restarting the application.

## Key Features

- **Dynamic Library Loading**: Games and graphical libraries are loaded at runtime using the `dlopen` system
- **Hot-Swapping**: Switch between graphical libraries and games on-the-fly during gameplay
- **Multiple Rendering Engines**:
  - SFML (hardware-accelerated graphics)
  - SDL2 (cross-platform multimedia)
  - Ncurses (terminal-based display)
- **Interactive Menu System**: Username input with alphabet selection and game/library selection
- **Score Persistence**: High scores saved between sessions
- **Progressive Difficulty**: Dynamic speed increases based on score

## Architecture

The project follows a plugin architecture pattern with clear separation of concerns:

```
┌─────────────┐
│    Core     │  ← Orchestrates game loop and library management
└──────┬──────┘
       │
   ┌───┴────┐
   │        │
┌──▼──┐  ┌─▼────┐
│Games│  │Display│  ← Abstract interfaces
└──┬──┘  └─┬────┘
   │        │
   ├────────┼────────┐
   │        │        │
┌──▼──┐ ┌──▼──┐  ┌─▼────┐
│Snake│ │SFML │  │SDL2  │  ← Concrete implementations
└─────┘ │     │  │      │
        └─────┘  └──────┘
```

### Core Components

- **Abstract Base Classes**: `AGame` and `ADisplay` provide common functionality
- **Interface Definitions**: `IGame` and `IDisplay` define contracts for plugins
- **Dynamic Loader**: Custom `DLloader` class handles runtime library management
- **Core Engine**: Manages game state, event handling, and library switching

## Technical Highlights

- **Modern C++20**: Utilizes latest language features and STL
- **CMake Build System**: Cross-platform build configuration
- **Design Patterns**: 
  - Strategy Pattern (interchangeable libraries)
  - Template Method Pattern (abstract base classes)
  - Factory Pattern (dynamic object creation)
- **Real-time Event Handling**: Non-blocking input processing
- **Memory Management**: Proper resource cleanup and RAII principles

## Games

### Snake
Classic snake game with wall collision detection, apple collection, and progressive difficulty.

### Nibbler
Enhanced snake variant with maze navigation and automatic pathfinding around obstacles.

## Controls

| Key | Action |
|-----|--------|
| Arrow Keys | Movement |
| SPACE | Restart game |
| ENTER | Validate selection / Action 1 |
| R | Action 2 |
| N / P | Switch graphical library (next/previous) |
| G / B | Switch game (next/previous) |
| M | Return to menu |
| ESC | Exit |

## Building the Project

```bash
# Clone the repository
git clone <repository-url>
cd arcade

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
cmake --build .

# Run (from project root)
./arcade ./lib/arcade_sfml.so
```

### Requirements

- C++20 compatible compiler (GCC 10+ / Clang 12+)
- CMake 3.20+
- SFML 2.5+
- SDL2 and SDL2_image, SDL2_ttf
- Ncurses

## Project Structure

```
arcade/
├── Abstract/          # Base classes for games and displays
├── Core/              # Core engine and dynamic loader
├── Games/             # Game implementations
│   ├── Menu/
│   ├── Snake/
│   └── Nibbler/
├── Graphical_libraries/  # Display implementations
│   ├── SFML/
│   ├── SDL2/
│   └── Ncurses/
├── interface/         # Interface definitions
└── Assets/            # Game resources (sprites, fonts, configs)
```

## Learning Outcomes

This project demonstrates proficiency in:

- Object-oriented design and polymorphism
- Dynamic library management and plugin architecture
- Cross-platform development
- Real-time game loop implementation
- Resource management and memory safety
- Modern C++ best practices
- Build system configuration
- Documentation with Doxygen

---

*This project was developed as part of the EPITECH curriculum, focusing on advanced C++ programming and software architecture.*

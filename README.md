# Raylib Game Engine

This project is a simple game engine built using Raylib, designed to provide basic game development functionality such as game objects, components, and rendering. The engine is written in C++ and supports Linux platforms.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Configuration](#configuration)
- [Components](#components)
- [License](#license)

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/AakrishtSP/Game-Engine.git
    cd Game-Engine/
    ```

2. **Install Raylib**:
    Follow the instructions on the [Raylib official website](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) to install Raylib on your system.

3. **Build the project**:
    Open the project in Visual Studio Code and press `Ctrl+Shift+B` to build the project using the provided tasks.

## Usage

1. **Run the project**:
    After building, you can run the project from within Visual Studio Code by pressing `F5`.

2. **Modify the code**:
    The main game loop and initialization are defined in `src/main.cpp`. Modify this file to change game behavior, add new components, or customize rendering.

## Project Structure

```
Game-Engine/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── src/
│   ├── Components/
│   │   ├── SpriteRenderer.hpp
│   │   └── Transform2D.hpp
│   ├── GameObject.hpp
│   ├── Component.hpp
│   ├── Base.hpp
│   └── main.cpp
├── assets/
│   └── Raylib_logo.png
└── README.md
```

- **.vscode/**: Contains Visual Studio Code configuration files for building and debugging the project.
- **src/**: Contains all source code files for the project.
- **assets/**: Contains asset files such as images and textures.
- **README.md**: This file.


## Components

### Transform2D

The `Transform2D` component manages the position, rotation, and scale of a game object.

### SpriteRenderer

The `SpriteRenderer` component handles rendering a texture on the screen.

### GameObject

The `GameObject` class manages components and children game objects.

### Component

The `Component` class is a base class for all components in the game engine.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
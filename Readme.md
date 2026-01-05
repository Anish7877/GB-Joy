# GBJoy

A Game Boy emulator written in C++20 using SDL2 for graphics and input handling.

## Features

- **Core Emulation**: Implements CPU, PPU, APU, and memory bus emulation
- **Graphics**: Renders game output via SDL2
- **Audio**: Basic audio support
- **Input**: Keyboard support for standard Game Boy controls
- **ROM Support**: Loads standard `.gb` ROM files

## Prerequisites

To build GBJoy, you need the following installed on your system:

- **C++ Compiler**: Must support C++20 (e.g., GCC 10+, Clang 10+)
- **CMake**: Version 3.16 or higher
- **SDL2**: Development libraries for SDL2

### Installing Dependencies

#### Linux (Debian/Ubuntu-based)
```bash
sudo apt-get install cmake libsdl2-dev g++
```

## Build Instructions

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd GBJoy
   ```

2. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Generate build files with CMake:**
   ```bash
   cmake ..
   ```

4. **Compile the project:**
   ```bash
   make
   ```

## Usage

Run the emulator from the command line by passing the path to a Game Boy ROM file as an argument:

```bash
./GBJoy <path-to-gameboy-rom>
```

**Example:**
```bash
./GBJoy ../roms/tetris.gb
```

## Controls

The emulator maps keyboard keys to the Game Boy joypad inputs as follows:

| Game Boy Button | Keyboard Key |
|----------------|--------------|
| D-Pad Up       | W            |
| D-Pad Down     | S            |
| D-Pad Left     | A            |
| D-Pad Right    | D            |
| A              | J            |
| B              | K            |
| Start          | 1            |
| Select         | 2            |

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Anish7877

## Acknowledgments

- Game Boy documentation from the [Pan Docs](https://gbdev.io/pandocs/)
- SDL2 library for cross-platform multimedia support

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Known Issues

- Audio emulation is basic and may have some inaccuracies
- Some advanced mapper types may not be fully supported

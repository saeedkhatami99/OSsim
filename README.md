# Operating System Simulation

A straightforward OS/terminal simulation with fundamental system capabilities (resembling Linux).

## Build Instructions

This project is written in C++ and requires a C++ compiler that supports C++17 or later (for std::filesystem).

### Prerequisites

- Windows OS (due to Windows-specific APIs)
- C++ compiler (e.g., Visual Studio, MinGW)
- Windows SDK for Windows APIs

### Building

1. Clone or download the repository.
2. Compile the source files: `OS.cpp`, `User_cmd.cpp`, and headers `Boot.hpp`, `Core.hpp`, `Logs.hpp`, `User_cmd.hpp`.
3. Link with required libraries: `Winmm.lib` (for MP3 playback).
4. Example command with g++:

   ```ps
   g++ -std=c++17 OS.cpp User_cmd.cpp -o OSsim.exe -lwinmm
   ```

### Running

- Run `OSsim.exe` from the command line.
- The program requires elevated privileges.
- On first run, create a user account.
- Type `help` for available commands.

## Known Issues

- The `ls` command may crash when attempting to list directories within a non-existent path. (Fixed in modern version with error handling)
- Currently only `BMP` files are being rendered in terminal, you will need to add `BMP` conversion functions to actually render other file types.

## Project Details

This is part of a college assignment. The code has been modernized to use C++17 features, improved error handling, and better code structure.

### Programming Languages

- **C++** (with some C-style elements for Windows compatibility)

### Features

- User authentication
- File and directory operations
- System information display
- Basic text editing
- Image rendering (BMP only)
- MP3 playback
- Logging

### Modernizations Applied

- Replaced C-style strings with std::string
- Used modern C++ features (auto, range-based loops, filesystem)
- Added comprehensive error handling
- Improved code structure and readability
- Enhanced security considerations

No external libraries were utilized, which results in some limitations in the program's features. One notable omission in this codebase is the absence of multithreading capabilities (easily implementable, see my [Multithread](https://github.com/saeedkhatami99/MultiThread)).

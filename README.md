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

## Limitations

- Image rendering is limited to BMP files only, as no external image processing libraries are used to maintain pure standard C++ implementation.

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
- Multithreaded command execution and UI updates

No external libraries were utilized, which results in some limitations in the program's features.

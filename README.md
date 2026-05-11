# Othello

## Overview

Basic implemenation of the game Othello using C++.

Supports 1-Player mode (vs Computer), and 2-Player mode (Player vs Player). The computer has no intelligent strategy, and will always play the first valid move it finds.

## Playing the Game

When the program runs, the Othello game board will be shown, along with supported commands, player info/scores, command feedback, and a user input section.

Enter a command using the keyboard, and press ``Enter``. <br>
The result of the command will be shown in the feedback area.

Supported commands are:
- [1]: New One Player Game (Player vs Computer)
- [2]: New Two Player Game (Player vs Player)
- [X]: Exit Game
- [A-H][1-8]: Make a move, e.g. D3, E6.

The players (or computer) will take turns placing pieces, until no more moves are possible. The player with the highest score will win. For further details of the rules, see [Reversi](https://en.wikipedia.org/wiki/Reversi).

## Modules

The project is made up of various modules performing separate functions:

- main <br>
  Main sequence of the program in an endless loop.

- game <br>
  The game logic, such as gameplay rules, game board, game states, player info/scores, and computer player.

- input <br>
  Parses the player input for use by the game, includes input verification.

- display <br>
  Display the UI on the terminal, includes the game board, player scores, command feedback interface, and program header.

```mermaid
flowchart LR
    Keyboard([Keyboard]) -->|Player Input| Input
    Input -->|Parsed Input| Game
    Game -->|Game State| Display
    Display -->|UI Data| Terminal([Terminal UI])
```

## Building the Project

The project was developed and tested in Linux, therefore would build and run best in Linux.

The project's build script and CMake configuration also support cross compiling a Windows executable. To make the program display correctly on Windows, support for UTF-8 output and Virtual Terminal ANSI processing were added.

The project has not been compiled natively in Windows.

### Building for Linux

1. Install the GNU C++ compiler and CMake:
    ```
    sudo apt install build-essential cmake
    ```
    Verify by:
    ```
    g++ --version
    cmake --version
    ```

2. Run the build script with linux argurment:
    ```
    ./scripts/build.sh linux
    ```

3. Obtain the Linux executable from the build folder:
    ```
    /build/othello
    ```


### Building for Windows

1. Install the MinGW cross compiler and CMake:
    ```
    sudo apt install mingw-w64 cmake
    ```
    Verify by:
    ```
    x86_64-w64-mingw32-g++ --version
    cmake --version
    ```

2. Run the build script with windows argurment:
    ```
    ./scripts/build.sh windows
    ```

3. Obtain the Windows executable from the build folder:
    ```
    /build-win/othello.exe
    ```

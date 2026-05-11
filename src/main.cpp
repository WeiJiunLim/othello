/*
 *  File        : main.cpp
 *  Description : Main code entry point
 *  Author      : Wei Jiun Lim
 *  Created     : 9 May 2026
 */

/* ====================================================================================================================
 *  Includes
 * ================================================================================================================= */

#include "types.hpp"
#include "display.hpp"
#include "game.hpp"
#include "input.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

/* ====================================================================================================================
 *  Constants / Macros
 * ================================================================================================================= */

/* Software info */
constexpr const char* SW_NAME = "Othello";
constexpr const char* SW_VERSION = "0.1";

constexpr const char* SW_INSTRUCTIONS =
"1: New One Player Game (Player vs Computer)\n\
2: New Two Player Game (Player vs Player)\n\
X: Exit Game\n\
[A-H][1-8]: Make a move, e.g. D3, E6\n";

using namespace othello;

 /* ====================================================================================================================
  *  Local Function Prototypes
  * ================================================================================================================= */

#ifdef _WIN32
void initWindowsTerminal();
#endif

 /* ====================================================================================================================
  *  Public Functions
  * ================================================================================================================= */

int main() {

#ifdef _WIN32
    /* For Windows compatibility */
    initWindowsTerminal();
#endif

    Display display(SW_NAME, SW_VERSION, SW_INSTRUCTIONS);
    GameBoard gameBoard;
    PlayerInput playerInput;

    /* Start a 1 Player game by default */
    gameBoard.reset(GameType::OnePlayer);

    while (true) {

        /* Refresh game display */
        display.refreshGame(gameBoard);

        /* Get input, either from computer or human */
        if ((gameBoard.isGameRunning()) &&
            (gameBoard.getGameType() == GameType::OnePlayer) &&
            (gameBoard.getTurnPlayer() == CellState::White)) {

            /* Computer's turn */
            gameBoard.gameInput = gameBoard.compMove();
        }
        else {

            /* Get user input */
            std::string inputStr;
            std::getline(std::cin, inputStr);

            /* Parse user input */
            gameBoard.gameInput = playerInput.parseInput(inputStr);
        }

        /* Take action on the input */
        switch (gameBoard.gameInput.type)
        {
            case InputType::NewGame2P:
                gameBoard.reset(GameType::TwoPlayer);
                break;

            case InputType::NewGame1P:
                gameBoard.reset(GameType::OnePlayer);
                break;

            case InputType::Exit:
                gameBoard.setGameState(GameState::Exit);
                break;

            case InputType::Move:
            {
                if (gameBoard.isGameRunning()) {
                    gameBoard.playerMove(gameBoard.gameInput);
                }
                else {
                    gameBoard.setGameState(GameState::InvalidInputAtGameEnded);
                }
                break;
            }

            default:
                /* Invalid input */
                if (gameBoard.isGameRunning()) {
                    gameBoard.setGameState(GameState::InvalidInput);
                }
                else {
                    gameBoard.setGameState(GameState::InvalidInputAtGameEnded);
                }

                break;
        }

        /* Check for exit request */
        if (gameBoard.getGameState() == GameState::Exit) {
            break;
        }
    }

    return 0;
}

 /* ====================================================================================================================
  *  Local Functions
  * ================================================================================================================= */

#ifdef _WIN32
/* Function to allow UTF-8 output, and Virtual Terminal ANSI processing on Windows.
 * Copied from online */
void initWindowsTerminal()
{
    /* Enable UTF-8 output */
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    /* Enable ANSI escape sequence processing */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;

    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if (!SetConsoleMode(hOut, dwMode))
        return;
}
#endif

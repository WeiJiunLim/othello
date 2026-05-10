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

/* ====================================================================================================================
 *  Constants / Macros
 * ================================================================================================================= */

/* Software info */
constexpr const char* SW_NAME = "Othello";
constexpr const char* SW_VERSION = "0.1";
constexpr const char* SW_INSTRUCTIONS =
"P: New Game (Player vs Player)\n\
N: New Game (Player vs Computer)\n\
X: Exit Game\n\
[col][row]: Make a move [A-H][1-8], e.g. D3, E6\n";

 /* ====================================================================================================================
 *  Public Functions
 * ================================================================================================================= */

int main() {

    othello::Display display(SW_NAME, SW_VERSION, SW_INSTRUCTIONS);
    othello::GameBoard gameBoard;
    othello::PlayerInput playerInput;

    /* Start a PVP game by default */
    gameBoard.reset(othello::GameType::PVP);

    while (1) {

        /* Refresh game display */
        display.refreshGame(gameBoard);

        /* Get user input */
        std::string inputStr;
        std::getline(std::cin, inputStr);

        /* Parse user input */
        othello::GameInput gameInput = playerInput.parseInput(inputStr);

        /* Take action on user input */
        switch (gameInput.type)
        {
            case othello::InputType::NewGamePVP:
                gameBoard.reset(othello::GameType::PVP);
                break;

            case othello::InputType::NewGamePVC:
                gameBoard.reset(othello::GameType::PVC);
                break;

            case othello::InputType::Exit:
                gameBoard.setGameState(othello::GameState::Exit);
                break;

            case othello::InputType::Move:
                gameBoard.move(gameInput);
                break;

            default:
                /* Invalid input */
                gameBoard.setGameState(othello::GameState::InvalidInput);
                break;
        }

        /* Check for exit request */
        if (gameBoard.getGameState() == othello::GameState::Exit) {
            break;
        }
    }

    return 0;
}


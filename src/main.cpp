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
"1: New One Player Game (Player vs Computer)\n\
2: New Two Player Game (Player vs Player)\n\
X: Exit Game\n\
[A-H][1-8]: Make a move, e.g. D3, E6\n";

 /* ====================================================================================================================
 *  Public Functions
 * ================================================================================================================= */

int main() {

    othello::Display display(SW_NAME, SW_VERSION, SW_INSTRUCTIONS);
    othello::GameBoard gameBoard;
    othello::PlayerInput playerInput;

    /* Start a 2 Player game by default */
    gameBoard.reset(othello::GameType::TwoPlayer);

    while (true) {

        /* Refresh game display */
        display.refreshGame(gameBoard);

        /* Get user input */
        std::string inputStr;
        std::getline(std::cin, inputStr);

        /* Parse user input */
        gameBoard.gameInput = playerInput.parseInput(inputStr);

        /* Take action on user input */
        switch (gameBoard.gameInput.type)
        {
            case othello::InputType::NewGame2P:
                gameBoard.reset(othello::GameType::TwoPlayer);
                break;

            case othello::InputType::NewGame1P:
                gameBoard.reset(othello::GameType::OnePlayer);
                break;

            case othello::InputType::Exit:
                gameBoard.setGameState(othello::GameState::Exit);
                break;

            case othello::InputType::Move:
            {
                if (gameBoard.isGameRunning()) {
                    gameBoard.move(gameBoard.gameInput);
                }
                else {
                    gameBoard.setGameState(othello::GameState::InvalidInputAtGameEnded);
                }
                break;
            }

            default:
                /* Invalid input */
                if (gameBoard.isGameRunning()) {
                    gameBoard.setGameState(othello::GameState::InvalidInput);
                }
                else {
                    gameBoard.setGameState(othello::GameState::InvalidInputAtGameEnded);
                }

                break;
        }

        /* Check for exit request */
        if (gameBoard.getGameState() == othello::GameState::Exit) {
            break;
        }
    }

    return 0;
}


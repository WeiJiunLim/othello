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

using namespace othello;

 /* ====================================================================================================================
 *  Public Functions
 * ================================================================================================================= */

int main() {

    Display display(SW_NAME, SW_VERSION, SW_INSTRUCTIONS);
    GameBoard gameBoard;
    PlayerInput playerInput;

    /* Start a 2 Player game by default */
    gameBoard.reset(GameType::TwoPlayer);

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

